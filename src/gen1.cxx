#include "gen1.h"

enum {
	G1_BOX_SIZE = 1122
};

const wchar_t charMapGen1En[0x100] = {
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
	L'y', L'z', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xCX
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xDX
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xEX
	L'�', L'P', L'M', L'-', L'�', L'�', L'?', L'!',
	L'.', L'�', L'�', L'�', L'�', L'�', L'�', L'♂',

	// 0xFX
	L'�', L'×', L'�', L'/', L',', L'♀', L'0', L'1',
	L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' 
};

int getPartyPokemon(uint8_t* saveblock, struct G1PartyPokemon** pokemon , uint8_t** names, uint8_t** otNames) {
	int nPokemon = saveblock[G10E_PARTY_POKEMON];
	if (pokemon) {
		*pokemon = reinterpret_cast<struct G1PartyPokemon*>(&saveblock[G10E_PARTY_POKEMON + 2 + 6]);
	}
	if (names) {
		*names = &saveblock[G10E_PARTY_POKEMON + 2 + (sizeof(struct G1PartyPokemon) + 12) * 6];
	}
	if (otNames) {
		*otNames = &saveblock[G10E_PARTY_POKEMON + 2 + (sizeof(struct G1PartyPokemon) + 1) * 6];
	}
	return nPokemon;
}

int getBoxPokemon(uint8_t* saveblock, enum G1Box box, struct G1BoxPokemon** pokemon , uint8_t** names, uint8_t** otNames) {
	size_t start;
	if (box == G1_BOX_CURRENT) {
		start = G10E_CURRENT_BOX;
	} else {
		start = G10E_BOX_1 + (box - 1) * G1_BOX_SIZE;
	}
	int nPokemon = saveblock[start];
	if (pokemon) {
		*pokemon = reinterpret_cast<struct G1BoxPokemon*>(&saveblock[start + 2 + 20]);
	}
	if (names) {
		*names = &saveblock[start + 2 + (sizeof(struct G1BoxPokemon) + 12) * 20];
	}
	if (otNames) {
		*otNames = &saveblock[start + 2 + (sizeof(struct G1BoxPokemon) + 1) * 20];
	}
	return nPokemon;
}
