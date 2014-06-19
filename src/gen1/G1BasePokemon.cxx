#include "gen1/G1BasePokemon.h"

template <>
const PokemonSpecies* GBPokemon<G1BasePokemonData>::species() const {
	return m_gen->species(m_gen->mapId(m_data->species));
}

template <>
unsigned GBPokemon<G1BasePokemonData>::currentHp() const {
	return R16(m_data->currentHp);
}

template <>
Type GBPokemon<G1BasePokemonData>::type1() const {
	return GameBoyGame::typeMapping[m_data->type1];
}

template <>
Type GBPokemon<G1BasePokemonData>::type2() const {
	return GameBoyGame::typeMapping[m_data->type2];
}

template <>
unsigned GBPokemon<G1BasePokemonData>::pokerusStrain() const {
	return 0;
}

template <>
unsigned GBPokemon<G1BasePokemonData>::pokerusDays() const {
	return 0;
}
