#include "gen2/G2Party.h"

#include "gen2/Generation2.h"

enum {
	G20J_PARTY_POKEMON = 0x283E,
	G20E_PARTY_POKEMON = 0x288A,
	G21E_PARTY_POKEMON = 0x2865,
};

G2Party::G2Party(Generation2* gen)
	: GBGroup<G2PartyPokemon>(gen)
{
	switch (gen->version()) {
	case Game::G20_GOLD | Game::JAPANESE:
	case Game::G20_SILVER | Game::JAPANESE:
		setStart(&gen->ram()[G20J_PARTY_POKEMON]);
		setOtNameLength(6);
		break;
	case Game::G20_GOLD | Game::ENGLISH:
	case Game::G20_SILVER | Game::ENGLISH:
	default:
		setStart(&gen->ram()[G20E_PARTY_POKEMON]);
		break;
	case Game::G21_CRYSTAL | Game::ENGLISH:
		setStart(&gen->ram()[G21E_PARTY_POKEMON]);
		break;
	}
}

unsigned G2Party::capacity() const {
	return 6;
}

std::string G2Party::name() const {
	return "Party";
}
