#include "gen1/G1Party.h"

#include "gen1/Generation1.h"

G1Party::G1Party(Generation1* gen)
	: GBGroup<G1PartyPokemon>(gen)
{
	setStart(&gen->ram()[gen->offsets()->partyPokemon]);
	if ((gen->version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		setNameLength(6);
	}
}

unsigned G1Party::capacity() const {
	return 6;
}

std::string G1Party::name() const {
	return "Party";
}
