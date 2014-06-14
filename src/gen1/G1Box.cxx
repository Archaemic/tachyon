#include "gen1/G1Box.h"

#include "gen1/Generation1.h"

#include <sstream>

enum {
	G1_BOX_SIZE = 1122,

	G10E_CURRENT_BOX_ID = 0x284C,
	G10E_CURRENT_BOX = 0x30C0,
	G10E_BOX_1 = 0x4000,
	G10E_BOX_7 = 0x6000,
};

G1Box::G1Box(Generation1* gen, unsigned box)
	: GBGroup<G1BasePokemon>(gen)
	, m_box(box)
{
	uint8_t* start = gen->ram();
	if (box == (start[G10E_CURRENT_BOX_ID] & 0xF)) {
		start += G10E_CURRENT_BOX;
	} else if (box < 6) {
		start += G10E_BOX_1 + box * G1_BOX_SIZE;
	} else if (box < gen->numBoxes()) {
		start += G10E_BOX_7 + (box - 6) * G1_BOX_SIZE;
	} else {
		start += G10E_CURRENT_BOX;
	}
	setStart(start);
}

unsigned G1Box::capacity() const {
	return 20;
}

std::string G1Box::name() const {
	std::stringstream name;
	name << "Box ";
	name << m_box;
	return name.str();
}
