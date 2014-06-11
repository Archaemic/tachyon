#include "gen2/G2PokemonSpecies.h"

#include "common/GameBoyGame.h"

G2PokemonSpecies::G2PokemonSpecies(const G2PokemonBaseStats* data)
	: GenericPokemonSpecies<G2PokemonBaseStats>(data)
{
}

Type G2PokemonSpecies::mapType(unsigned unmapped) const {
	return GameBoyGame::typeMapping[static_cast<uint8_t>(unmapped)];
}
