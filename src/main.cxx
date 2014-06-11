#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "gen1/Generation1.h"
#include "gen2.h"
#include "gen3.h"
#include "util.h"

int main(int, char**) {
	Generation1::registerLoader();
	Generation2::registerLoader();
	Generation3::registerLoader();

	int fd = open("test.sav", O_RDONLY);
	int romfd = open("game.bin", O_RDONLY);
	uint8_t* memory = static_cast<uint8_t*>(mmap(0, Generation3::SIZE_SAV, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0));
	uint8_t* rom = static_cast<uint8_t*>(mmap(0, Generation3::SIZE_ROM, PROT_READ, MAP_FILE | MAP_PRIVATE, romfd, 0));
	std::unique_ptr<Game> game(Game::load(memory, rom));

	std::cout.imbue(std::locale(""));

	std::cout << "Trainer name: " << game->trainerName() << std::endl;

	Table<Pokemon*> table;
	table.addColumn(u8"Name", [] (Pokemon* p) {
		return p->name();
	}, 10);

	table.addColumn(u8"Species", [] (Pokemon* p) {
		std::stringstream buffer;
		buffer << p->species()->readable() << " (" << p->species()->id() << ") ";
		switch (p->gender()) {
		case Pokemon::MALE:
			buffer << "M";
			break;
		case Pokemon::FEMALE:
			buffer << "F";
			break;
		case Pokemon::GENDERLESS:
			buffer << " ";
			break;
		}
		if (p->shiny()) {
			buffer << u8"*";
		}
		return buffer.str();
	}, 19);

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

	table.addColumn(u8"Nature", [] (Pokemon* p) {
		return p->natureReadable();
	}, 8);

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
	std::vector<std::unique_ptr<Group>> groups;

	groups.push_back(game->party());
	for (unsigned b = 0; b < game->numBoxes(); ++b) {
		groups.push_back(game->box(b));
	}

	for (auto iter = groups.begin(); iter < groups.end(); ++iter) {
		for (unsigned i = 0; i < (*iter)->length(); ++i) {
			std::unique_ptr<Pokemon> pokemon = (*iter)->at(i);
			if (pokemon) {
				table.addRow(pokemon.get());
				pokemonRefs.push_back(std::move(pokemon));
			}
		}
	}

	table.print();

	munmap(memory, Generation3::SIZE_SAV);
	munmap(rom, Generation3::SIZE_ROM);
	close(fd);
	close(romfd);
}
