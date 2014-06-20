#include "gen2/G2Box.h"

#include "gen2/Generation2.h"

enum {
	G2_BOX_SIZE = 1104,

	G20E_CURRENT_BOX_ID = 0x2724,
	G21E_CURRENT_BOX_ID = 0x2700,
	G20E_BOX_NAMES = 0x2727,
	G21E_BOX_NAMES = 0x2703,
	G20E_CURRENT_BOX = 0x2D6C,
	G21E_CURRENT_BOX = 0x2D11,
	G20E_BOX_1 = 0x4000,
	G20E_BOX_8 = 0x6000,
};

G2Box::G2Box(Generation2* gen, unsigned box)
	: GBGroup<G2BasePokemon>(gen)
{
	uint8_t* start = gen->ram();
	switch (gen->version() & Game::MASK_GAME) {
	case Game::G20_GOLD:
	case Game::G20_SILVER:
	default:
		if (box == (gen->ram()[G20E_CURRENT_BOX_ID] & 0xF)) {
			start += G20E_CURRENT_BOX;
		} else if (box < 7) {
			start += G20E_BOX_1 + box * G2_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G20E_BOX_8 + (box - 7) * G2_BOX_SIZE;
		} else {
			start += G20E_CURRENT_BOX;
		}
		m_name = gen->gameTextToUTF8(&gen->ram()[G20E_BOX_NAMES + 9 * box], 9);
		break;
	case Game::G21_CRYSTAL:
		if (box == (gen->ram()[G21E_CURRENT_BOX_ID] & 0xF)) {
			start += G21E_CURRENT_BOX;
		} else if (box < 7) {
			start += G20E_BOX_1 + box * G2_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G20E_BOX_8 + (box - 7) * G2_BOX_SIZE;
		} else {
			start += G21E_CURRENT_BOX;
		}
		m_name = gen->gameTextToUTF8(&gen->ram()[G21E_BOX_NAMES + 9 * box], 9);
		break;
	}

	setStart(start);
}

unsigned G2Box::capacity() const {
	return 20;
}

std::string G2Box::name() const {
	return m_name;
}
