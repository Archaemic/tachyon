#ifndef PTXN_GEN_1_H
#define PTXN_GEN_1_H

#include "base.h"

enum {
	SIZE_GEN_1_SAV = 0x8000,
	SIZE_GEN_1_ROM = 0x100000,
};

class Generation1 : public Game {
public:
	enum Box {
		BOX_CURRENT,
		BOX_01,
		BOX_02,
		BOX_03,
		BOX_04,
		BOX_05,
		BOX_06,
		BOX_07,
		BOX_08,
		BOX_09,
		BOX_10,
		BOX_11,
		BOX_12
	};

	Generation1(uint8_t* memory, const uint8_t* rom);

	virtual const wchar_t* trainerName() const override;

	virtual Pokemon partyPokemon(int i) override;
	virtual unsigned nPartyPokemon() const override;
	virtual Pokemon boxPokemon(int box, int i) override;
	virtual unsigned nBoxPokemon(int box) const override;

	virtual Version version() const override;

private:
	const static wchar_t charMapGen1En[0x100];

	wchar_t m_trainerName[8];

public:
	static void gameTextToWchar(wchar_t* out, const uint8_t* gameText, size_t len);
};

#endif
