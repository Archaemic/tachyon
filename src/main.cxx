#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "gen1.h"
#include "util.h"

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

	Table<Pokemon> table;
	table.addColumn(L"Name", [] (Pokemon p) {
		return p.name();
	}, 12);

	table.addColumn(L"Species", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.species().readable() << " (" << p.species().id() << ")";
		return buffer.str();
	}, 15);

	table.addColumn(L"Level", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.level();
		return buffer.str();
	}, 5);

	table.addColumn(L"Orig. Trainer", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.otName() << " (" << p.otId() << ")";
		return buffer.str();
	}, 17);

	table.addColumn(L"Exp", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.xp();
		return buffer.str();
	}, 8);

	table.addColumn(L"HP", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.currentHp() << "/" << p.maxHp();
		return buffer.str();
	}, 7);

	table.addColumn(L"Type", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << TypeReadable(p.type1());
		if (p.type1() != p.type2()) {
			buffer << "/" << TypeReadable(p.type2());
		}
		return buffer.str();
	}, 18);

	int i;
	for (i = 0; i < nPokemon; ++i) {
		Pokemon pokemon = g1.partyPokemon(i);
		table.addRow(pokemon);
	}

	nPokemon = g1.nBoxPokemon(Generation1::BOX_CURRENT);
	for (i = 0; i < nPokemon; ++i) {
		Pokemon pokemon = g1.boxPokemon(Generation1::BOX_CURRENT, i);
		table.addRow(pokemon);
	}
	table.print();

	munmap(memory, SIZE_GEN_1_SAV);
	munmap(memory, SIZE_GEN_1_ROM);
	close(fd);
	close(romfd);
}
