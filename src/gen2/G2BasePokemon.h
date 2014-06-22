#ifndef PTXN_G2_BASE_POKEMON_H
#define PTXN_G2_BASE_POKEMON_H

#include "gb/GBPokemon.h"

struct G2BasePokemonData {
	const static int GENERATION = 0x200;

	uint8_t species;
	uint8_t heldItem;
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
	uint8_t friendship;
	uint8_t pokerus;
	uint16_t caughtData;
	uint8_t level;
} __attribute__((packed));

typedef GBPokemon<G2BasePokemonData> G2BasePokemon;

#endif
