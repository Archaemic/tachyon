#ifndef PTXN_GEN_3_PRIVATE_H
#define PTXN_GEN_3_PRIVATE_H

#include "gen3.h"

struct G3PokemonGrowth {
	uint16_t species;
	uint16_t heldItem;
	uint32_t xp;
	uint8_t pp;
	uint8_t friendship;
	uint16_t unknown;
} __attribute__((packed));

struct G3PokemonAttacks {
	uint16_t moves[4];
	uint8_t pp[4];
} __attribute__((packed));

struct G3PokemonEVs {
	uint8_t hp;
	uint8_t attack;
	uint8_t defense;
	uint8_t speed;
	uint8_t specialAttack;
	uint8_t specialDefense;
	uint8_t coolness;
	uint8_t beauty;
	uint8_t cuteness;
	uint8_t smartness;
	uint8_t toughness;
	uint8_t feel;
} __attribute__((packed));

struct G3PokemonMisc {
	uint8_t pokerus;
	uint8_t met;
	uint16_t origin;
	uint32_t ivHp : 5;
	uint32_t ivAttack : 5;
	uint32_t ivDefense : 5;
	uint32_t ivSpeed : 5;
	uint32_t ivSpecialAttack : 5;
	uint32_t ivSpecialDefense : 5;
	uint32_t egg : 1;
	uint32_t ability : 1;
	uint32_t cool : 3;
	uint32_t beauty : 3;
	uint32_t cute : 3;
	uint32_t smart : 3;
	uint32_t tough : 3;
	uint32_t champion : 1;
	uint32_t winning : 1;
	uint32_t victory : 1;
	uint32_t artist : 1;
	uint32_t effort : 1;
	uint32_t special1 : 1;
	uint32_t special2 : 1;
	uint32_t special3 : 1;
	uint32_t special4 : 1;
	uint32_t special5 : 1;
	uint32_t special6 : 1;
	uint32_t padding : 4;
	uint32_t obedience : 1;
} __attribute__((packed));

union G3PokemonField {
	G3PokemonGrowth g;
	G3PokemonAttacks a;
	G3PokemonEVs e;
	G3PokemonMisc m;
	uint32_t raw[3];
} __attribute__((packed));

struct G3PokemonSubdata {
	G3PokemonField f0;
	G3PokemonField f1;
	G3PokemonField f2;
	G3PokemonField f3;
} __attribute__((packed));

struct G3BasePokemonData {
	uint32_t personality;
	uint32_t otId;
	uint8_t name[10];
	uint16_t language;
	uint8_t otName[7];
	uint8_t markings;
	uint16_t checksum;
	uint16_t padding;
	G3PokemonSubdata data;

	G3PokemonGrowth* growth();
	G3PokemonAttacks* attacks();
	G3PokemonEVs* evs();
	G3PokemonMisc* misc();
} __attribute__((packed));

struct G3PartyPokemonData : public G3BasePokemonData {
	uint32_t status;
	uint8_t level;
	uint8_t pokerus;
	uint16_t currentHp;
	uint16_t maxHp;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t specialAttack;
	uint16_t specialDefense;
} __attribute__((packed));

struct G3PokemonBaseStats {
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
	uint16_t evYieldHp : 2;
	uint16_t evYieldAttack : 2;
	uint16_t evYieldDefense : 2;
	uint16_t evYieldSpeed : 2;
	uint16_t evYieldSpecialAttack : 2;
	uint16_t evYieldSpecialDefense : 2;
	uint16_t item1;
	uint16_t item2;
	uint8_t gender;
	uint8_t eggCycles;
	uint8_t baseFriendship;
	uint8_t growthRate;
	uint8_t eggGroup1;
	uint8_t eggGroup2;
	uint8_t ability1;
	uint8_t ability2;
	uint8_t safariZoneRate;
	uint8_t color : 7;
	uint8_t flip : 1;
	uint16_t padding;
} __attribute__((packed));

class G3PartyPokemon : public Pokemon {
public:
	G3PartyPokemon(Generation3* gen, uint8_t* data);

	virtual PokemonSpecies* species() const override;

	virtual uint16_t otId() const override;
	virtual uint16_t otSecretId() const override;
	virtual unsigned xp() const override;
	virtual unsigned currentHp() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;

	virtual unsigned level() const override;
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

	virtual unsigned move1() const override;
	virtual unsigned move2() const override;
	virtual unsigned move3() const override;
	virtual unsigned move4() const override;

	unsigned stat(unsigned iv, unsigned base, unsigned ev) const;
	void decrypt();

private:
	Generation3* m_gen;
	std::unique_ptr<G3PartyPokemonData> m_data;
	bool m_dirty;
};

class G3PokemonSpecies : public PokemonSpecies {
public:
	G3PokemonSpecies(const G3PokemonBaseStats* data, PokemonSpecies::Id id);

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
	const G3PokemonBaseStats* m_data;
	PokemonSpecies::Id m_id;
};

class G3Party : public Group {
public:
	G3Party(Generation3* gen);

	virtual std::unique_ptr<Pokemon> at(unsigned i) override;
	virtual unsigned length() const override;

private:
	Generation3* m_gen;
	uint8_t* m_start;
};

#endif
