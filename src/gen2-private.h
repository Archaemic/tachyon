#ifndef PTXN_GEN_2_PRIVATE_H
#define PTXN_GEN_2_PRIVATE_H

#include "gen2.h"
#include "gen-gb-private.h"

struct G2TMSet {
public:
	G2TMSet();
	G2TMSet(uint64_t tmset);

	bool containsTM(int tm) const;
	bool containsHM(int hm) const;

private:
	uint8_t m_set[8];
} __attribute__((packed));

struct G2BasePokemonData {
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

struct G2PokemonBaseStats {
	uint8_t species;
	uint8_t hp;
	uint8_t attack;
	uint8_t defense;
	uint8_t speed;
	uint8_t specialAttack;
	uint8_t specialDefense;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	uint8_t baseExpYield;
	uint8_t heldItem1;
	uint8_t heldItem2;
	uint8_t genderRatio;
	uint8_t unknown1;
	uint8_t eggCycles;
	uint8_t unknown2;
	uint8_t spriteDim;
	uint32_t padding;
	uint8_t growthRate;
	uint8_t eggGroups;
	G2TMSet tmFlags;
} __attribute__((packed));

class G2BasePokemon : public GBPokemon<G2BasePokemonData> {
public:
	G2BasePokemon(Generation2* gen, uint8_t* data, uint8_t* name, uint8_t* ot);
};

class G2PartyPokemon : public GBPartyPokemon<G2PartyPokemonData> {
public:
	G2PartyPokemon(Generation2* gen, uint8_t* data, uint8_t* name, uint8_t* ot);
};

class G2PokemonSpecies : public PokemonSpecies {
public:
	G2PokemonSpecies(const G2PokemonBaseStats* data);

	virtual PokemonSpecies::Id id() const override;
	virtual unsigned baseHp() const override;
	virtual unsigned baseAttack() const override;
	virtual unsigned baseDefense() const override;
	virtual unsigned baseSpeed() const override;
	virtual unsigned baseSpecialAttack() const override;
	virtual unsigned baseSpecialDefense() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;
	virtual PokemonSpecies::GrowthRate growthRate() const override;

private:
	const G2PokemonBaseStats* m_data;
};

class G2Party : public Group {
public:
	G2Party(Generation2* gen);

	virtual std::unique_ptr<Pokemon> at(unsigned i) override;
	virtual unsigned length() const override;

private:
	Generation2* m_gen;
	uint8_t* m_start;
};

class G2Box : public Group {
public:
	G2Box(Generation2* gen, GameBoyGame::Box box);

	virtual std::unique_ptr<Pokemon> at(unsigned i) override;
	virtual unsigned length() const override;

private:
	Generation2* m_gen;
	uint8_t* m_start;
};

#endif
