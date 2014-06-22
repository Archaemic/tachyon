#include "gen1/G1Box.h"

#include "gen1/Generation1.h"

#include <sstream>

enum {
	G10J_BOX_SIZE = 1382,
	G10E_BOX_SIZE = 1122,

	G10J_CURRENT_BOX_ID = 0x2842,
	G10J_CURRENT_BOX = 0x302D,

	G10E_CURRENT_BOX_ID = 0x284C,
	G10E_CURRENT_BOX = 0x30C0,

	G10_BOX_LOW = 0x4000,
	G10_BOX_HIGH = 0x6000,
};

G1Box::G1Box(Generation1* gen, unsigned box)
	: GBGroup<G1BasePokemon>(gen)
	, m_box(box)
{
	uint8_t* start = gen->ram();
	switch (gen->version() & Game::MASK_LOCALIZATION) {
	case Game::JAPANESE:
		if (box == (start[G10J_CURRENT_BOX_ID] & 0xF)) {
			start += G10J_CURRENT_BOX;
		} else if (box < 4) {
			start += G10_BOX_LOW + box * G10J_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G10_BOX_HIGH + (box - 4) * G10J_BOX_SIZE;
		} else {
			start += G10J_CURRENT_BOX;
		}
		setNameLength(6);
		break;
	case Game::ENGLISH:
		if (box == (start[G10E_CURRENT_BOX_ID] & 0xF)) {
			start += G10E_CURRENT_BOX;
		} else if (box < 6) {
			start += G10_BOX_LOW + box * G10E_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G10_BOX_HIGH + (box - 6) * G10E_BOX_SIZE;
		} else {
			start += G10E_CURRENT_BOX;
		}
		break;
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
