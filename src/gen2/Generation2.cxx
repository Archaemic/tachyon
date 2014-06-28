#include "gen2/Generation2.h"

#include "gen2/G2Box.h"
#include "gen2/G2Party.h"
#include "gen2/G2PokemonSpecies.h"

enum {
	G20_TRAINER_NAME = 0x200B,

	G20J_BASE_STATS = 0x051AA9,
	G21E_BASE_STATS = 0x051424,

	G20_SPRITE_MAPPING_BASE = 0x048000,
	G21_SPRITE_MAPPING_BASE = 0x120000,

	G20_UNOWN_SPRITE_MAPPING_BASE = 0x07C000,
	G21_UNOWN_SPRITE_MAPPING_BASE = 0x124000,

	G20GF_MENU_SPRITE_MAPPING = 0x08E977,
	G20SI_MENU_SPRITE_MAPPING = 0x08E973,
	G21E_MENU_SPRITE_MAPPING = 0x08EAC4,

	G20GF_MENU_SPRITES = 0x08EAC0,
	G20SI_MENU_SPRITES = 0x08EABC,
	G21E_MENU_SPRITES = 0x08EC0D,

	G20J_PALETTES = 0x00ACCB,
	G20X_PALETTES = 0x00AD45,
	G21E_PALETTES = 0x00A8D6,

	G20J_PARTY_POKEMON = 0x283E,
	G20X_PARTY_POKEMON = 0x288A,
	G21E_PARTY_POKEMON = 0x2865,

	G20J_BOX_SIZE = 1354,
	G20X_BOX_SIZE = 1104,

	G20J_BOX_HIGH_OFFSET = 6,
	G20X_BOX_HIGH_OFFSET = 7,

	G20J_CURRENT_BOX_ID = 0x2705,
	G20X_CURRENT_BOX_ID = 0x2724,
	G21E_CURRENT_BOX_ID = 0x2700,

	G20J_BOX_NAMES = 0x2708,
	G20X_BOX_NAMES = 0x2727,
	G21E_BOX_NAMES = 0x2703,

	G20J_CURRENT_BOX = 0x2D10,
	G20X_CURRENT_BOX = 0x2D6C,
};

static const Generation2::Offsets::ChecksumRegion G20J_CHECKSUM_1 = {
	.offset = 0x2D0D,
	.regions = {
		{ 0x2009, 0x2C8B }
	}
};

static const Generation2::Offsets::ChecksumRegion G20J_CHECKSUM_2 = {
	.offset = 0x7F0D,
	.regions = {
		{ 0x7209, 0x7E8B }
	}
};

static const Generation2::Offsets::ChecksumRegion G20X_CHECKSUM_1 = {
	.offset = 0x2D69,
	.regions = {
		{ 0x2009, 0x222F },
		{ 0x222F, 0x23D9 },
		{ 0x23D9, 0x2856 },
		{ 0x2856, 0x288A },
		{ 0x288A, 0x2D69 }
	}
};

static const Generation2::Offsets::ChecksumRegion G20X_CHECKSUM_2 = {
	.offset = 0x7E6D,
	.regions = {
		{ 0x15C7, 0x17ED },
		{ 0x3D96, 0x3F40 },
		{ 0x0C6B, 0x10E8 },
		{ 0x7E39, 0x7E6D },
		{ 0x10E8, 0x15C7 }
	}
};

static const Generation2::Offsets::ChecksumRegion G21E_CHECKSUM_1 = {
	.offset = 0x2D0D,
	.regions = {
		{ 0x2009, 0x2B83 }
	}
};

static const Generation2::Offsets::ChecksumRegion G21E_CHECKSUM_2 = {
	.offset = 0x1F0D,
	.regions = {
		{ 0x1209, 0x1D83 }
	}
};

static const Generation2::Offsets G20J = {
	.baseStats = G20J_BASE_STATS,
	.spriteMapping = G20_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = 0x08E795,
	.menuSprites = 0x08E8DE,
	.palettes = G20J_PALETTES,
	.checksumRegionsCount = 1,
	.checksumRegions = { G20J_CHECKSUM_1, G20J_CHECKSUM_2 },
	.partyPokemon = G20J_PARTY_POKEMON,
	.boxSize = G20J_BOX_SIZE,
	.boxHigh = G20J_BOX_HIGH_OFFSET,
	.currentBoxId = G20J_CURRENT_BOX_ID,
	.boxNames = G20J_BOX_NAMES,
	.currentBox = G20J_CURRENT_BOX
};

static const Generation2::Offsets G20J1 = {
	.baseStats = G20J_BASE_STATS,
	.spriteMapping = G20_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = 0x08E79A,
	.menuSprites = 0x08E8E3,
	.palettes = G20J_PALETTES,
	.checksumRegionsCount = 1,
	.checksumRegions = { G20J_CHECKSUM_1, G20J_CHECKSUM_2 },
	.partyPokemon = G20J_PARTY_POKEMON,
	.boxSize = G20J_BOX_SIZE,
	.boxHigh = G20J_BOX_HIGH_OFFSET,
	.currentBoxId = G20J_CURRENT_BOX_ID,
	.boxNames = G20J_BOX_NAMES,
	.currentBox = G20J_CURRENT_BOX
};

static const Generation2::Offsets G20E = {
	.baseStats = 0x051B0B,
	.spriteMapping = G20_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = 0x08E975,
	.menuSprites = 0x08EABE,
	.palettes = G20X_PALETTES,
	.checksumRegionsCount = 5,
	.checksumRegions = { G20X_CHECKSUM_1, G20X_CHECKSUM_2 },
	.partyPokemon = G20X_PARTY_POKEMON,
	.boxSize = G20X_BOX_SIZE,
	.boxHigh = G20X_BOX_HIGH_OFFSET,
	.currentBoxId = G20X_CURRENT_BOX_ID,
	.boxNames = G20X_BOX_NAMES,
	.currentBox = G20X_CURRENT_BOX
};

static const Generation2::Offsets G20G = {
	.baseStats = 0x051B00,
	.spriteMapping = G20_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = G20GF_MENU_SPRITE_MAPPING,
	.menuSprites = G20GF_MENU_SPRITES,
	.palettes = G20X_PALETTES,
	.checksumRegionsCount = 5,
	.checksumRegions = { G20X_CHECKSUM_1, G20X_CHECKSUM_2 },
	.partyPokemon = G20X_PARTY_POKEMON,
	.boxSize = G20X_BOX_SIZE,
	.boxHigh = G20X_BOX_HIGH_OFFSET,
	.currentBoxId = G20X_CURRENT_BOX_ID,
	.boxNames = G20X_BOX_NAMES,
	.currentBox = G20X_CURRENT_BOX
};

static const Generation2::Offsets G20F = {
	.baseStats = 0x051B10,
	.spriteMapping = G20_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = G20GF_MENU_SPRITE_MAPPING,
	.menuSprites = G20GF_MENU_SPRITES,
	.palettes = G20X_PALETTES,
	.checksumRegionsCount = 5,
	.checksumRegions = { G20X_CHECKSUM_1, G20X_CHECKSUM_2 },
	.partyPokemon = G20X_PARTY_POKEMON,
	.boxSize = G20X_BOX_SIZE,
	.boxHigh = G20X_BOX_HIGH_OFFSET,
	.currentBoxId = G20X_CURRENT_BOX_ID,
	.boxNames = G20X_BOX_NAMES,
	.currentBox = G20X_CURRENT_BOX
};

static const Generation2::Offsets G20S = {
	.baseStats = 0x051B19,
	.spriteMapping = G20_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = 0x08E973,
	.menuSprites = G20SI_MENU_SPRITES,
	.palettes = G20X_PALETTES,
	.checksumRegionsCount = 5,
	.checksumRegions = { G20X_CHECKSUM_1, G20X_CHECKSUM_2 },
	.partyPokemon = G20X_PARTY_POKEMON,
	.boxSize = G20X_BOX_SIZE,
	.boxHigh = G20X_BOX_HIGH_OFFSET,
	.currentBoxId = G20X_CURRENT_BOX_ID,
	.boxNames = G20X_BOX_NAMES,
	.currentBox = G20X_CURRENT_BOX
};

static const Generation2::Offsets G20I = {
	.baseStats = 0x051B19,
	.spriteMapping = G20_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = 0x08E973,
	.menuSprites = G20SI_MENU_SPRITES,
	.palettes = G20X_PALETTES,
	.checksumRegionsCount = 5,
	.checksumRegions = { G20X_CHECKSUM_1, G20X_CHECKSUM_2 },
	.partyPokemon = G20X_PARTY_POKEMON,
	.boxSize = G20X_BOX_SIZE,
	.boxHigh = G20X_BOX_HIGH_OFFSET,
	.currentBoxId = G20X_CURRENT_BOX_ID,
	.boxNames = G20X_BOX_NAMES,
	.currentBox = G20X_CURRENT_BOX
};

static const Generation2::Offsets G21E = {
	.baseStats = G21E_BASE_STATS,
	.spriteMapping = G21_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G21_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = G21E_MENU_SPRITE_MAPPING,
	.menuSprites = G21E_MENU_SPRITES,
	.palettes = G21E_PALETTES,
	.checksumRegionsCount = 1,
	.checksumRegions = { G21E_CHECKSUM_1, G21E_CHECKSUM_2 },
	.partyPokemon = G21E_PARTY_POKEMON,
	.boxSize = G20X_BOX_SIZE,
	.boxHigh = G20X_BOX_HIGH_OFFSET,
	.currentBoxId = G21E_CURRENT_BOX_ID,
	.boxNames = G21E_BOX_NAMES,
	.currentBox = G20J_CURRENT_BOX
};

const GameBoyGame::ChecksumMapping<Generation2::Offsets> Generation2::s_checksums[] = {
	{ 0x708A, Game::G20_GOLD | Game::JAPANESE, &G20J },
	{ 0x6084, Game::G20_GOLD | Game::JAPANESE, &G20J1 },
	{ 0x2D68, Game::G20_GOLD | Game::ENGLISH, &G20E },
	{ 0x97DC, Game::G20_GOLD | Game::GERMAN, &G20G },
	{ 0xC66F, Game::G20_GOLD | Game::FRENCH, &G20F },
	{ 0x5393, Game::G20_GOLD | Game::SPANISH, &G20S },
	{ 0x0CCE, Game::G20_GOLD | Game::ITALIAN, &G20I },
	{ 0x9176, Game::G20_SILVER | Game::JAPANESE, &G20J },
	{ 0x341D, Game::G20_SILVER | Game::JAPANESE, &G20J1 },
	{ 0xAE0D, Game::G20_SILVER | Game::ENGLISH, &G20E },
	{ 0x6ECD, Game::G20_SILVER | Game::GERMAN, &G20G },
	{ 0x8CFB, Game::G20_SILVER | Game::FRENCH, &G20F },
	{ 0x4B06, Game::G20_SILVER | Game::SPANISH, &G20S },
	{ 0x5073, Game::G20_SILVER | Game::ITALIAN, &G20I },
	{ 0x9F12, Game::G21_CRYSTAL | Game::ENGLISH, &G21E },
	{ 0, Game::INVALID, nullptr }
};

Generation2::Generation2(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
{
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	m_offsets = findVersion<Offsets>(Generation2::s_checksums, checksum)->offsets;
	setTrainerName(gameTextToUTF8(&memory[G20_TRAINER_NAME], 8));
	setParty(new G2Party(this));
	for (unsigned box = 0; box < numBoxes(); ++box) {
		addBox(new G2Box(this, box));
	}

	uint16_t menuPaletteData[4];
	menuPaletteData[0] = 0x6FFB;
	menuPaletteData[1] = 0x2A7F;
	menuPaletteData[2] = 0x10FF;
	menuPaletteData[3] = 0x0000;
	m_menuPalette = std::make_shared<const Palette>(menuPaletteData, 4);
}

void Generation2::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Generation2* Generation2::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	if (detect(rom)) {
		return new Generation2(memory, rom);
	}
	return nullptr;
}

Game::Edition Generation2::Loader::detect(const uint8_t* rom) const {
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	return GameBoyGame::findVersion<Offsets>(Generation2::s_checksums, checksum)->version;
}

unsigned Generation2::numBoxes() const {
	if ((version() & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
		return 9;
	}
	return 14;
}

Game::Edition Generation2::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	return GameBoyGame::findVersion<Offsets>(s_checksums, checksum)->version;
}

const Generation2::Offsets* Generation2::offsets() const {
	return m_offsets;
}

const PokemonSpecies* Generation2::species(PokemonSpecies::Id id, PokemonSpecies::Forme forme) {
	const PokemonSpecies* species = Game::species(id, forme);
	if (!species) {
		const G2PokemonBaseStats* stats = reinterpret_cast<const G2PokemonBaseStats*>(&rom()[m_offsets->baseStats]);
		if (id <= 251) {
			stats = &stats[id - 1];
		} else {
			stats = &stats[-1];
		}
		PokemonSpecies* newSpecies = new G2PokemonSpecies(stats, forme);
		loadSprites(newSpecies, stats);
		putSpecies(id, newSpecies, forme);
		species = newSpecies;
	}
	return species;
}

void Generation2::finalize() {
	uint16_t sum = checksum();
	uint8_t* memory = ram();
	*reinterpret_cast<uint16_t*>(&memory[m_offsets->checksumRegions[0].offset]) = sum;
	*reinterpret_cast<uint16_t*>(&memory[m_offsets->checksumRegions[1].offset]) = sum;
	for (unsigned i = 0; i < m_offsets->checksumRegionsCount; ++i) {
		unsigned start = m_offsets->checksumRegions[0].regions[i].start;
		unsigned newStart = m_offsets->checksumRegions[1].regions[i].start;
		unsigned end = m_offsets->checksumRegions[0].regions[i].end;
		memmove(&memory[newStart], &memory[start], end - start);
	}
}

bool Generation2::testChecksum() const {
	uint16_t sum = checksum();
	const uint8_t* memory = ram();
	if (*reinterpret_cast<const uint16_t*>(&memory[m_offsets->checksumRegions[0].offset]) == sum) {
		return true;
	}
	if (*reinterpret_cast<const uint16_t*>(&memory[m_offsets->checksumRegions[1].offset]) == sum) {
		return true;
	}
	return false;
}

uint16_t Generation2::checksum() const {
	uint16_t checksum = 0;
	const uint8_t* memory = ram();
	for (unsigned i = 0; i < m_offsets->checksumRegionsCount; ++i) {
		unsigned start = m_offsets->checksumRegions[0].regions[i].start;
		unsigned end = m_offsets->checksumRegions[0].regions[i].end;
		for (unsigned offset = 0; offset < end - start; ++offset) {
			checksum += memory[start + offset];
		}
	}
	return checksum;
}

void Generation2::loadSprites(PokemonSpecies* species, const G2PokemonBaseStats* data) const {
	if (species->id() > PokemonSpecies::CELEBI) {
		return;
	}

	unsigned size = data->spriteDim & 0xF;
	if (!size) {
		return;
	}

	const struct Mapping {
		uint8_t frontBank;
		uint16_t frontPointer;
		uint8_t backBank;
		uint16_t backPointer;
	} __attribute__((packed))* mapping;

	const struct PaletteInfo {
		uint16_t colorA;
		uint16_t colorB;
		uint16_t shinyColorA;
		uint16_t shinyColorB;
	} __attribute__((packed))* paletteMemory;

	const uint8_t* menuSpritePointer = nullptr;
	if (species->id() != PokemonSpecies::UNOWN) {
		mapping = &reinterpret_cast<const Mapping*>(&rom()[m_offsets->spriteMapping])[species->id() - 1];
	} else {
		mapping = &reinterpret_cast<const Mapping*>(&rom()[m_offsets->unownSpriteMapping])[species->forme()];
	}
	paletteMemory = &reinterpret_cast<const PaletteInfo*>(&rom()[m_offsets->palettes])[species->id() - 1];
	menuSpritePointer = &rom()[m_offsets->menuSpriteMapping];
	menuSpritePointer = &rom()[m_offsets->menuSprites + (menuSpritePointer[species->id() - 1] - 1) * 0x80];

	unsigned frontBank = mapping->frontBank;
	unsigned backBank = mapping->backBank;
	if ((version() & MASK_GAME) == Game::G21_CRYSTAL) {
		frontBank += 0x36;
		backBank += 0x36;
	}

	switch (frontBank) {
	case 0x13:
	case 0x14:
		frontBank += 0xC;
		break;
	case 0x1F:
		frontBank += 0xF;
		break;
	}

	switch (backBank) {
	case 0x13:
	case 0x14:
		backBank += 0xC;
		break;
	case 0x1F:
		backBank += 0xF;
		break;
	}

	unsigned frontAddress = mapping->frontPointer;
	frontAddress = frontBank * 0x4000 + (frontAddress & 0x3FFF);
	unsigned backAddress = mapping->backPointer;
	backAddress = backBank * 0x4000 + (backAddress & 0x3FFF);

	uint8_t rawSpriteData[size * size * 16];
	uint8_t* spriteData = new uint8_t[size * size * 16];
	uint8_t rawBackSpriteData[6 * 6 * 16];
	uint8_t* backSpriteData = new uint8_t[6 * 6 * 16];
	uint8_t* menuSpriteData = new uint8_t[2 * 2 * 16];
	uint16_t paletteData[4];
	uint16_t shinyPaletteData[4];

	paletteData[0] = 0x7FFF;
	paletteData[1] = paletteMemory->colorA;
	paletteData[2] = paletteMemory->colorB;
	paletteData[3] = 0x0000;
	shinyPaletteData[0] = 0x7FFF;
	shinyPaletteData[1] = paletteMemory->shinyColorA;
	shinyPaletteData[2] = paletteMemory->shinyColorB;
	shinyPaletteData[3] = 0x0000;

	std::shared_ptr<const Palette> palette = std::make_shared<const Palette>(paletteData, 4);
	std::shared_ptr<const Palette> shinyPalette = std::make_shared<const Palette>(shinyPaletteData, 4);

	const uint8_t* spritePointer = &rom()[frontAddress & (SIZE_ROM - 1)];
	const uint8_t* backSpritePointer = &rom()[backAddress & (SIZE_ROM - 1)];
	lzDecompress(spritePointer, rawSpriteData, size * size * 16);
	lzDecompress(backSpritePointer, rawBackSpriteData, 6 * 6 * 16);

	arrangeTilesTransposed(rawSpriteData, spriteData, size, size);
	arrangeTilesTransposed(rawBackSpriteData, backSpriteData, 6, 6);

	MultipaletteSprite* sprite = new MultipaletteSprite(size * 8, size * 8, spriteData, palette, Sprite::GB_2);
	sprite->addPalette(shinyPalette);
	species->setFrontSprite(sprite);

	sprite = new MultipaletteSprite(6 * 8, 6 * 8, backSpriteData, palette, Sprite::GB_2);
	sprite->addPalette(shinyPalette);
	species->setBackSprite(sprite);

	if (menuSpritePointer) {
		arrangeTiles(menuSpritePointer, menuSpriteData, 2, 2);

		sprite = new MultipaletteSprite(16, 16, menuSpriteData, m_menuPalette, Sprite::GB_2);
		sprite->addPalette(m_menuPalette);
		species->setMenuSprite(sprite);
	}
}

void Generation2::lzDecompress(const uint8_t* source, uint8_t* dest, size_t maxLength) {
	uint8_t* decompressed = dest;
	while (1) {
		uint8_t byte = *source;
		++source;
		if (byte == 0xFF) {
			break;
		}

		enum Command {
			LITERAL,
			REPEAT,
			ALTERNATE,
			ZERO,
			COPY,
			MIRROR_BITS,
			MIRROR_BYTES,
			LONG
		} command = static_cast<Command>(byte >> 5);

		unsigned length;
		if (command == 7) {
			length = (byte & 0x3) << 8;
			command = static_cast<Command>((byte >> 2) & 7);
			length += *source + 1;
			++source;
		} else {
			length = (byte & 0x1F) + 1;
		}

		switch (command) {
		case LITERAL:
			for (unsigned i = 0; i < length; ++i) {
				*dest = *source;
				++source;
				++dest;
				--maxLength;
				if (maxLength == 0) {
					return;
				}
			}
			break;
		case REPEAT:
			byte = *source;
			++source;
			for (unsigned i = 0; i < length; ++i) {
				*dest = byte;
				++dest;
				--maxLength;
				if (maxLength == 0) {
					return;
				}
			}
			break;
		case ALTERNATE:
			uint8_t byte2;
			byte = *source;
			++source;
			byte2 = *source;
			++source;
			for (unsigned i = 0; i < length; ++i) {
				if (i & 1) {
					*dest = byte2;
				} else {
					*dest = byte;
				}
				++dest;
				--maxLength;
				if (maxLength == 0) {
					return;
				}
			}
			break;
		case ZERO:
			for (unsigned i = 0; i < length; ++i) {
				*dest = 0;
				++dest;
				--maxLength;
				if (maxLength == 0) {
					return;
				}
			}
			break;
		case COPY:
		case MIRROR_BITS:
		case MIRROR_BYTES:
			int offset;
			uint8_t* backtrack;
			offset = *source;
			++source;
			if (offset > 0x7F) {
				backtrack = dest - (offset & 0x7F) - 1;
			} else {
				offset <<= 8;
				offset += *source;
				++source;
				backtrack = decompressed + offset;
			}
			switch (command) {
			case COPY:
				for (unsigned i = 0; i < length; ++i) {
					if (backtrack >= decompressed && backtrack < dest) {
						*dest = *backtrack;
					} else {
						*dest = 0;
					}
					++backtrack;
					++dest;
					--maxLength;
					if (maxLength == 0) {
						return;
					}
				}
				break;
			case MIRROR_BITS:
				for (unsigned i = 0; i < length; ++i) {
					*dest = 0;
					if (backtrack >= decompressed && backtrack < dest) {
						byte = *backtrack;
						for (int bit = 0; bit < 8; ++bit) {
							*dest |= ((byte & (1 << bit)) >> bit) << (7 - bit);
						}
					}
					++backtrack;
					++dest;
					--maxLength;
					if (maxLength == 0) {
						return;
					}
				}
				break;
			case MIRROR_BYTES:
				for (unsigned i = 0; i < length; ++i) {
					if (backtrack >= decompressed && backtrack < dest) {
						*dest = *backtrack;
					} else {
						*dest = 0;
					}
					--backtrack;
					++dest;
					--maxLength;
					if (maxLength == 0) {
						return;
					}
				}
				break;
			default:
				break;
			}
			break;
		case LONG:
			break;
		}
	}
}
