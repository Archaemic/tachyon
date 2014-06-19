#include "gen2/G2PokemonSpecies.h"

#include "common/GameBoyGame.h"
#include "gen2/Generation2.h"

G2PokemonSpecies::G2PokemonSpecies(const G2PokemonBaseStats* data, PokemonSpecies::Forme forme)
	: GenericPokemonSpecies<G2PokemonBaseStats>(data)
	, m_forme(forme)
{
}

PokemonSpecies::Forme G2PokemonSpecies::forme() const {
	return m_forme;
}

Type G2PokemonSpecies::mapType(unsigned unmapped) const {
	return GameBoyGame::typeMapping[static_cast<uint8_t>(unmapped)];
}
