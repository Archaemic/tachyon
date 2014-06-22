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

	G10J_PALETTE_MAPPING = 0x072A1E,
	G10E_PALETTE_MAPPING = 0x0725C8,
	G10G_PALETTE_MAPPING = 0x0725A2,
	G10F_PALETTE_MAPPING = 0x072599,
	G10S_PALETTE_MAPPING = 0x0725B8,
	G10I_PALETTE_MAPPING = 0x072608,
	G11J_PALETTE_MAPPING = 0x072A0D,
	G12J_PALETTE_MAPPING = 0x07264F,
	G12E_PALETTE_MAPPING = 0x072921,
	G12G_PALETTE_MAPPING = 0x072900,
	G12F_PALETTE_MAPPING = 0x0728F2,
	G12S_PALETTE_MAPPING = 0x072911,
	G12I_PALETTE_MAPPING = 0x072961,
	G13J_PALETTE_MAPPING = 0x07265A,

	G10J_PALETTES = 0x072AB6,
	G10E_PALETTES = 0x072660,
	G10G_PALETTES = 0x07263A,
	G10F_PALETTES = 0x072631,
	G10S_PALETTES = 0x072650,
	G10I_PALETTES = 0x0726A0,
	G11J_PALETTES = 0x072AA5,
	G12J_PALETTES = 0x0726E7,
	G12E_PALETTES = 0x0729B9,
	G12G_PALETTES = 0x072998,
	G12F_PALETTES = 0x07298A,
	G12S_PALETTES = 0x0729A9,
	G12I_PALETTES = 0x0729F9,
	G13J_PALETTES = 0x0726F2,

	G10J_BASE_STATS = 0x038000,
	G10E_BASE_STATS = 0x0383DE,
	G10J_MEW_STATS = 0x004200,
	G10E_MEW_STATS = 0x00425B,

	G10J_ID_MAPPING = 0x042799,
	G10E_ID_MAPPING = 0x041023,
	G10G_ID_MAPPING = 0x040F95,
	G10F_ID_MAPPING = 0x040FA9,
	G10I_ID_MAPPING = 0x040FB5,
	G10S_ID_MAPPING = 0x040FB3,
	G11J_ID_MAPPING = 0x042783,
	G12J_ID_MAPPING = 0x04282C,
	G12E_ID_MAPPING = 0x0410B0,
	G12G_ID_MAPPING = 0x041022,
	G12F_ID_MAPPING = 0x041035,
	G12S_ID_MAPPING = 0x041040,
	G12I_ID_MAPPING = 0x041042,
};

const GameBoyGame::ChecksumMapping Generation1::s_checksums[] = {
	{ 0x66B8, Game::G10_RED | Game::JAPANESE },
	{ 0xC1A2, Game::G10_RED | Game::JAPANESE },
	{ 0xE691, Game::G10_RED | Game::ENGLISH },
	{ 0xDC5C, Game::G10_RED | Game::GERMAN },
	{ 0xFC7A, Game::G10_RED | Game::FRENCH },
	{ 0x4A38, Game::G10_RED | Game::SPANISH },
	{ 0xD289, Game::G10_RED | Game::ITALIAN },
	{ 0xD5DD, Game::G10_GREEN | Game::JAPANESE },
	{ 0x47F5, Game::G10_GREEN | Game::JAPANESE },
	{ 0x0A9D, Game::G10_BLUE | Game::ENGLISH },
	{ 0xBC2E, Game::G10_BLUE | Game::GERMAN },
	{ 0xA456, Game::G10_BLUE | Game::FRENCH },
	{ 0xD714, Game::G10_BLUE | Game::SPANISH },
	{ 0x9C5E, Game::G10_BLUE | Game::ITALIAN },
	{ 0x36DC, Game::G11_BLUE | Game::JAPANESE },
	{ 0x299C, Game::G12_YELLOW | Game::JAPANESE },
	{ 0x7C04, Game::G12_YELLOW | Game::ENGLISH },
	{ 0xFB66, Game::G12_YELLOW | Game::GERMAN },
	{ 0xC1B7, Game::G12_YELLOW | Game::FRENCH },
	{ 0x3756, Game::G12_YELLOW | Game::SPANISH },
	{ 0x8F4E, Game::G12_YELLOW | Game::ITALIAN },
	{ 0x5888, Game::G13_YELLOW | Game::JAPANESE },
	{ 0xD9ED, Game::G13_YELLOW | Game::JAPANESE },
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

Game::Edition Generation1::Loader::detect(const uint8_t* rom) const {
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	return GameBoyGame::findVersion(Generation1::s_checksums, checksum);
}

unsigned Generation1::numBoxes() const {
	if ((version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		return 8;
	}
	return 12;
}

Game::Edition Generation1::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	return GameBoyGame::findVersion(s_checksums, checksum);
}

const PokemonSpecies* Generation1::species(PokemonSpecies::Id id, PokemonSpecies::Forme) {
	const PokemonSpecies* species = Game::species(id);
	if (!species) {
		const G1PokemonBaseStats* stats;
		if ((version() & Game::MASK_LOCALIZATION) == Game::JAPANESE && (version() & Game::MASK_GAME) < Game::G11_BLUE) {
			if (id == PokemonSpecies::MEW && (version() & Game::MASK_GAME) < Game::G12_YELLOW) {
				stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10J_MEW_STATS]);
			} else {
				stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10J_BASE_STATS]);
				stats = &stats[id - 1];
			}
		} else {
			if (id == PokemonSpecies::MEW && (version() & Game::MASK_GAME) < Game::G12_YELLOW) {
				stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_MEW_STATS]);
			} else {
				stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_BASE_STATS]);
				stats = &stats[id - 1];
			}
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
	const uint8_t* idMapping;
	switch (version()) {
	case Game::G10_RED | Game::JAPANESE:
	case Game::G10_GREEN | Game::JAPANESE:
		idMapping = &rom()[G10J_ID_MAPPING];
		break;
	case Game::G10_RED | ENGLISH:
	case Game::G10_BLUE | ENGLISH:
		idMapping = &rom()[G10E_ID_MAPPING];
		break;
	case Game::G10_RED | Game::GERMAN:
	case Game::G10_BLUE | Game::GERMAN:
		idMapping = &rom()[G10G_ID_MAPPING];
		break;
	case Game::G10_RED | Game::FRENCH:
	case Game::G10_BLUE | Game::FRENCH:
		idMapping = &rom()[G10F_ID_MAPPING];
		break;
	case Game::G10_RED | Game::SPANISH:
	case Game::G10_BLUE | Game::SPANISH:
		idMapping = &rom()[G10S_ID_MAPPING];
		break;
	case Game::G10_RED | Game::ITALIAN:
	case Game::G10_BLUE | Game::ITALIAN:
		idMapping = &rom()[G10I_ID_MAPPING];
		break;
	case Game::G11_BLUE | Game::JAPANESE:
		idMapping = &rom()[G11J_ID_MAPPING];
		break;
	case Game::G12_YELLOW | Game::JAPANESE:
	case Game::G13_YELLOW | Game::JAPANESE:
		idMapping = &rom()[G12J_ID_MAPPING];
		break;
	case Game::G12_YELLOW | Game::ENGLISH:
		idMapping = &rom()[G12E_ID_MAPPING];
		break;
	case Game::G12_YELLOW | Game::GERMAN:
		idMapping = &rom()[G12G_ID_MAPPING];
		break;
	case Game::G12_YELLOW | Game::FRENCH:
		idMapping = &rom()[G12F_ID_MAPPING];
		break;
	case Game::G12_YELLOW | Game::SPANISH:
		idMapping = &rom()[G12S_ID_MAPPING];
		break;
	case Game::G12_YELLOW | Game::ITALIAN:
		idMapping = &rom()[G12I_ID_MAPPING];
		break;
	default:
		return PokemonSpecies::MISSINGNO;
	}
	return static_cast<PokemonSpecies::Id>(idMapping[id]);
}

void Generation1::loadSprites(PokemonSpecies* species, const G1PokemonBaseStats* data) const {
	unsigned width = data->spriteDim >> 4;
	unsigned height = data->spriteDim & 0xF;

	// TODO: Handle glitch Pokemon
	const uint8_t* idMapping;
	uint8_t mapping;
	const struct Palette {
		uint16_t color[4];
	} __attribute__((packed))* palette;

	switch (version()) {
	case Game::G10_RED | Game::JAPANESE:
	case Game::G10_GREEN | Game::JAPANESE:
		idMapping = &rom()[G10J_ID_MAPPING];
		mapping = rom()[G10J_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G10J_PALETTES])[mapping];
		break;
	case Game::G10_RED | ENGLISH:
	case Game::G10_BLUE | ENGLISH:
		idMapping = &rom()[G10E_ID_MAPPING];
		mapping = rom()[G10E_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G10E_PALETTES])[mapping];
		break;
	case Game::G10_RED | Game::GERMAN:
	case Game::G10_BLUE | Game::GERMAN:
		idMapping = &rom()[G10G_ID_MAPPING];
		mapping = rom()[G10G_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G10G_PALETTES])[mapping];
		break;
	case Game::G10_RED | Game::FRENCH:
	case Game::G10_BLUE | Game::FRENCH:
		idMapping = &rom()[G10F_ID_MAPPING];
		mapping = rom()[G10F_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G10F_PALETTES])[mapping];
		break;
	case Game::G10_RED | Game::SPANISH:
	case Game::G10_BLUE | Game::SPANISH:
		idMapping = &rom()[G10S_ID_MAPPING];
		mapping = rom()[G10S_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G10S_PALETTES])[mapping];
		break;
	case Game::G10_RED | Game::ITALIAN:
	case Game::G10_BLUE | Game::ITALIAN:
		idMapping = &rom()[G10I_ID_MAPPING];
		mapping = rom()[G10I_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G10I_PALETTES])[mapping];
		break;
	case Game::G11_BLUE | Game::JAPANESE:
		idMapping = &rom()[G11J_ID_MAPPING];
		mapping = rom()[G11J_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G11J_PALETTES])[mapping];
		break;
	case Game::G12_YELLOW | Game::JAPANESE:
		idMapping = &rom()[G12J_ID_MAPPING];
		mapping = rom()[G12J_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G12J_PALETTES])[mapping];
		break;
	case Game::G12_YELLOW | Game::ENGLISH:
		idMapping = &rom()[G12E_ID_MAPPING];
		mapping = rom()[G12E_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G12E_PALETTES])[mapping];
		break;
	case Game::G12_YELLOW | Game::GERMAN:
		idMapping = &rom()[G12G_ID_MAPPING];
		mapping = rom()[G12G_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G12G_PALETTES])[mapping];
		break;
	case Game::G12_YELLOW | Game::FRENCH:
		idMapping = &rom()[G12F_ID_MAPPING];
		mapping = rom()[G12F_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G12F_PALETTES])[mapping];
		break;
	case Game::G12_YELLOW | Game::SPANISH:
		idMapping = &rom()[G12S_ID_MAPPING];
		mapping = rom()[G12S_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G12S_PALETTES])[mapping];
		break;
	case Game::G12_YELLOW | Game::ITALIAN:
		idMapping = &rom()[G12I_ID_MAPPING];
		mapping = rom()[G12I_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G12I_PALETTES])[mapping];
		break;
	case Game::G13_YELLOW | Game::JAPANESE:
		idMapping = &rom()[G12J_ID_MAPPING];
		mapping = rom()[G13J_PALETTE_MAPPING + species->id()];
		palette = &reinterpret_cast<const Palette*>(&rom()[G13J_PALETTES])[mapping];
		break;
	default:
		return;
	}

	int gameId;
	for (gameId = 0; gameId < 256; ++gameId) {
		if (idMapping[gameId] == species->id()) {
			break;
		}
	}

	unsigned bank;

	if (gameId == 0x15 && (version() & Game::MASK_GAME) < Game::G12_YELLOW){
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

	uint8_t* rawSpriteData = new uint8_t[width * height * 16];
	uint8_t* spriteData = new uint8_t[width * height * 16];
	uint8_t* rawBackSpriteData = new uint8_t[256];
	uint8_t* backSpriteData = new uint8_t[256];
	uint16_t* paletteData = new uint16_t[16];
	uint16_t* backPaletteData = new uint16_t[16];

	paletteData[0] = palette->color[0];
	paletteData[1] = palette->color[1];
	paletteData[2] = palette->color[2];
	paletteData[3] = palette->color[3];
	backPaletteData[0] = palette->color[0];
	backPaletteData[1] = palette->color[1];
	backPaletteData[2] = palette->color[2];
	backPaletteData[3] = palette->color[3];

	unsigned frontAddress = data->frontSprite;
	frontAddress = bank * 0x4000 + (frontAddress & 0x3FFF);

	unsigned backAddress = data->backSprite;
	backAddress = bank * 0x4000 + (backAddress & 0x3FFF);

	const uint8_t* spritePointer = &rom()[frontAddress & (Generation1::SIZE_ROM - 1)];
	const uint8_t* backSpritePointer = &rom()[backAddress & (Generation1::SIZE_ROM - 1)];

	G1SpriteDecompressor decomp(spritePointer, 0x400);
	decomp.decompress();
	memcpy(rawSpriteData, decomp.output(), std::min<size_t>(width * height * 16, decomp.size()));

	decomp = G1SpriteDecompressor(backSpritePointer, 0x200);
	decomp.decompress();
	memcpy(rawBackSpriteData, decomp.output(), std::min<size_t>(256, decomp.size()));

	arrangeTiles(rawSpriteData, spriteData, width, height);
	arrangeTiles(rawBackSpriteData, backSpriteData, 4, 4);

	delete [] rawSpriteData;
	delete [] rawBackSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(width * 8, height * 8, spriteData, paletteData, Sprite::GB_2);
	species->setFrontSprite(sprite);

	sprite = new MultipaletteSprite(32, 32, backSpriteData, backPaletteData, Sprite::GB_2);
	species->setBackSprite(sprite);
}
