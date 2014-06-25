#include "gen2/Generation2.h"

#include "gen2/G2Box.h"
#include "gen2/G2Party.h"
#include "gen2/G2PokemonSpecies.h"

enum {
	G20E_TRAINER_NAME = 0x200B,
	G20_CHECKSUM_1 = 0x2D69,
	G20_CHECKSUM_2 = 0x7E6D,
	G21_CHECKSUM_1 = 0x2D0D,
	G21_CHECKSUM_2 = 0x1F0D,

	G20J_BASE_STATS = 0x051AA9,
	G20E_BASE_STATS = 0x051B0B,
	G21E_BASE_STATS = 0x051424,

	G20E_SPRITE_MAPPING_BASE = 0x048000,
	G21E_SPRITE_MAPPING_BASE = 0x120000,

	G20E_UNOWN_SPRITE_MAPPING_BASE = 0x07C000,
	G21E_UNOWN_SPRITE_MAPPING_BASE = 0x124000,

	G20E_MENU_SPRITE_MAPPING = 0x08E975,
	G21E_MENU_SPRITE_MAPPING = 0x08EAC4,

	G20E_MENU_SPRITES = 0x08EABE,
	G21E_MENU_SPRITES = 0x08EC0D,

	G20J_PALETTES = 0x00ACCB,
	G20E_PALETTES = 0x00AD45,
	G21E_PALETTES = 0x00A8D6,
};

struct Range {
	unsigned start;
	unsigned end;
};

static const Range checksumRegionsG20E[2][5] = {
	{
		{ 0x2009, 0x222F },
		{ 0x222F, 0x23D9 },
		{ 0x23D9, 0x2856 },
		{ 0x2856, 0x288A },
		{ 0x288A, 0x2D69 }
	},
	{
		{ 0x15C7, 0x17ED },
		{ 0x3D96, 0x3F40 },
		{ 0x0C6B, 0x10E8 },
		{ 0x7E39, 0x7E6D },
		{ 0x10E8, 0x15C7 }
	}
};

static const Range checksumRegionsG21E[2] = {
	{ 0x2009, 0x2B83 },
	{ 0x1209, 0x1D83 }
};

static const Generation2::Offsets G20E = {
	.baseStats = G20E_BASE_STATS,
	.spriteMapping = G20E_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20E_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = G20E_MENU_SPRITE_MAPPING,
	.menuSprites = G20E_MENU_SPRITES,
	.palettes = G20E_PALETTES
};

static const Generation2::Offsets G20J = {
	.baseStats = G20J_BASE_STATS,
	.spriteMapping = G20E_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G20E_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = G20E_MENU_SPRITE_MAPPING,
	.menuSprites = G20E_MENU_SPRITES,
	.palettes = G20J_PALETTES
};

static const Generation2::Offsets G21E = {
	.baseStats = G21E_BASE_STATS,
	.spriteMapping = G21E_SPRITE_MAPPING_BASE,
	.unownSpriteMapping = G21E_UNOWN_SPRITE_MAPPING_BASE,
	.menuSpriteMapping = G21E_MENU_SPRITE_MAPPING,
	.menuSprites = G21E_MENU_SPRITES,
	.palettes = G21E_PALETTES
};

const GameBoyGame::ChecksumMapping<Generation2::Offsets> Generation2::s_checksums[] = {
	{ 0x708A, Game::G20_GOLD | Game::JAPANESE, &G20J },
	{ 0x6084, Game::G20_GOLD | Game::JAPANESE, &G20J },
	{ 0x2D68, Game::G20_GOLD | Game::ENGLISH, &G20E },
	{ 0, Game::INVALID, nullptr }
};

Generation2::Generation2(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
{
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	m_offsets = findVersion<Offsets>(Generation2::s_checksums, checksum)->offsets;
	setTrainerName(gameTextToUTF8(&memory[G20E_TRAINER_NAME], 8));
	setParty(new G2Party(this));
	for (unsigned box = 0; box < numBoxes(); ++box) {
		addBox(new G2Box(this, box));
	}
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
	uint16_t checksum = 0;
	uint8_t* memory = ram();
	switch (version() & Game::MASK_GAME) {
	case Game::G20_GOLD:
	case Game::G20_SILVER:
	default:
		for (unsigned i = 0; i < 5; ++i) {
			unsigned start = checksumRegionsG20E[0][i].start;
			unsigned newStart = checksumRegionsG20E[1][i].start;
			unsigned end = checksumRegionsG20E[0][i].end;
			for (unsigned offset = 0; offset < end - start; ++offset) {
				checksum += memory[start + offset];
				memory[newStart + offset] = memory[start + offset];
			}
		}
		*reinterpret_cast<uint16_t*>(&memory[G20_CHECKSUM_1]) = checksum;
		*reinterpret_cast<uint16_t*>(&memory[G20_CHECKSUM_2]) = checksum;
		break;
	case Game::G21_CRYSTAL:
		unsigned start = checksumRegionsG21E[0].start;
		unsigned newStart = checksumRegionsG21E[1].start;
		unsigned end = checksumRegionsG21E[0].end;
		for (unsigned offset = 0; offset < end - start; ++offset) {
			checksum += memory[start + offset];
			memory[newStart + offset] = memory[start + offset];
		}
		*reinterpret_cast<uint16_t*>(&memory[G21_CHECKSUM_1]) = checksum;
		*reinterpret_cast<uint16_t*>(&memory[G21_CHECKSUM_2]) = checksum;
		break;
	}
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

	const struct Palette {
		uint16_t colorA;
		uint16_t colorB;
		uint16_t shinyColorA;
		uint16_t shinyColorB;
	} __attribute__((packed))* palette;

	const uint8_t* menuSpritePointer = nullptr;
	if (species->id() != PokemonSpecies::UNOWN) {
		mapping = &reinterpret_cast<const Mapping*>(&rom()[m_offsets->spriteMapping])[species->id() - 1];
	} else {
		mapping = &reinterpret_cast<const Mapping*>(&rom()[m_offsets->unownSpriteMapping])[species->forme()];
	}
	palette = &reinterpret_cast<const Palette*>(&rom()[m_offsets->palettes])[species->id() - 1];
	menuSpritePointer = &rom()[m_offsets->menuSpriteMapping];
	menuSpritePointer = &rom()[m_offsets->menuSprites + (menuSpritePointer[species->id() - 1] - 1) * 0x80];

	unsigned frontBank = mapping->frontBank;
	unsigned backBank = mapping->backBank;
	if ((version() & MASK_GAME) == Game::G21_CRYSTAL) {
		frontBank += 0x36;
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

	uint8_t* rawSpriteData = new uint8_t[size * size * 16];
	uint8_t* spriteData = new uint8_t[size * size * 16];
	uint8_t* rawBackSpriteData = new uint8_t[6 * 6 * 16];
	uint8_t* backSpriteData = new uint8_t[6 * 6 * 16];
	uint8_t* menuSpriteData = new uint8_t[2 * 2 * 16];
	uint16_t* paletteData = new uint16_t[16];
	uint16_t* shinyPaletteData = new uint16_t[16];
	uint16_t* backPaletteData = new uint16_t[16];
	uint16_t* shinyBackPaletteData = new uint16_t[16];
	uint16_t* menuPaletteData = new uint16_t[16];
	uint16_t* shinyMenuPaletteData = new uint16_t[16];

	paletteData[0] = 0x7FFF;
	paletteData[1] = palette->colorA;
	paletteData[2] = palette->colorB;
	paletteData[3] = 0x0000;
	shinyPaletteData[0] = 0x7FFF;
	shinyPaletteData[1] = palette->shinyColorA;
	shinyPaletteData[2] = palette->shinyColorB;
	shinyPaletteData[3] = 0x0000;
	backPaletteData[0] = 0x7FFF;
	backPaletteData[1] = palette->colorA;
	backPaletteData[2] = palette->colorB;
	backPaletteData[3] = 0x0000;
	shinyBackPaletteData[0] = 0x7FFF;
	shinyBackPaletteData[1] = palette->shinyColorA;
	shinyBackPaletteData[2] = palette->shinyColorB;
	shinyBackPaletteData[3] = 0x0000;
	menuPaletteData[0] = 0x6FFB;
	menuPaletteData[1] = 0x2A7F;
	menuPaletteData[2] = 0x10FF;
	menuPaletteData[3] = 0x0000;
	shinyMenuPaletteData[0] = 0x6FFB;
	shinyMenuPaletteData[1] = 0x2A7F;
	shinyMenuPaletteData[2] = 0x10FF;
	shinyMenuPaletteData[3] = 0x0000;

	const uint8_t* spritePointer = &rom()[frontAddress & (SIZE_ROM - 1)];
	const uint8_t* backSpritePointer = &rom()[backAddress & (SIZE_ROM - 1)];
	lzDecompress(spritePointer, rawSpriteData, size * size * 16);
	lzDecompress(backSpritePointer, rawBackSpriteData, 6 * 6 * 16);

	arrangeTilesTransposed(rawSpriteData, spriteData, size, size);
	arrangeTilesTransposed(rawBackSpriteData, backSpriteData, 6, 6);

	delete [] rawSpriteData;
	delete [] rawBackSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(size * 8, size * 8, spriteData, paletteData, Sprite::GB_2);
	sprite->addPalette(shinyPaletteData);
	species->setFrontSprite(sprite);

	sprite = new MultipaletteSprite(6 * 8, 6 * 8, backSpriteData, backPaletteData, Sprite::GB_2);
	sprite->addPalette(shinyBackPaletteData);
	species->setBackSprite(sprite);

	if (menuSpritePointer) {
		arrangeTiles(menuSpritePointer, menuSpriteData, 2, 2);

		sprite = new MultipaletteSprite(16, 16, menuSpriteData, menuPaletteData, Sprite::GB_2);
		sprite->addPalette(shinyMenuPaletteData);
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
