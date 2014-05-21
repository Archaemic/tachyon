#include "gen-gb-private.h"

#include <cmath>

unsigned GBPokemon::maxHp() const {
	PokemonSpecies sp = species();
	return (ivHp() + sp.baseHp() + int(sqrt(evHp())) / 8 + 50) * level() / 50 + 10;
}

unsigned GBPokemon::attack() const {
	PokemonSpecies sp = species();
	return stat(ivAttack(), sp.baseAttack(), evAttack());
}

unsigned GBPokemon::defense() const {
	PokemonSpecies sp = species();
	return stat(ivDefense(), sp.baseDefense(), evDefense());
}

unsigned GBPokemon::speed() const {
	PokemonSpecies sp = species();
	return stat(ivSpeed(), sp.baseSpeed(), evSpeed());
}

unsigned GBPokemon::specialAttack() const {
	PokemonSpecies sp = species();
	return stat(ivSpecialAttack(), sp.baseSpecialAttack(), evSpecialAttack());
}

unsigned GBPokemon::specialDefense() const {
	PokemonSpecies sp = species();
	return stat(ivSpecialDefense(), sp.baseSpecialDefense(), evSpecialDefense());
}

unsigned GBPokemon::stat(unsigned iv, unsigned base, unsigned ev) const {
	return (iv + base + int(sqrt(ev)) / 8) * level() / 50 + 5;
}

const wchar_t GameBoyGame::charMapGBEn[0x100] = {
	// 0x0X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x1X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x2X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x3X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x4X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x5X
	L'\0', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x6X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x7X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L' ',

	// 0x8X
	L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H',
	L'I', L'J', L'K', L'L', L'M', L'N', L'O', L'P',

	// 0x9X
	L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X',
	L'Y', L'Z', L'(', L')', L':', L';', L'[', L']',

	// 0xAX
	L'a', L'b', L'c', L'd', L'e', L'f', L'g', L'h',
	L'i', L'j', L'k', L'l', L'm', L'n', L'o', L'p',

	// 0xBX
	L'q', L'r', L's', L't', L'u', L'v', L'w', L'x',
	L'y', L'z', L'é', L'd', L'l', L's', L't', L'v',

	// 0xCX
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xDX
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xEX
	L'\'', L'ᴾ', L'ᴹ', L'-', L'r', L'm', L'?', L'!',
	L'.', L'ァ', L'ゥ', L'ェ', L'▹', L'▸', L'▾', L'♂',

	// 0xFX
	L'$', L'×', L'.', L'/', L',', L'♀', L'0', L'1',
	L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'
};

GameBoyGame::GameBoyGame(uint8_t* memory, const uint8_t* rom)
	: Game(memory, rom)
{
}

void GameBoyGame::gameTextToWchar(wchar_t* out, const uint8_t* gameText, size_t len) {
	int i;
	for (i = 0; i < len; ++i) {
		out[i] = charMapGBEn[gameText[i]];
	}
}

const wchar_t* GameBoyGame::trainerName() const {
	return m_trainerName;
}
