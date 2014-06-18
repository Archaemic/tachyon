#ifndef PTXN_G2_POKEMON_SPECIES_H
#define PTXN_G2_POKEMON_SPECIES_H

#include "common/GenericPokemonSpecies.h"

#include <memory>

struct G2TMSet {
public:
	G2TMSet();
	G2TMSet(uint64_t tmset);

	bool containsTM(int tm) const;
	bool containsHM(int hm) const;

private:
	uint8_t m_set[8];
} __attribute__((packed));

class Generation2;
class Sprite;

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

class G2PokemonSpecies : public GenericPokemonSpecies<G2PokemonBaseStats> {
public:
	G2PokemonSpecies(const Generation2* gen, const G2PokemonBaseStats* data, Forme forme = FORME_NORMAL);

	virtual Forme forme() const override;

	virtual const MultipaletteSprite* frontSprite() const override;

private:
	void loadSprites();

	virtual Type mapType(unsigned unmapped) const override;

	const Generation2* m_gen;
	Forme m_forme;
	std::unique_ptr<MultipaletteSprite> m_frontSprite;
};

#endif
