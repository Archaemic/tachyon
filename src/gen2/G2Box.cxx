#include "gen2/G2Box.h"

#include "gen2/Generation2.h"

enum {
	G20J_BOX_SIZE = 1354,
	G20E_BOX_SIZE = 1104,

	G20J_CURRENT_BOX_ID = 0x2705,
	G20E_CURRENT_BOX_ID = 0x2724,
	G21E_CURRENT_BOX_ID = 0x2700,

	G20J_BOX_NAMES = 0x2708,
	G20E_BOX_NAMES = 0x2727,
	G21E_BOX_NAMES = 0x2703,

	G20J_CURRENT_BOX = 0x2D10,
	G20E_CURRENT_BOX = 0x2D6C,
	G21E_CURRENT_BOX = 0x2D11,

	G20E_BOX_1 = 0x4000,
	G20E_BOX_8 = 0x6000,
};

G2Box::G2Box(Generation2* gen, unsigned box)
	: GBGroup<G2BasePokemon>(gen)
{
	uint8_t* start = gen->ram();
	switch (gen->version()) {
	case Game::G20_GOLD | Game::JAPANESE:
	case Game::G20_SILVER | Game::JAPANESE:
		if (box == (gen->ram()[G20J_CURRENT_BOX_ID] & 0xF)) {
			start += G20J_CURRENT_BOX;
		} else if (box < 6) {
			start += G20E_BOX_1 + box * G20J_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G20E_BOX_8 + (box - 6) * G20J_BOX_SIZE;
		} else {
			start += G20J_CURRENT_BOX;
		}
		m_name = gen->gameTextToUTF8(&gen->ram()[G20J_BOX_NAMES + 9 * box], 9);
		setNameLength(6);
		break;
	case Game::G20_GOLD | Game::ENGLISH:
	case Game::G20_SILVER | Game::ENGLISH:
	default:
		if (box == (gen->ram()[G20E_CURRENT_BOX_ID] & 0xF)) {
			start += G20E_CURRENT_BOX;
		} else if (box < 7) {
			start += G20E_BOX_1 + box * G20E_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G20E_BOX_8 + (box - 7) * G20E_BOX_SIZE;
		} else {
			start += G20E_CURRENT_BOX;
		}
		m_name = gen->gameTextToUTF8(&gen->ram()[G20E_BOX_NAMES + 9 * box], 9);
		break;
	case Game::G21_CRYSTAL | Game::ENGLISH:
		if (box == (gen->ram()[G21E_CURRENT_BOX_ID] & 0xF)) {
			start += G21E_CURRENT_BOX;
		} else if (box < 7) {
			start += G20E_BOX_1 + box * G20E_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G20E_BOX_8 + (box - 7) * G20E_BOX_SIZE;
		} else {
			start += G21E_CURRENT_BOX;
		}
		m_name = gen->gameTextToUTF8(&gen->ram()[G21E_BOX_NAMES + 9 * box], 9);
		break;
	}

	setStart(start);
}

unsigned G2Box::capacity() const {
	if ((m_gen->version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		return 30;
	}
	return 20;
}

std::string G2Box::name() const {
	return m_name;
}
