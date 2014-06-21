#include "gen1/G1Party.h"

#include "gen1/Generation1.h"

enum {
	G10J_PARTY_POKEMON = 0x2ED5,
	G10E_PARTY_POKEMON = 0x2F2C,
};

G1Party::G1Party(Generation1* gen)
	: GBGroup<G1PartyPokemon>(gen)
{
	switch (gen->version() & Game::MASK_LOCALIZATION) {
	case Game::JAPANESE:
		setStart(&gen->ram()[G10J_PARTY_POKEMON]);
		setNameLength(6);
		break;
	case Game::ENGLISH:
	default:
		setStart(&gen->ram()[G10E_PARTY_POKEMON]);
		break;
	}
}

unsigned G1Party::capacity() const {
	return 6;
}

std::string G1Party::name() const {
	return "Party";
}
