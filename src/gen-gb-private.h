#ifndef PTXN_GEN_GB_PRIVATE_H
#define PTXN_GEN_GB_PRIVATE_H

#include "gen-gb.h"

#define R16(V) (((V) & 0xFF) << 8) | (((V) & 0xFF00) >> 8)
#define R24(V) (((V) & 0xFF) << 16) | ((V) & 0xFF00) | (((V) & 0xFF0000) >> 16)
#define R32(V) (((V) & 0xFF) << 24) | (((V) & 0xFF00) << 8) | (((V) & 0xFF0000) >> 8) | (((V) & 0xFF000000) >> 24)

struct GBMoveSet {
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
};

class GBPokemon : public PokemonImpl {
public:
	virtual unsigned maxHp() const override;
	virtual unsigned attack() const override;
	virtual unsigned defense() const override;
	virtual unsigned speed() const override;
	virtual unsigned specialAttack() const override;
	virtual unsigned specialDefense() const override;

	unsigned stat(unsigned iv, unsigned base, unsigned ev) const;
};

#endif
