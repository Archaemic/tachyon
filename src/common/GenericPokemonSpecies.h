#ifndef PTXN_GENERIC_POKEMON_SPECIES_H
#define PTXN_GENERIC_POKEMON_SPECIES_H

#include "base.h"

template <typename T>
class GenericPokemonSpecies : public PokemonSpecies {
public:
	GenericPokemonSpecies(const T*);

	virtual Id id() const override;
	virtual unsigned baseHp() const override;
	virtual unsigned baseAttack() const override;
	virtual unsigned baseDefense() const override;
	virtual unsigned baseSpeed() const override;
	virtual unsigned baseSpecialAttack() const override;
	virtual unsigned baseSpecialDefense() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;
	virtual uint8_t genderRatio() const override;
	virtual PokemonSpecies::GrowthRate growthRate() const override;

protected:
	virtual Type mapType(unsigned) const = 0;

private:
	const T* m_data;
};

template <typename T>
GenericPokemonSpecies<T>::GenericPokemonSpecies(const T* data)
	: m_data(data)
{
}

template <typename T>
PokemonSpecies::Id GenericPokemonSpecies<T>::id() const {
	return (PokemonSpecies::Id) m_data->species;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseHp() const {
	return m_data->hp;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseAttack() const {
	return m_data->attack;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseDefense() const {
	return m_data->defense;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseSpeed() const {
	return m_data->speed;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseSpecialAttack() const {
	return m_data->specialAttack;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseSpecialDefense() const {
	return m_data->specialDefense;
}

template <typename T>
PokemonSpecies::GrowthRate GenericPokemonSpecies<T>::growthRate() const {
	switch (m_data->growthRate) {
	case 0:
		return PokemonSpecies::LEVEL_MEDIUM_FAST;
	case 1:
		return PokemonSpecies::LEVEL_ERRATIC;
	case 2:
		return PokemonSpecies::LEVEL_FLUCTUATING;
	case 3:
		return PokemonSpecies::LEVEL_MEDIUM_SLOW;
	case 4:
		return PokemonSpecies::LEVEL_FAST;
	case 5:
		return PokemonSpecies::LEVEL_SLOW;
	default:
		return PokemonSpecies::LEVEL_MEDIUM_FAST;
	}
}

template <typename T>
Type GenericPokemonSpecies<T>::type1() const {
	return mapType(m_data->type1);
}

template <typename T>
Type GenericPokemonSpecies<T>::type2() const {
	return mapType(m_data->type2);
}

template <typename T>
uint8_t GenericPokemonSpecies<T>::genderRatio() const {
	return m_data->genderRatio;
}

#endif
