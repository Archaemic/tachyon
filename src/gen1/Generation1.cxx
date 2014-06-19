#include "gen1/Generation1.h"

#include "gen1/G1Box.h"
#include "gen1/G1Party.h"
#include "gen1/G1PokemonSpecies.h"
#include "gen1/G1SpriteDecompressor.h"

enum {
	G1_BOX_SIZE = 1122,

	G10E_SUM_REGION_START = 0x2598,
	G10E_SUM_REGION_END = 0x3523,

	G10E_TRAINER_NAME = 0x2598,
	G10E_CHECKSUM = 0x3523,

	G10E_PALETTE_MAPPING = 0x0725C8,
	G10E_PALETTES = 0x072660,

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

const PokemonSpecies* Generation1::species(PokemonSpecies::Id id, PokemonSpecies::Forme) {
	const PokemonSpecies* species = Game::species(id);
	if (!species) {
		const G1PokemonBaseStats* stats;
		if (id == PokemonSpecies::MEW && version() != Game::G11E_YELLOW) {
			stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_MEW_STATS]);
		} else {
			stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_BASE_STATS]);
			stats = &stats[id - 1];
		}
		PokemonSpecies* newSpecies = new G1PokemonSpecies(stats);
		loadSprites(newSpecies, stats);
		putSpecies(id, newSpecies);
		species = newSpecies;
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

PokemonSpecies::Id Generation1::mapId(unsigned id) const {
	const uint8_t* idMapping = &rom()[G10E_ID_MAPPING];
	return static_cast<PokemonSpecies::Id>(idMapping[id]);
}

void Generation1::loadSprites(PokemonSpecies* species, const G1PokemonBaseStats* data) const {
	unsigned width = data->spriteDim >> 4;
	unsigned height = data->spriteDim & 0xF;

	// TODO: Handle glitch Pokemon
	const uint8_t* idMapping = &rom()[G10E_ID_MAPPING];
	int gameId;
	for (gameId = 0; gameId < 256; ++gameId) {
		if (idMapping[gameId] == species->id()) {
			break;
		}
	}

	uint8_t mapping = rom()[G10E_PALETTE_MAPPING + species->id()];

	const struct Palette {
		uint16_t color[4];
	} __attribute__((packed))* palette = &reinterpret_cast<const Palette*>(&rom()[G10E_PALETTES])[mapping];

	unsigned bank;

	if (gameId == 0x15) {
		bank = 0x01;
	} else if (gameId == 0xB6) {
		bank = 0x0B;
	} else if (gameId <= 0x1F) {
		bank = 0x09;
	} else if (gameId <= 0x49) {
		bank = 0x0A;
	} else if (gameId <= 0x73) {
		bank = 0x0B;
	} else if (gameId <= 0x98) {
		bank = 0x0C;
	} else {
		bank = 0x0D;
	}

	unsigned address = data->frontSprite;
	address = bank * 0x4000 + (address & 0x3FFF);

	uint8_t* rawSpriteData = new uint8_t[width * height * 16];
	uint8_t* spriteData = new uint8_t[width * height * 16];
	uint16_t* paletteData = new uint16_t[16];

	paletteData[0] = palette->color[0];
	paletteData[1] = palette->color[1];
	paletteData[2] = palette->color[2];
	paletteData[3] = palette->color[3];

	const uint8_t* spritePointer = &rom()[address & (Generation1::SIZE_ROM - 1)];

	G1SpriteDecompressor decomp(spritePointer, 0x400);
	decomp.decompress();
	memcpy(rawSpriteData, decomp.output(), std::min<size_t>(width * height * 16, decomp.size()));

	arrangeTiles(rawSpriteData, spriteData, width, height);

	delete [] rawSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(width * 8, height * 8, spriteData, paletteData, Sprite::GB_2);
	species->setFrontSprite(sprite);
}
