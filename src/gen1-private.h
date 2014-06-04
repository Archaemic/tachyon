#ifndef PTXN_GEN_1_PRIVATE_H
#define PTXN_GEN_1_PRIVATE_H

#include "gen1.h"
#include "gen-gb-private.h"

struct G1TMSet {
public:
	G1TMSet();
	G1TMSet(uint64_t tmset);

	bool containsTM(int tm) const;
	bool containsHM(int hm) const;

private:
	uint8_t m_set[7];
} __attribute__((packed));

struct G1BasePokemonData {
	const static int GENERATION = 1;

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

struct G1PartyPokemonData : public G1BasePokemonData {
	uint8_t level;
	uint16_t maxHp;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t special;
} __attribute__((packed));

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

typedef GBPokemon<G1BasePokemonData> G1BasePokemon;
typedef GBPartyPokemon<G1PartyPokemonData> G1PartyPokemon;

class G1PokemonSpecies : public GenericPokemonSpecies<G1PokemonBaseStats> {
public:
	G1PokemonSpecies(const G1PokemonBaseStats* data);

private:
	virtual Type mapType(unsigned unmapped) const override;
};

class G1Party : public GBGroup<G1PartyPokemon> {
public:
	G1Party(Generation1* gen);

	virtual unsigned capacity() const override;
};

class G1Box : public GBGroup<G1BasePokemon> {
public:
	G1Box(Generation1* gen, GameBoyGame::Box box);

	virtual unsigned capacity() const override;
};

#endif
