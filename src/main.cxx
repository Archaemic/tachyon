#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "gen2.h"
#include "util.h"

int main(int argc, char** argv) {
	int fd = open("test.sav", O_RDONLY);
	int romfd = open("game.bin", O_RDONLY);
	uint8_t* memory = static_cast<uint8_t*>(mmap(0, SIZE_GEN_2_SAV, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0));
	uint8_t* rom = static_cast<uint8_t*>(mmap(0, SIZE_GEN_2_ROM, PROT_READ, MAP_FILE | MAP_PRIVATE, romfd, 0));
	Generation2 game(memory, rom);

	std::wcout.imbue(std::locale(""));

	std::wcout << "Trainer name: " << game.trainerName() << std::endl;

	Table<Pokemon*> table;
	table.addColumn(L"Name", [] (Pokemon* p) {
		return p->name();
	}, 10);

	table.addColumn(L"Species", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->species()->readable() << " (" << p->species()->id() << ")";
		return buffer.str();
	}, 16);

	table.addColumn(L"Lvl", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->level();
		return buffer.str();
	}, 3);

	table.addColumn(L"Original Trainer", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->otName() << " (" << p->otId() << ")";
		return buffer.str();
	}, 18);

	table.addColumn(L"Exp.", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->xp();
		return buffer.str();
	}, 7);

	table.addColumn(L"HP", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->currentHp() << "/" << p->maxHp();
		return buffer.str();
	}, 7);

	table.addColumn(L"Type", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << TypeReadable(p->type1());
		if (p->type1() != p->type2()) {
			buffer << "/" << TypeReadable(p->type2());
		}
		return buffer.str();
	}, 18);

	table.addColumn(L"Atk", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->attack();
		return buffer.str();
	}, 4);

	table.addColumn(L"Def", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->defense();
		return buffer.str();
	}, 4);

	table.addColumn(L"Spd", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->speed();
		return buffer.str();
	}, 4);

	table.addColumn(L"SAtk", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->specialAttack();
		return buffer.str();
	}, 4);

	table.addColumn(L"SDef", [] (Pokemon* p) {
		std::wostringstream buffer;
		buffer << p->specialDefense();
		return buffer.str();
	}, 4);

	table.addColumn(L"Move 1", [] (Pokemon* p) {
		return MoveReadable(p->move1());
	}, 15);

	table.addColumn(L"Move 2", [] (Pokemon* p) {
		return MoveReadable(p->move2());
	}, 15);

	table.addColumn(L"Move 3", [] (Pokemon* p) {
		return MoveReadable(p->move3());
	}, 15);

	table.addColumn(L"Move 4", [] (Pokemon* p) {
		return MoveReadable(p->move4());
	}, 15);

	std::vector<std::unique_ptr<Pokemon>> pokemonRefs;

	for (int i = 0; i < game.nPartyPokemon(); ++i) {
		std::unique_ptr<Pokemon> pokemon = game.partyPokemon(i);
		table.addRow(pokemon.get());
		pokemonRefs.push_back(std::move(pokemon));
	}

	int nPokemon = game.nBoxPokemon(GameBoyGame::BOX_CURRENT);
	for (int i = 0; i < nPokemon; ++i) {
		std::unique_ptr<Pokemon> pokemon = game.boxPokemon(GameBoyGame::BOX_CURRENT, i);
		table.addRow(pokemon.get());
		pokemonRefs.push_back(std::move(pokemon));
	}

	for (int box = GameBoyGame::BOX_01; box <= GameBoyGame::BOX_12; ++box) {
		int nPokemon = game.nBoxPokemon(box);
		for (int i = 0; i < nPokemon; ++i) {
			std::unique_ptr<Pokemon> pokemon = game.boxPokemon(box, i);
			table.addRow(pokemon.get());
			pokemonRefs.push_back(std::move(pokemon));
		}
	}
	table.print();

	munmap(memory, SIZE_GEN_2_SAV);
	munmap(memory, SIZE_GEN_2_ROM);
	close(fd);
	close(romfd);
}
