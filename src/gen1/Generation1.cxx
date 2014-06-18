#include "gen1/Generation1.h"

#include "gen1/G1Box.h"
#include "gen1/G1Party.h"
#include "gen1/G1PokemonSpecies.h"

enum {
	G10E_SUM_REGION_START = 0x2598,
	G10E_SUM_REGION_END = 0x3523,

	G10E_TRAINER_NAME = 0x2598,
	G10E_CHECKSUM = 0x3523,

	G10E_BASE_STATS = 0x0383DE,
	G10E_MEW_STATS = 0x00425B,
};

const GameBoyGame::ChecksumMapping Generation1::s_checksums[] = {
	{ 0x66B8, Game::G10J_RED },
	{ 0xC1A2, Game::G10J_RED },
	{ 0xE691, Game::G10E_RED },
	{ 0, Game::INVALID }
};

Generation1::Generation1(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
{
	setTrainerName(gameTextToUTF8(&memory[G10E_TRAINER_NAME], 8));
	setParty(new G1Party(this));
	for (unsigned box = 0; box < numBoxes(); ++box) {
		addBox(new G1Box(this, box));
	}
}

void Generation1::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Generation1* Generation1::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	if (detect(rom)) {
		return new Generation1(memory, rom);
	}
	return nullptr;
}

Game::Version Generation1::Loader::detect(const uint8_t* rom) const {
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	return GameBoyGame::version(Generation1::s_checksums, checksum);
}

unsigned Generation1::numBoxes() const {
	return 12;
}

Game::Version Generation1::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	return GameBoyGame::version(s_checksums, checksum);
}

PokemonSpecies* Generation1::species(PokemonSpecies::Id id, PokemonSpecies::Forme) {
	PokemonSpecies* species = Game::species(id);
	if (!species) {
		if (id == PokemonSpecies::MEW && version() != Game::G11E_YELLOW) {
			const G1PokemonBaseStats* stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_MEW_STATS]);
			species = new G1PokemonSpecies(this, stats);
		} else {
			const G1PokemonBaseStats* stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_BASE_STATS]);
			species = new G1PokemonSpecies(this, &stats[id - 1]);
		}
		putSpecies(id, species);
	}
	return species;
}

void Generation1::finalize() {
	uint8_t checksum = 0xFF;
	uint8_t* memory = ram();
	for (unsigned i = G10E_SUM_REGION_START; i < G10E_SUM_REGION_END; ++i) {
		checksum -= memory[i];
	}
	memory[G10E_CHECKSUM] = checksum;
}
