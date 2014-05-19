#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>

#include "gen1.h"

int main(int argc, char** argv) {
	int fd = open("test.sav", O_RDONLY);
	int romfd = open("game.bin", O_RDONLY);
	uint8_t* memory = static_cast<uint8_t*>(mmap(0, SIZE_GEN_1_SAV, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0));
	uint8_t* rom = static_cast<uint8_t*>(mmap(0, SIZE_GEN_1_ROM, PROT_READ, MAP_FILE | MAP_PRIVATE, romfd, 0));
	Generation1 g1(memory, rom);

	std::wcout.imbue(std::locale(""));

	std::wcout << "Trainer name: " << g1.trainerName() << std::endl;

	int nPokemon = g1.nPartyPokemon();
	std::wcout << L"Party Pokémon: " << nPokemon << std::endl;

	int i;
	for (i = 0; i < nPokemon; ++i) {
		Pokemon pokemon = g1.partyPokemon(i);
		std::wcout << L"Pokémon " << (i + 1) << ":" << std::endl;
		pokemon.enumerate();
	}

	nPokemon = g1.nBoxPokemon(Generation1::BOX_CURRENT);
	std::wcout << L"Box Pokémon: " << nPokemon << std::endl;
	for (i = 0; i < nPokemon; ++i) {
		Pokemon pokemon = g1.boxPokemon(Generation1::BOX_CURRENT, i);
		std::wcout << L"Pokémon " << (i + 1) << ":" << std::endl;
		pokemon.enumerate();
	}

	munmap(memory, SIZE_GEN_1_SAV);
	munmap(memory, SIZE_GEN_1_ROM);
	close(fd);
	close(romfd);
}
