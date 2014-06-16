#ifndef PTXN_G1_POKEMON_SPECIES_H
#define PTXN_G1_POKEMON_SPECIES_H

#include "common/GameBoyGame.h"
#include "common/GenericPokemonSpecies.h"

struct G1TMSet {
public:
	G1TMSet();
	G1TMSet(uint64_t tmset);

	bool containsTM(int tm) const;
	bool containsHM(int hm) const;

private:
	uint8_t m_set[7];
} __attribute__((packed));

class Sprite;

struct G1PokemonBaseStats {
	uint8_t species;
	uint8_t hp;
	uint8_t attack;
	uint8_t defense;
	uint8_t speed;
	uint8_t special;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	uint8_t baseExpYield;
	uint8_t spriteDim;
	uint16_t frontSprite;
	uint16_t backSprite;
	GBMoveSet baseMoveSet;
	uint8_t growthRate;
	G1TMSet tmFlags;
	uint8_t padding;
} __attribute__((packed));

class G1PokemonSpecies : public GenericPokemonSpecies<G1PokemonBaseStats> {
public:
	G1PokemonSpecies(const G1PokemonBaseStats* data);

	virtual const MultipaletteSprite* frontSprite() const override;

private:
	virtual Type mapType(unsigned unmapped) const override;
};

template <> unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialAttack() const;
template <> unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialDefense() const;
template <> uint8_t GenericPokemonSpecies<G1PokemonBaseStats>::genderRatio() const;

#endif
