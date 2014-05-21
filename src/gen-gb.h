#ifndef PTXN_GEN_GB_H
#define PTXN_GEN_GB_H

#include "base.h"

class GameBoyGame : public Game {
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

	GameBoyGame(uint8_t* memory, const uint8_t* rom);

	virtual const wchar_t* trainerName() const override;

private:
	const static wchar_t charMapGBEn[0x100];

protected:
	wchar_t m_trainerName[8];

public:
	static void gameTextToWchar(wchar_t* out, const uint8_t* gameText, size_t len);
};

#endif
