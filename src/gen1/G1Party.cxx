#include "gen1/G1Party.h"

#include "gen1/Generation1.h"

enum {
	G10E_PARTY_POKEMON = 0x2F2C,
};

G1Party::G1Party(Generation1* gen)
	: GBGroup<G1PartyPokemon>(gen)
{
	setStart(&gen->ram()[G10E_PARTY_POKEMON]);
}

unsigned G1Party::capacity() const {
	return 6;
}

std::string G1Party::name() const {
	return "Party";
}
