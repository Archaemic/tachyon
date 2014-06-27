#include "gen1/Generation1.h"

#include "gen1/G1Box.h"
#include "gen1/G1Party.h"
#include "gen1/G1PokemonSpecies.h"
#include "gen1/G1SpriteDecompressor.h"

enum {
	G10X_SUM_REGION_START = 0x2598,
	G10J_SUM_REGION_END = 0x3594,
	G10X_SUM_REGION_END = 0x3523,

	G10_TRAINER_NAME = 0x2598,

	G10J_BASE_STATS = 0x038000,
	G10X_BASE_STATS = 0x0383DE,
	G10J_MEW_STATS = 0x004200,
	G10X_MEW_STATS = 0x00425B,

	G10J_PARTY_POKEMON = 0x2ED5,
	G10X_PARTY_POKEMON = 0x2F2C,

	G10J_BOX_SIZE = 1382,
	G10X_BOX_SIZE = 1122,

	G10J_BOX_HIGH_OFFSET = 4,
	G10X_BOX_HIGH_OFFSET = 6,

	G10J_CURRENT_BOX_ID = 0x2842,
	G10J_CURRENT_BOX = 0x302D,

	G10X_CURRENT_BOX_ID = 0x284C,
	G10X_CURRENT_BOX = 0x30C0,

	G12J_ID_MAPPING = 0x04282C,
	G12J_MENU_SPRITE_MAPPING = 0x071911,
	G12J_MENU_SPRITE_COMMANDS = 0x0717A4,

	G10_NUM_MENU_SPRITE_COMMANDS = 0x1C,
};

static const Generation1::Offsets G10J = {
	.paletteMapping = 0x072A1E,
	.paletteBase = 0x072AB6,
	.baseStats = G10J_BASE_STATS,
	.mewStats = G10J_MEW_STATS,
	.idMapping = 0x042799,
	.menuSpriteMapping = 0x071DD1,
	.menuSpriteCommands = 0x071C84,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10J_SUM_REGION_END,
	.partyPokemon = G10J_PARTY_POKEMON,
	.boxSize = G10J_BOX_SIZE,
	.boxHigh = G10J_BOX_HIGH_OFFSET,
	.currentBox = G10J_CURRENT_BOX,
	.currentBoxId = G10J_CURRENT_BOX_ID
};

static const Generation1::Offsets G10E = {
	.paletteMapping = 0x0725C8,
	.paletteBase = 0x072660,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x041023,
	.menuSpriteMapping = 0x07190D,
	.menuSpriteCommands = 0x0717C0,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G10F = {
	.paletteMapping = 0x072599,
	.paletteBase = 0x072631,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x040FA9,
	.menuSpriteMapping = 0x0718DE,
	.menuSpriteCommands = 0x071791,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G10G = {
	.paletteMapping = 0x0725A2,
	.paletteBase = 0x07263A,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x040F95,
	.menuSpriteMapping = 0x0718E7,
	.menuSpriteCommands = 0x07179A,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G10I = {
	.paletteMapping = 0x072608,
	.paletteBase = 0x0726A0,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x040FB5,
	.menuSpriteMapping = 0x07194D,
	.menuSpriteCommands = 0x071800,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G10S = {
	.paletteMapping = 0x072911,
	.paletteBase = 0x072650,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x040FB3,
	.menuSpriteMapping = 0x0718FD,
	.menuSpriteCommands = 0x0717B0,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G11J = {
	.paletteMapping = 0x072A0D,
	.paletteBase = 0x072AA5,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x042783,
	.menuSpriteMapping = 0x071DC1,
	.menuSpriteCommands = 0x071C74,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10J_SUM_REGION_END,
	.partyPokemon = G10J_PARTY_POKEMON,
	.boxSize = G10J_BOX_SIZE,
	.boxHigh = G10J_BOX_HIGH_OFFSET,
	.currentBox = G10J_CURRENT_BOX,
	.currentBoxId = G10J_CURRENT_BOX_ID
};

static const Generation1::Offsets G12J = {
	.paletteMapping = 0x07264F,
	.paletteBase = 0x0726E7,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = G12J_ID_MAPPING,
	.menuSpriteMapping = G12J_MENU_SPRITE_MAPPING,
	.menuSpriteCommands = G12J_MENU_SPRITE_COMMANDS,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10J_SUM_REGION_END,
	.partyPokemon = G10J_PARTY_POKEMON,
	.boxSize = G10J_BOX_SIZE,
	.boxHigh = G10J_BOX_HIGH_OFFSET,
	.currentBox = G10J_CURRENT_BOX,
	.currentBoxId = G10J_CURRENT_BOX_ID
};

static const Generation1::Offsets G12E = {
	.paletteMapping = 0x072921,
	.paletteBase = 0x0729B9,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x0410B0,
	.menuSpriteMapping = 0x0719BA,
	.menuSpriteCommands = 0x07184E,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G12F = {
	.paletteMapping = 0x0728F2,
	.paletteBase = 0x07298A,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x041035,
	.menuSpriteMapping = 0x07198B,
	.menuSpriteCommands = 0x07181E,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G12G = {
	.paletteMapping = 0x072900,
	.paletteBase = 0x072998,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x041022,
	.menuSpriteMapping = 0x071999,
	.menuSpriteCommands = 0x07182C,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G12I = {
	.paletteMapping = 0x072961,
	.paletteBase = 0x0729F9,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x041042,
	.menuSpriteMapping = 0x0719FA,
	.menuSpriteCommands = 0x07188E,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G12S = {
	.paletteMapping = 0x072911,
	.paletteBase = 0x0729A9,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = 0x041040,
	.menuSpriteMapping = 0x0719AA,
	.menuSpriteCommands = 0x07183D,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10X_SUM_REGION_END,
	.partyPokemon = G10X_PARTY_POKEMON,
	.boxSize = G10X_BOX_SIZE,
	.boxHigh = G10X_BOX_HIGH_OFFSET,
	.currentBox = G10X_CURRENT_BOX,
	.currentBoxId = G10X_CURRENT_BOX_ID
};

static const Generation1::Offsets G12J1 = {
	.paletteMapping = 0x07265A,
	.paletteBase = 0x0726F2,
	.baseStats = G10X_BASE_STATS,
	.mewStats = G10X_MEW_STATS,
	.idMapping = G12J_ID_MAPPING,
	.checksumStart = G10X_SUM_REGION_START,
	.checksumEnd = G10J_SUM_REGION_END,
	.menuSpriteMapping = G12J_MENU_SPRITE_MAPPING,
	.menuSpriteCommands = G12J_MENU_SPRITE_COMMANDS,
	.partyPokemon = G10J_PARTY_POKEMON,
	.boxSize = G10J_BOX_SIZE,
	.boxHigh = G10J_BOX_HIGH_OFFSET,
	.currentBox = G10J_CURRENT_BOX,
	.currentBoxId = G10J_CURRENT_BOX_ID
};

const GameBoyGame::ChecksumMapping<Generation1::Offsets> Generation1::s_checksums[] = {
	{ 0x66B8, Game::G10_RED | Game::JAPANESE, &G10J },
	{ 0xC1A2, Game::G10_RED | Game::JAPANESE, &G10J },
	{ 0xE691, Game::G10_RED | Game::ENGLISH, &G10E },
	{ 0xDC5C, Game::G10_RED | Game::GERMAN, &G10G },
	{ 0xFC7A, Game::G10_RED | Game::FRENCH, &G10F },
	{ 0x4A38, Game::G10_RED | Game::SPANISH, &G10S },
	{ 0xD289, Game::G10_RED | Game::ITALIAN, &G10I },
	{ 0xD5DD, Game::G10_GREEN | Game::JAPANESE, &G10J },
	{ 0x47F5, Game::G10_GREEN | Game::JAPANESE, &G10J },
	{ 0x0A9D, Game::G10_BLUE | Game::ENGLISH, &G10E },
	{ 0xBC2E, Game::G10_BLUE | Game::GERMAN, &G10G },
	{ 0xA456, Game::G10_BLUE | Game::FRENCH, &G10F },
	{ 0xD714, Game::G10_BLUE | Game::SPANISH, &G10S },
	{ 0x9C5E, Game::G10_BLUE | Game::ITALIAN, &G10I },
	{ 0x36DC, Game::G11_BLUE | Game::JAPANESE, &G11J },
	{ 0x299C, Game::G12_YELLOW | Game::JAPANESE, &G12J },
	{ 0x5888, Game::G12_YELLOW | Game::JAPANESE, &G12J1 },
	{ 0xD9ED, Game::G12_YELLOW | Game::JAPANESE, &G12J1 },
	{ 0x7C04, Game::G12_YELLOW | Game::ENGLISH, &G12E },
	{ 0xFB66, Game::G12_YELLOW | Game::GERMAN, &G12G },
	{ 0xC1B7, Game::G12_YELLOW | Game::FRENCH, &G12F },
	{ 0x3756, Game::G12_YELLOW | Game::SPANISH, &G12S },
	{ 0x8F4E, Game::G12_YELLOW | Game::ITALIAN, &G12I },
	{ 0, Game::INVALID, nullptr }
};

Generation1::Generation1(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
	, m_spriteMemory(nullptr)
{
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	m_offsets = findVersion<Offsets>(Generation1::s_checksums, checksum)->offsets;
	setTrainerName(gameTextToUTF8(&memory[G10_TRAINER_NAME], 8));
	setParty(new G1Party(this));
	for (unsigned box = 0; box < numBoxes(); ++box) {
		addBox(new G1Box(this, box));
	}
	prepareSprites();
}

Generation1::~Generation1() {
	delete [] m_spriteMemory;
	m_spriteMemory = nullptr;
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
	return GameBoyGame::findVersion<Offsets>(Generation1::s_checksums, checksum)->version;
}

unsigned Generation1::numBoxes() const {
	if ((version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		return 8;
	}
	return 12;
}

Game::Edition Generation1::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	return GameBoyGame::findVersion<Offsets>(Generation1::s_checksums, checksum)->version;
}

const Generation1::Offsets* Generation1::offsets() const {
	return m_offsets;
}

const PokemonSpecies* Generation1::species(PokemonSpecies::Id id, PokemonSpecies::Forme) {
	const PokemonSpecies* species = Game::species(id);
	if (!species) {
		const G1PokemonBaseStats* stats;
		if (id == PokemonSpecies::MEW && (version() & Game::MASK_GAME) < Game::G12_YELLOW) {
			stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[m_offsets->mewStats]);
		} else {
			stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[m_offsets->baseStats]);
			stats = &stats[(id - 1) & 0xFF];
		}
		PokemonSpecies* newSpecies = new G1PokemonSpecies(stats);
		loadSprites(newSpecies, stats);
		putSpecies(id, newSpecies);
		species = newSpecies;
	}
	return species;
}

void Generation1::finalize() {
	ram()[m_offsets->checksumEnd] = checksum();
}

bool Generation1::testChecksum() const {
	return ram()[m_offsets->checksumEnd] == checksum();
}

uint8_t Generation1::checksum() const {
	uint8_t checksum = 0xFF;
	const uint8_t* memory = ram();
	for (unsigned i = m_offsets->checksumStart; i < m_offsets->checksumEnd; ++i) {
		checksum -= memory[i];
	}
	return checksum;
}

PokemonSpecies::Id Generation1::mapId(unsigned id) const {
	const uint8_t* idMapping;
	idMapping = &rom()[m_offsets->idMapping];
	return static_cast<PokemonSpecies::Id>(idMapping[id]);
}

void Generation1::loadSprites(PokemonSpecies* species, const G1PokemonBaseStats* data) const {
	unsigned width = data->spriteDim >> 4;
	unsigned height = data->spriteDim & 0xF;

	// TODO: Handle glitch Pokemon
	const uint8_t* idMapping = &rom()[m_offsets->idMapping];
	uint8_t mapping = rom()[m_offsets->paletteMapping + species->id()];

	const uint8_t* menuIdMapping = reinterpret_cast<const uint8_t*>(&rom()[m_offsets->menuSpriteMapping]);

	int gameId;
	for (gameId = 0; gameId < 256; ++gameId) {
		if (idMapping[gameId] == species->id()) {
			break;
		}
	}

	unsigned bank;

	if (gameId == 0x15 && (version() & Game::MASK_GAME) < Game::G12_YELLOW) {
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

	uint8_t rawSpriteData[width * height * 16];
	uint8_t* spriteData = new uint8_t[width * height * 16];
	uint8_t* menuSpriteData = new uint8_t[16 * 4];
	uint8_t rawBackSpriteData[256];
	uint8_t* backSpriteData = new uint8_t[256];

	std::shared_ptr<const Palette> palette = m_palettes[mapping - 0x10];

	unsigned frontAddress = data->frontSprite;
	frontAddress = bank * 0x4000 + (frontAddress & 0x3FFF);

	unsigned backAddress = data->backSprite;
	backAddress = bank * 0x4000 + (backAddress & 0x3FFF);

	uint8_t dexId = ((species->id() - 1) & 0xFF);
	uint8_t menuSpriteId = menuIdMapping[dexId / 2];
	menuSpriteId >>= 4 * !(dexId & 1);
	menuSpriteId &= 0xF;

	const uint8_t* spritePointer = &rom()[frontAddress & (Generation1::SIZE_ROM - 1)];
	const uint8_t* backSpritePointer = &rom()[backAddress & (Generation1::SIZE_ROM - 1)];
	const uint8_t* menuSpritePointer = &m_spriteMemory[0x40 * menuSpriteId];

	G1SpriteDecompressor decomp(spritePointer, 0x400);
	decomp.decompress();
	memcpy(rawSpriteData, decomp.output(), std::min<size_t>(width * height * 16, decomp.size()));

	decomp = G1SpriteDecompressor(backSpritePointer, 0x200);
	decomp.decompress();
	memcpy(rawBackSpriteData, decomp.output(), std::min<size_t>(256, decomp.size()));

	arrangeTilesTransposed(rawSpriteData, spriteData, width, height);
	arrangeTilesTransposed(rawBackSpriteData, backSpriteData, 4, 4);
	arrangeTiles(menuSpritePointer, menuSpriteData, 2, 2);

	MultipaletteSprite* sprite = new MultipaletteSprite(width * 8, height * 8, spriteData, palette, Sprite::GB_2);
	species->setFrontSprite(sprite);

	sprite = new MultipaletteSprite(32, 32, backSpriteData, palette, Sprite::GB_2);
	species->setBackSprite(sprite);

	sprite = new MultipaletteSprite(16, 16, menuSpriteData, m_menuPalette, Sprite::GB_2);
	species->setMenuSprite(sprite);
}

void Generation1::prepareSprites() {	
	const struct LoaderCommand {
		uint16_t pointer;
		uint8_t size;
		uint8_t bank;
		uint16_t offset;
	}* commands = reinterpret_cast<const LoaderCommand*>(&rom()[m_offsets->menuSpriteCommands]);
	unsigned numCommands = G10_NUM_MENU_SPRITE_COMMANDS;

	m_spriteMemory = new uint8_t[2048];

	for (unsigned command = 0; command < numCommands; ++command) {
		size_t romAddress = commands[command].bank * 0x4000 + (commands[command].pointer & 0x3FFF);
		size_t ramAddress = commands[command].offset & 0x7FF;
		size_t size = commands[command].size * 0x10;
		if (size + ramAddress > 2048) {
			size = 2048 - ramAddress;
		}
		memcpy(&m_spriteMemory[ramAddress], &rom()[romAddress], size);
	}

	for (unsigned i = 0; i < 11; ++i) {
		if (i == 2) { // FOSSIL
			continue;
		}
		for (unsigned byte = 0; byte < 16; ++byte) {
			m_spriteMemory[0x40 * i + 0x10 + byte] = mirrorByte(m_spriteMemory[0x40 * i + byte]);
			m_spriteMemory[0x40 * i + 0x30 + byte] = mirrorByte(m_spriteMemory[0x40 * i + 0x20 + byte]);
			m_spriteMemory[0x400 + 0x40 * i + 0x10 + byte] = mirrorByte(m_spriteMemory[0x400 + 0x40 * i + byte]);
			m_spriteMemory[0x400 + 0x40 * i + 0x30 + byte] = mirrorByte(m_spriteMemory[0x400 + 0x40 * i + 0x20 + byte]);
		}
	}

	const struct GBPalette {
		uint16_t color[4];
	} __attribute__((packed))* palette = reinterpret_cast<const GBPalette*>(&rom()[m_offsets->paletteBase]);

	m_menuPalette = std::make_shared<const Palette>(palette->color, 4);

	m_palettes.clear();
	for (unsigned i = 0x10; i < 0x1A; ++i) {
		m_palettes.push_back(std::make_shared<const Palette>(palette[i].color, 4));
	}
}

uint8_t Generation1::mirrorByte(uint8_t byte) {
	uint8_t out = 0;
	out |= (byte & 0x1) << 7;
	out |= (byte & 0x2) << 5;
	out |= (byte & 0x4) << 3;
	out |= (byte & 0x8) << 1;
	out |= (byte & 0x10) >> 1;
	out |= (byte & 0x20) >> 3;
	out |= (byte & 0x40) >> 5;
	out |= (byte & 0x80) >> 7;
	return out;
}
