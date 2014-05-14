#include <fcntl.h>
#include <sys/mman.h>

#include "gen1.h"

int main(int argc, char** argv) {
	int fd = open("test.sav", O_RDONLY);
	uint8_t* memory = static_cast<uint8_t*>(mmap(0, SIZE_GEN_1, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0));
	Generation1 g1(memory);

	printf("Trainer name: %ls\n", g1.trainerName());

	int nPokemon = g1.nPartyPokemon();
	printf("Party Pokémon: %u\n", nPokemon);

	int i;
	for (i = 0; i < nPokemon; ++i) {
		Pokemon pokemon = g1.partyPokemon(i);
		printf("Pokémon %u:\n", i + 1);
		printf("\tName: %ls\n", pokemon.name());
		printf("\tOT: %ls (%u)\n", pokemon.otName(), pokemon.otId());
		printf("\tExp: %u\n", pokemon.xp());
		printf("\tHP: %u\n", pokemon.currentHp());
	}

	nPokemon = g1.nBoxPokemon(Generation1::BOX_CURRENT);
	printf("Box Pokémon: %u\n", nPokemon);
	for (i = 0; i < nPokemon; ++i) {
		Pokemon pokemon = g1.boxPokemon(Generation1::BOX_CURRENT, i);
		printf("Pokémon %u:\n", i + 1);
		printf("\tName: %ls\n", pokemon.name());
		printf("\tOT: %ls (%u)\n", pokemon.otName(), pokemon.otId());
		printf("\tExp: %u\n", pokemon.xp());
		printf("\tHP: %u\n", pokemon.currentHp());
	}
}
