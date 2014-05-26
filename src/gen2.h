#ifndef PTXN_GEN_2_H
#define PTXN_GEN_2_H

#include "gen-gb.h"

enum {
	SIZE_GEN_2_SAV = 0x8000,
	SIZE_GEN_2_ROM = 0x200000,
};

class Generation2 : public GameBoyGame {
public:
	Generation2(uint8_t* memory, const uint8_t* rom);

	virtual std::unique_ptr<Group> party() override;
	virtual std::unique_ptr<Group> box(unsigned box) override;

	virtual Version version() const override;

	virtual PokemonSpecies* species(PokemonSpecies::Id) override;

private:
	const static char charMapGen2En[0x100];
};

#endif
