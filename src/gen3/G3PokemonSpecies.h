#ifndef PTXN_G3_POKEMON_SPECIES_H
#define PTXN_G3_POKEMON_SPECIES_H

#include "common/GenericPokemonSpecies.h"

#include <memory>

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
	uint8_t genderRatio;
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

class Generation3;
class Sprite;

class G3PokemonSpecies : public GenericPokemonSpecies<G3PokemonBaseStats> {
public:
	enum {
		UNOWN_BASE = 413
	};

	G3PokemonSpecies(const Generation3* gen, const G3PokemonBaseStats* data, PokemonSpecies::Id id, PokemonSpecies::Forme = PokemonSpecies::FORME_NORMAL);

	virtual PokemonSpecies::Id id() const override;
	virtual Forme forme() const override;

	virtual const MultipaletteSprite* frontSprite() const override;

	const static PokemonSpecies::Id idMapping[440];

private:
	void loadSprites();

	virtual Type mapType(unsigned unmapped) const override;

	const Generation3* m_gen;
	PokemonSpecies::Id m_id;
	PokemonSpecies::Forme m_forme;
	std::unique_ptr<MultipaletteSprite> m_frontSprite;
};

#endif
