#include "gen2/G2Party.h"

#include "gen2/Generation2.h"

enum {
	G20E_PARTY_POKEMON = 0x288A,
	G21E_PARTY_POKEMON = 0x2865,
};

G2Party::G2Party(Generation2* gen)
	: GBGroup<G2PartyPokemon>(gen)
{
	switch (gen->version()) {
	case Game::G20E_GOLD:
	case Game::G20J_GOLD:
	case Game::G20E_SILVER:
	case Game::G20J_SILVER:
	default:
		setStart(&gen->ram()[G20E_PARTY_POKEMON]);
		break;
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
		setStart(&gen->ram()[G21E_PARTY_POKEMON]);
		break;
	}
}

unsigned G2Party::capacity() const {
	return 6;
}
