#ifndef PTXN_GEN_1_PRIVATE_H
#define PTXN_GEN_1_PRIVATE_H

#include "gen1.h"

struct G1MoveSet {
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
};

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
	uint8_t pokemonId;
	uint16_t currentHp;
	uint8_t displayLevel;
	uint8_t status;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	G1MoveSet moves;
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
	G1MoveSet pp;
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
	G1MoveSet baseMoveSet;
	uint8_t growthRate;
	G1TMSet tmFlags;
	uint8_t padding;
} __attribute__((packed));

class G1BasePokemon : public PokemonImpl {
public:
	G1BasePokemon(const Generation1& gen, uint8_t* data, uint8_t* name, uint8_t* ot);

	virtual const wchar_t* name() const override;
	virtual PokemonSpecies species() const override;
	virtual const wchar_t* otName() const override;
	virtual uint16_t otId() const override;
	virtual unsigned xp() const override;
	virtual unsigned currentHp() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;

	virtual unsigned maxHp() const override;
	virtual unsigned attack() const override;
	virtual unsigned defense() const override;
	virtual unsigned speed() const override;
	virtual unsigned specialAttack() const override;
	virtual unsigned specialDefense() const override;

	virtual unsigned ivHp() const override;
	virtual unsigned ivAttack() const override;
	virtual unsigned ivDefense() const override;
	virtual unsigned ivSpeed() const override;
	virtual unsigned ivSpecialAttack() const override;
	virtual unsigned ivSpecialDefense() const override;

	virtual unsigned evHp() const override;
	virtual unsigned evAttack() const override;
	virtual unsigned evDefense() const override;
	virtual unsigned evSpeed() const override;
	virtual unsigned evSpecialAttack() const override;
	virtual unsigned evSpecialDefense() const override;

	unsigned stat(unsigned iv, unsigned base, unsigned ev) const;

private:
	const Generation1& m_gen;
	G1BasePokemonData* m_data;
	wchar_t m_ot[8];
	wchar_t m_name[11];
};

class G1PartyPokemon : public G1BasePokemon {
public:
	G1PartyPokemon(const Generation1& gen, uint8_t* data, uint8_t* name, uint8_t* ot);

	virtual unsigned level() const override;
	virtual unsigned maxHp() const override;
	virtual unsigned attack() const override;
	virtual unsigned defense() const override;
	virtual unsigned speed() const override;
	virtual unsigned specialAttack() const override;
	virtual unsigned specialDefense() const override;

private:
	G1PartyPokemonData* m_data;
};

class G1PokemonSpecies : public PokemonSpeciesImpl {
public:
	G1PokemonSpecies(const Generation1& gen, G1PokemonBaseStats* data);

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
	const Generation1& m_gen;
	G1PokemonBaseStats* m_data;
};

#endif
