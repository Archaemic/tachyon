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

	Table<Pokemon> table;
	table.addColumn(L"Name", [] (Pokemon p) {
		return p.name();
	}, 10);

	table.addColumn(L"Species", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.species().readable() << " (" << p.species().id() << ")";
		return buffer.str();
	}, 16);

	table.addColumn(L"Lvl", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.level();
		return buffer.str();
	}, 3);

	table.addColumn(L"Original Trainer", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.otName() << " (" << p.otId() << ")";
		return buffer.str();
	}, 18);

	table.addColumn(L"Exp.", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.xp();
		return buffer.str();
	}, 7);

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

	table.addColumn(L"Atk", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.attack();
		return buffer.str();
	}, 4);

	table.addColumn(L"Def", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.defense();
		return buffer.str();
	}, 4);

	table.addColumn(L"Spd", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.speed();
		return buffer.str();
	}, 4);

	table.addColumn(L"SAtk", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.specialAttack();
		return buffer.str();
	}, 4);

	table.addColumn(L"SDef", [] (Pokemon p) {
		std::wostringstream buffer;
		buffer << p.specialDefense();
		return buffer.str();
	}, 4);

	table.addColumn(L"Move 1", [] (Pokemon p) {
		return MoveReadable(p.move1());
	}, 15);

	table.addColumn(L"Move 2", [] (Pokemon p) {
		return MoveReadable(p.move2());
	}, 15);

	table.addColumn(L"Move 3", [] (Pokemon p) {
		return MoveReadable(p.move3());
	}, 15);

	table.addColumn(L"Move 4", [] (Pokemon p) {
		return MoveReadable(p.move4());
	}, 15);

	for (int i = 0; i < g1.nPartyPokemon(); ++i) {
		Pokemon pokemon = g1.partyPokemon(i);
		table.addRow(pokemon);
	}

	int nPokemon = g1.nBoxPokemon(Generation1::BOX_CURRENT);
	for (int i = 0; i < nPokemon; ++i) {
		Pokemon pokemon = g1.boxPokemon(Generation1::BOX_CURRENT, i);
		table.addRow(pokemon);
	}

	for (int box = Generation1::BOX_01; box <= Generation1::BOX_12; ++box) {
		int nPokemon = g1.nBoxPokemon(box);
		for (int i = 0; i < nPokemon; ++i) {
			Pokemon pokemon = g1.boxPokemon(box, i);
			table.addRow(pokemon);
		}
	}
	table.print();

	munmap(memory, SIZE_GEN_1_SAV);
	munmap(memory, SIZE_GEN_1_ROM);
	close(fd);
	close(romfd);
}
