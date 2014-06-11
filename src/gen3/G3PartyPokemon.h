#ifndef PTXN_G3_PARTY_POKEMON_H
#define PTXN_G3_PARTY_POKEMON_H

#include "gen3/G3BasePokemon.h"

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

class G3PartyPokemon : public G3Pokemon<G3PartyPokemonData> {
public:
	static std::unique_ptr<G3PartyPokemon> copy(Generation3* gen, const Pokemon&);

	G3PartyPokemon(Generation3* gen, G3PartyPokemonData* data);
	G3PartyPokemon(Generation3* gen);

	virtual unsigned level() const override;
	virtual unsigned currentHp() const override;
	virtual unsigned maxHp() const override;
	virtual unsigned attack() const override;
	virtual unsigned defense() const override;
	virtual unsigned speed() const override;
	virtual unsigned specialAttack() const override;
	virtual unsigned specialDefense() const override;
	virtual unsigned pokerusDays() const override;

	virtual bool copy(const Pokemon& other) override;
};

#endif
