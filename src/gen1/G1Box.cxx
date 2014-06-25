#include "gen1/G1Box.h"

#include "gen1/Generation1.h"

#include <sstream>

enum {
	G10_BOX_LOW = 0x4000,
	G10_BOX_HIGH = 0x6000,
};

G1Box::G1Box(Generation1* gen, unsigned box)
	: GBGroup<G1BasePokemon>(gen)
	, m_box(box)
{
	uint8_t* start = gen->ram();
	if (box == (start[gen->offsets()->currentBoxId] & 0xF)) {
		start += gen->offsets()->currentBox;
	} else if (box < gen->offsets()->boxHigh) {
		start += G10_BOX_LOW + box * gen->offsets()->boxSize;
	} else if (box < gen->numBoxes()) {
		start += G10_BOX_HIGH + (box - gen->offsets()->boxHigh) * gen->offsets()->boxSize;
	} else {
		start += gen->offsets()->currentBox;
	}
	if ((gen->version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		setNameLength(6);
	}
	setStart(start);
}

unsigned G1Box::capacity() const {
	if ((m_gen->version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		return 30;
	}
	return 20;
}

std::string G1Box::name() const {
	std::stringstream name;
	name << "Box ";
	name << (m_box + 1);
	return name.str();
}
