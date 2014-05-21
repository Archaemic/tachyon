#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "gen2.h"
#include "util.h"

int main(int, char**) {
	int fd = open("test.sav", O_RDONLY);
	int romfd = open("game.bin", O_RDONLY);
	uint8_t* memory = static_cast<uint8_t*>(mmap(0, SIZE_GEN_2_SAV, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0));
	uint8_t* rom = static_cast<uint8_t*>(mmap(0, SIZE_GEN_2_ROM, PROT_READ, MAP_FILE | MAP_PRIVATE, romfd, 0));
	Generation2 game(memory, rom);

	std::cout.imbue(std::locale(""));

	std::cout << "Trainer name: " << game.trainerName() << std::endl;

	Table<Pokemon*> table;
	table.addColumn(u8"Name", [] (Pokemon* p) {
		return p->name();
	}, 10);

	table.addColumn(u8"Species", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->species()->readable() << " (" << p->species()->id() << ")";
		return buffer.str();
	}, 16);

	table.addColumn(u8"Lvl", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->level();
		return buffer.str();
	}, 3);

	table.addColumn(u8"Original Trainer", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->otName() << " (" << p->otId() << ")";
		return buffer.str();
	}, 18);

	table.addColumn(u8"Exp.", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->xp();
		return buffer.str();
	}, 7);

	table.addColumn(u8"HP", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->currentHp() << "/" << p->maxHp();
		return buffer.str();
	}, 7);

	table.addColumn(u8"Type", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << TypeReadable(p->type1());
		if (p->type1() != p->type2()) {
			buffer << "/" << TypeReadable(p->type2());
		}
		return buffer.str();
	}, 18);

	table.addColumn(u8"Atk", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->attack();
		return buffer.str();
	}, 4);

	table.addColumn(u8"Def", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->defense();
		return buffer.str();
	}, 4);

	table.addColumn(u8"Spd", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->speed();
		return buffer.str();
	}, 4);

	table.addColumn(u8"SAtk", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->specialAttack();
		return buffer.str();
	}, 4);

	table.addColumn(u8"SDef", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->specialDefense();
		return buffer.str();
	}, 4);

	table.addColumn(u8"Move 1", [] (Pokemon* p) {
		return MoveReadable(p->move1());
	}, 15);

	table.addColumn(u8"Move 2", [] (Pokemon* p) {
		return MoveReadable(p->move2());
	}, 15);

	table.addColumn(u8"Move 3", [] (Pokemon* p) {
		return MoveReadable(p->move3());
	}, 15);

	table.addColumn(u8"Move 4", [] (Pokemon* p) {
		return MoveReadable(p->move4());
	}, 15);

	std::vector<std::unique_ptr<Pokemon>> pokemonRefs;

	for (unsigned i = 0; i < game.nPartyPokemon(); ++i) {
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
