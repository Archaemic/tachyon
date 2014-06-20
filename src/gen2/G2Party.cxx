#include "gen2/G2Party.h"

#include "gen2/Generation2.h"

enum {
	G20_PARTY_POKEMON = 0x288A,
	G21_PARTY_POKEMON = 0x2865,
};

G2Party::G2Party(Generation2* gen)
	: GBGroup<G2PartyPokemon>(gen)
{
	switch (gen->version() & Game::MASK_GAME) {
	case Game::G20_GOLD:
	case Game::G20_SILVER:
	default:
		setStart(&gen->ram()[G20_PARTY_POKEMON]);
		break;
	case Game::G21_CRYSTAL:
		setStart(&gen->ram()[G21_PARTY_POKEMON]);
		break;
	}
}

unsigned G2Party::capacity() const {
	return 6;
}

std::string G2Party::name() const {
	return "Party";
}
