#include "gen1/G1PartyPokemon.h"

template <>
const PokemonSpecies* GBPokemon<G1PartyPokemonData>::species() const {
	return m_gen->species(m_gen->mapId(m_data->species));
}

template <>
unsigned GBPokemon<G1PartyPokemonData>::pokerusStrain() const {
	return 0;
}

template <>
unsigned GBPokemon<G1PartyPokemonData>::pokerusDays() const {
	return 0;
}

template <>
unsigned GBPartyPokemon<G1PartyPokemonData>::specialAttack() const {
	return R16(m_data->special);
}

template <>
unsigned GBPartyPokemon<G1PartyPokemonData>::specialDefense() const {
	return R16(m_data->special);
}

template <>
bool GBPartyPokemon<G1PartyPokemonData>::copy(const Pokemon& other) {
	if (!GBPokemon<G1PartyPokemonData>::copy(other)) {
		return false;
	}

	GBPokemon<G1PartyPokemonData>::m_data->level = GBPokemon<G1PartyPokemonData>::level();
	GBPokemon<G1PartyPokemonData>::m_data->maxHp = R16(GBPokemon<G1PartyPokemonData>::maxHp());
	GBPokemon<G1PartyPokemonData>::m_data->attack = R16(GBPokemon<G1PartyPokemonData>::attack());
	GBPokemon<G1PartyPokemonData>::m_data->defense = R16(GBPokemon<G1PartyPokemonData>::defense());
	GBPokemon<G1PartyPokemonData>::m_data->speed = R16(GBPokemon<G1PartyPokemonData>::speed());
	GBPokemon<G1PartyPokemonData>::m_data->special = R16(GBPokemon<G1PartyPokemonData>::specialAttack());
	return true;
}
