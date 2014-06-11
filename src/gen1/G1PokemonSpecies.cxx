#include "gen1/G1PokemonSpecies.h"

template <>
unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialAttack() const {
	return m_data->special;
}

template <>
unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialDefense() const {
	return m_data->special;
}

template <>
uint8_t GenericPokemonSpecies<G1PokemonBaseStats>::genderRatio() const {
	if (id() == PokemonSpecies::NIDORAN_F) {
		return 0xFE;
	}
	if (id() == PokemonSpecies::NIDORAN_M) {
		return 0x00;
	}
	return 0xFF;
}

G1PokemonSpecies::G1PokemonSpecies(const G1PokemonBaseStats* data)
	: GenericPokemonSpecies<G1PokemonBaseStats>(data)
{
}

Type G1PokemonSpecies::mapType(unsigned unmapped) const {
	return typeMapping[static_cast<uint8_t>(unmapped)];
}
