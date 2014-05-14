#include <fcntl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <wchar.h>

#include "gen1.h"

#define R16(V) (((V) & 0xFF) << 8) | (((V) & 0xFF00) >> 8)
#define R24(V) (((V) & 0xFF) << 16) | ((V) & 0xFF00) | (((V) & 0xFF0000) >> 16)
#define R32(V) (((V) & 0xFF) << 24) | (((V) & 0xFF00) << 8) | (((V) & 0xFF0000) >> 8) | (((V) & 0xFF000000) >> 24)

void gameTextToWchar(wchar_t* out, const uint8_t* gameText, size_t len, const wchar_t* table) {
	int i;
	for (i = 0; i < len; ++i) {
		out[i] = table[gameText[i]];
	}
}

int main(int argc, char** argv) {
	int fd = open("test.sav", O_RDONLY);
	uint8_t* memory = static_cast<uint8_t*>(mmap(0, SIZE_GEN_1, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0));

	uint8_t* start = &memory[G10E_TRAINER_NAME];
	wchar_t name[11] = L"";
	gameTextToWchar(name, start, 8, charMapGen1En);
	printf("Trainer name: %ls\n", name);

	struct G1PartyPokemon* partyPokemon = 0;
	struct G1BoxPokemon* boxPokemon = 0;
	uint8_t* otNameStart = 0;
	uint8_t* pokemonNameStart = 0;
	int nPokemon = getPartyPokemon(memory, &partyPokemon, &pokemonNameStart, &otNameStart);
	printf("Party Pokémon: %u\n", nPokemon);

	int i;
	for (i = 0; i < nPokemon; ++i) {
		printf("Pokémon %u:\n", i + 1);
		gameTextToWchar(name, pokemonNameStart + 11 * i, 10, charMapGen1En);
		printf("\tName: %ls\n", name);
		gameTextToWchar(name, otNameStart + 11 * i, 8, charMapGen1En);
		printf("\tOT: %ls (%u)\n", name, R16(partyPokemon[i].otId));
		printf("\tLv: %u\n", partyPokemon[i].level);
		printf("\tExp: %u\n", R24(partyPokemon[i].xp));
		printf("\tHP: %u/%u\n", R16(partyPokemon[i].currentHp), R16(partyPokemon[i].maxHp));
	}

	nPokemon = getBoxPokemon(memory, G1_BOX_CURRENT, &boxPokemon, &pokemonNameStart, &otNameStart);
	printf("Box Pokémon: %u\n", nPokemon);
	for (i = 0; i < nPokemon; ++i) {
		printf("Pokémon %u:\n", i + 1);
		gameTextToWchar(name, pokemonNameStart + 11 * i, 10, charMapGen1En);
		printf("\tName: %ls\n", name);
		gameTextToWchar(name, otNameStart + 11 * i, 8, charMapGen1En);
		printf("\tOT: %ls (%u)\n", name, R16(boxPokemon[i].otId));
		printf("\tExp: %u\n", R24(boxPokemon[i].xp));
		printf("\tHP: %u\n", R16(boxPokemon[i].currentHp));
	}
}
