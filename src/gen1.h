#ifndef PTXN_GEN_1_H
#define PTXN_GEN_1_H

#include "gen-gb.h"

enum {
	SIZE_GEN_1_SAV = 0x8000,
	SIZE_GEN_1_ROM = 0x100000,
};

class Generation1 : public GameBoyGame {
public:
	Generation1(uint8_t* memory, const uint8_t* rom);

	virtual std::unique_ptr<Pokemon> partyPokemon(int i) override;
	virtual unsigned nPartyPokemon() const override;
	virtual std::unique_ptr<Pokemon> boxPokemon(int box, int i) override;
	virtual unsigned nBoxPokemon(int box) const override;

	virtual Version version() const override;

	virtual PokemonSpecies* species(PokemonSpecies::Id) override;

private:
	const static char charMapGen1En[0x100];
};

#endif
