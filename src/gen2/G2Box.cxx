#include "gen2/G2Box.h"

#include "gen2/Generation2.h"

enum {
	G20_BOX_LOW = 0x4000,
	G20_BOX_HIGH = 0x6000,
};

G2Box::G2Box(Generation2* gen, unsigned box)
	: GBGroup<G2BasePokemon>(gen)
{
	uint8_t* start = gen->ram();
	if (box == (gen->ram()[gen->offsets()->currentBoxId] & 0xF)) {
		start += gen->offsets()->currentBox;
	} else if (box < gen->offsets()->boxHigh) {
		start += G20_BOX_LOW + box * gen->offsets()->boxSize;
	} else if (box < gen->numBoxes()) {
		start += G20_BOX_HIGH + (box - gen->offsets()->boxHigh) * gen->offsets()->boxSize;
	} else {
		start += gen->offsets()->currentBox;
	}
	m_name = gen->gameTextToUTF8(&gen->ram()[gen->offsets()->boxNames + 9 * box], 9);

	if ((gen->version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		setNameLength(6);
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
