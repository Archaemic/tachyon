#include "gen2/G2Party.h"

#include "gen2/Generation2.h"

G2Party::G2Party(Generation2* gen)
	: GBGroup<G2PartyPokemon>(gen)
{
	setStart(&gen->ram()[gen->offsets()->partyPokemon]);
	if ((gen->version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		setNameLength(6);
	}
}

unsigned G2Party::capacity() const {
	return 6;
}

std::string G2Party::name() const {
	return "Party";
}
