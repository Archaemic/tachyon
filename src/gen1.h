#ifndef PTXN_GEN_1_H
#define PTXN_GEN_1_H

#include "base.h"

enum {
	SIZE_GEN_1 = 0x8000,
};

struct G1BasePokemonData;
struct G1PartyPokemonData;

class G1BasePokemon : public PokemonImpl {
public:
	G1BasePokemon(uint8_t* data, uint8_t* name, uint8_t* ot);

	virtual const wchar_t* name() const override;
	virtual Pokemon::Id species() const override;
	virtual const wchar_t* otName() const override;
	virtual uint16_t otId() const override;
	virtual unsigned xp() const override;
	virtual unsigned currentHp() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;

private:
	G1BasePokemonData* m_data;
	wchar_t m_ot[8];
	wchar_t m_name[11];
};

class G1PartyPokemon : public G1BasePokemon {
public:
	G1PartyPokemon(uint8_t* data, uint8_t* name, uint8_t* ot);

private:
	G1PartyPokemonData* m_data;
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

	Generation1(uint8_t* memory);

	virtual const wchar_t* trainerName() const;

	virtual Pokemon partyPokemon(int i);
	virtual unsigned nPartyPokemon() const;
	virtual Pokemon boxPokemon(int box, int i);
	virtual unsigned nBoxPokemon(int box) const;

private:
	const static wchar_t charMapGen1En[0x100];

	wchar_t m_trainerName[8];

public:
	static void gameTextToWchar(wchar_t* out, const uint8_t* gameText, size_t len);
};

#endif
