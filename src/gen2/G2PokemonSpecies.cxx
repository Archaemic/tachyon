#include "gen2/G2PokemonSpecies.h"

#include "common/GameBoyGame.h"
#include "gen2/Generation2.h"

G2PokemonSpecies::G2PokemonSpecies(const Generation2* gen, const G2PokemonBaseStats* data)
	: GenericPokemonSpecies<G2PokemonBaseStats>(data)
	, m_frontSprite(gen->frontSprite(static_cast<PokemonSpecies::Id>(data->species), data->spriteDim & 0xF))
{
}

const MultipaletteSprite* G2PokemonSpecies::frontSprite() const
{
	return m_frontSprite.get();
}

Type G2PokemonSpecies::mapType(unsigned unmapped) const {
	return GameBoyGame::typeMapping[static_cast<uint8_t>(unmapped)];
}
