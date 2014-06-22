#ifndef PTXN_G1_BASE_POKEMON
#define PTXN_G1_BASE_POKEMON

#include "gb/GBPokemon.h"

struct G1BasePokemonData {
	const static int GENERATION = 0x100;

	uint8_t species;
	uint16_t currentHp;
	uint8_t level;
	uint8_t status;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	GBMoveSet moves;
	uint16_t otId;
	uint32_t xp : 24;
	uint16_t evHp;
	uint16_t evAttack;
	uint16_t evDefense;
	uint16_t evSpeed;
	uint16_t evSpecial;
	uint8_t ivDefense : 4;
	uint8_t ivAttack : 4;
	uint8_t ivSpecial : 4;
	uint8_t ivSpeed : 4;
	GBMoveSet pp;
} __attribute__((packed));

typedef GBPokemon<G1BasePokemonData> G1BasePokemon;

template <> const PokemonSpecies* GBPokemon<G1BasePokemonData>::species() const;
template <> unsigned GBPokemon<G1BasePokemonData>::currentHp() const;
template <> Type GBPokemon<G1BasePokemonData>::type1() const;
template <> Type GBPokemon<G1BasePokemonData>::type2() const;
template <> unsigned GBPokemon<G1BasePokemonData>::pokerusStrain() const;
template <> unsigned GBPokemon<G1BasePokemonData>::pokerusDays() const;

#endif
