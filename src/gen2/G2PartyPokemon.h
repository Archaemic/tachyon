#ifndef PTXN_G2_PARTY_POKEMON_H
#define PTXN_G2_PARTY_POKEMON_H

#include "common/GBPartyPokemon.h"
#include "gen2/G2BasePokemon.h"

struct G2PartyPokemonData : public G2BasePokemonData {
	uint8_t status;
	uint8_t padding;
	uint16_t currentHp;
	uint16_t maxHp;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t specialAttack;
	uint16_t specialDefense;
} __attribute__((packed));

typedef GBPartyPokemon<G2PartyPokemonData> G2PartyPokemon;

#endif
