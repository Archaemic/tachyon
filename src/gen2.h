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

	virtual Pokemon partyPokemon(int i) override;
	virtual unsigned nPartyPokemon() const override;
	virtual Pokemon boxPokemon(int box, int i) override;
	virtual unsigned nBoxPokemon(int box) const override;

	virtual Version version() const override;

private:
	const static wchar_t charMapGen2En[0x100];

	wchar_t m_trainerName[8];
};

#endif
