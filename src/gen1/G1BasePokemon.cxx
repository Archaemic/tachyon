#include "gen1/G1BasePokemon.h"

template <>
PokemonSpecies* GBPokemon<G1BasePokemonData>::species() const {
	const uint8_t* idMapping = &m_gen->rom()[G10E_ID_MAPPING];
	PokemonSpecies::Id id =  static_cast<PokemonSpecies::Id>(idMapping[m_data->species]);
	return m_gen->species(id);
}

template <>
unsigned GBPokemon<G1BasePokemonData>::currentHp() const {
	return R16(m_data->currentHp);
}

template <>
Type GBPokemon<G1BasePokemonData>::type1() const {
	return typeMapping[m_data->type1];
}

template <>
Type GBPokemon<G1BasePokemonData>::type2() const {
	return typeMapping[m_data->type2];
}

template <>
unsigned GBPokemon<G1BasePokemonData>::pokerusStrain() const {
	return 0;
}

template <>
unsigned GBPokemon<G1BasePokemonData>::pokerusDays() const {
	return 0;
}
