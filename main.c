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
