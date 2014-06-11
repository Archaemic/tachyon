#ifndef PTXN_G1_PARTY_POKEMON_H
#define PTXN_G1_PARTY_POKEMON_H

#include "gen-gb-private.h"
#include "gen1/G1BasePokemon.h"

struct G1PartyPokemonData : public G1BasePokemonData {
	uint8_t level;
	uint16_t maxHp;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t special;
} __attribute__((packed));

typedef GBPartyPokemon<G1PartyPokemonData> G1PartyPokemon;

template <> PokemonSpecies* GBPokemon<G1PartyPokemonData>::species() const;
template <> unsigned GBPokemon<G1PartyPokemonData>::pokerusStrain() const;
template <> unsigned GBPokemon<G1PartyPokemonData>::pokerusDays() const;
template <> unsigned GBPartyPokemon<G1PartyPokemonData>::specialAttack() const;
template <> unsigned GBPartyPokemon<G1PartyPokemonData>::specialDefense() const;
template <> bool GBPartyPokemon<G1PartyPokemonData>::copy(const Pokemon& other);

#endif
