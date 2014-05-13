#include <fcntl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <wchar.h>

#define R16(V) (((V) & 0xFF) << 8) | (((V) & 0xFF00) >> 8)
#define R24(V) (((V) & 0xFF) << 16) | ((V) & 0xFF00) | (((V) & 0xFF0000) >> 16)
#define R32(V) (((V) & 0xFF) << 24) | (((V) & 0xFF00) << 8) | (((V) & 0xFF0000) >> 8) | (((V) & 0xFF000000) >> 24)

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

enum SaveSizes {
	SIZE_GEN_1 = 0x8000
};

enum SaveOffsets {
	G10E_TRAINER_NAME = 0x2598,
	G10E_PARTY_POKEMON = 0x2F2C,
};

struct G1PartyPokemon {
	uint8_t pokemonId;
	uint16_t currentHp;
	uint8_t displayLevel;
	uint8_t status;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
	uint16_t otId;
	uint32_t xp : 24;
	uint16_t evHp;
	uint16_t evAttack;
	uint16_t evDefense;
	uint16_t evSpeed;
	uint16_t evSpecial;
	uint16_t ivs;
	uint8_t ppMove1;
	uint8_t ppMove2;
	uint8_t ppMove3;
	uint8_t ppMove4;
	uint8_t level;
	uint16_t maxHp;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t special;
} __attribute__((packed));

void gameTextToWchar(wchar_t* out, const uint8_t* gameText, size_t len, const wchar_t* table) {
	int i;
	for (i = 0; i < len; ++i) {
		out[i] = table[gameText[i]];
	}
}

int main(int argc, char** argv) {
	int fd = open("test.sav", O_RDONLY);
	const uint8_t* memory = mmap(0, SIZE_GEN_1, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);

	const uint8_t* start = &memory[G10E_TRAINER_NAME];
	wchar_t name[11] = L"";
	gameTextToWchar(name, start, 8, charMapGen1En);
	printf("Trainer name: %ls\n", name);

	int nPokemon = memory[G10E_PARTY_POKEMON];
	printf("Party Pokémon: %u\n", nPokemon);

	const struct G1PartyPokemon* partyPokemon = (const struct G1PartyPokemon*) &memory[G10E_PARTY_POKEMON + 2 + 6];
	int i;
	for (i = 0; i < nPokemon; ++i) {
		const uint8_t* otNameStart = &memory[G10E_PARTY_POKEMON + 2 + (sizeof(struct G1PartyPokemon) + 1) * 6 + 11 * i];
		const uint8_t* pokemonNameStart = &memory[G10E_PARTY_POKEMON + 2 + (sizeof(struct G1PartyPokemon) + 12) * 6 + 11 * i];
		printf("Pokémon %u:\n", i + 1);
		gameTextToWchar(name, pokemonNameStart, 10, charMapGen1En);
		printf("\tName: %ls\n", name);
		gameTextToWchar(name, otNameStart, 8, charMapGen1En);
		printf("\tOT: %ls (%u)\n", name, R16(partyPokemon[i].otId));
		printf("\tLv: %u\n", partyPokemon[i].level);
		printf("\tExp: %u\n", R24(partyPokemon[i].xp));
		printf("\tHP: %u/%u\n", R16(partyPokemon[i].currentHp), R16(partyPokemon[i].maxHp));
	}
}
