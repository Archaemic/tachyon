#include "gen2/Generation2.h"

#include "gen2/G2Box.h"
#include "gen2/G2Party.h"
#include "gen2/G2PokemonSpecies.h"

enum {
	G20E_TRAINER_NAME = 0x200B,
	G20E_CHECKSUM_1 = 0x2D69,
	G20E_CHECKSUM_2 = 0x7E6D,
	G21E_CHECKSUM_1 = 0x2D0D,
	G21E_CHECKSUM_2 = 0x1F0D,

	G20E_BASE_STATS = 0x051B0B,
	G21E_BASE_STATS = 0x051424,

	G20E_SPRITE_MAPPING_BASE = 0x048000,
	G21E_SPRITE_MAPPING_BASE = 0x120000,

	G20E_UNOWN_SPRITE_MAPPING_BASE = 0x07C000,
	G21E_UNOWN_SPRITE_MAPPING_BASE = 0x124000,

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

const GameBoyGame::ChecksumMapping Generation2::s_checksums[] = {
	{ 0x2D68, Game::G20E_GOLD },
	{ 0, Game::INVALID }
};

Generation2::Generation2(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
{
	setTrainerName(gameTextToUTF8(&memory[G20E_TRAINER_NAME], 8));
	setParty(new G2Party(this));
	for (unsigned box = 0; box < numBoxes(); ++box) {
		addBox(new G2Box(this, box));
	}
}

void Generation2::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Game* Generation2::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	if (GameBoyGame::version(Generation2::s_checksums, checksum)) {
		return new Generation2(memory, rom);
	}
	return nullptr;
}

unsigned Generation2::numBoxes() const {
	return 14;
}

Game::Version Generation2::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	return GameBoyGame::version(s_checksums, checksum);
}

PokemonSpecies* Generation2::species(PokemonSpecies::Id id) {
	PokemonSpecies* species = Game::species(id);
	if (!species) {
		const G2PokemonBaseStats* stats;
		switch (version()) {
		case Game::G20E_GOLD:
		case Game::G20J_GOLD:
		case Game::G20E_SILVER:
		case Game::G20J_SILVER:
		default:
			stats = reinterpret_cast<const G2PokemonBaseStats*>(&rom()[G20E_BASE_STATS]);
			break;
		case Game::G21E_CRYSTAL:
		case Game::G21J_CRYSTAL:
			stats = reinterpret_cast<const G2PokemonBaseStats*>(&rom()[G20E_BASE_STATS]);
			break;
		}
		if (id <= 251) {
			species = new G2PokemonSpecies(this, &stats[id - 1]);
		} else {
			species = new G2PokemonSpecies(this, &stats[-1]);
		}
		putSpecies(id, species);
	}
	return species;
}

void Generation2::finalize() {
	uint16_t checksum = 0;
	uint8_t* memory = ram();
	switch (version()) {
	case Game::G20E_GOLD:
	case Game::G20J_GOLD:
	case Game::G20E_SILVER:
	case Game::G20J_SILVER:
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
		*reinterpret_cast<uint16_t*>(&memory[G20E_CHECKSUM_1]) = checksum;
		*reinterpret_cast<uint16_t*>(&memory[G20E_CHECKSUM_2]) = checksum;
		break;
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
		unsigned start = checksumRegionsG21E[0].start;
		unsigned newStart = checksumRegionsG21E[1].start;
		unsigned end = checksumRegionsG21E[0].end;
		for (unsigned offset = 0; offset < end - start; ++offset) {
			checksum += memory[start + offset];
			memory[newStart + offset] = memory[start + offset];
		}
		*reinterpret_cast<uint16_t*>(&memory[G21E_CHECKSUM_1]) = checksum;
		*reinterpret_cast<uint16_t*>(&memory[G21E_CHECKSUM_2]) = checksum;
		break;
	}
}

std::unique_ptr<MultipaletteSprite> Generation2::frontSprite(PokemonSpecies::Id id, unsigned size) const {
	if (id > PokemonSpecies::CELEBI) {
		return nullptr;
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

	switch (version()) {
	case Game::G20E_GOLD:
	case Game::G20J_GOLD:
	case Game::G20E_SILVER:
	case Game::G20J_SILVER:
	default:
		mapping = &reinterpret_cast<const Mapping*>(&rom()[G20E_SPRITE_MAPPING_BASE])[id - 1];
		palette = &reinterpret_cast<const Palette*>(&rom()[G20E_PALETTES])[id - 1];
		break;
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
		mapping = &reinterpret_cast<const Mapping*>(&rom()[G21E_SPRITE_MAPPING_BASE])[id - 1];
		palette = &reinterpret_cast<const Palette*>(&rom()[G21E_PALETTES])[id - 1];
		break;
	}

	unsigned bank = mapping->frontBank;
	switch (version()) {
	case G21E_CRYSTAL:
	case G21J_CRYSTAL:
		bank += 0x36;
		break;
	default:
		break;
	}

	switch (bank) {
	case 0x13:
	case 0x14:
		bank += 0xC;
		break;
	case 0x1F:
		bank += 0xF;
		break;
	}

	unsigned address = mapping->frontPointer;
	address = bank * 0x4000 + (address & 0x3FFF);

	uint8_t* rawSpriteData = new uint8_t[size * size * 16];
	uint8_t* spriteData = new uint8_t[size * size * 16];
	uint16_t* paletteData = new uint16_t[16];
	uint16_t* shinyPaletteData = new uint16_t[16];

	paletteData[0] = 0x7FFF;
	paletteData[1] = palette->colorA;
	paletteData[2] = palette->colorB;
	paletteData[3] = 0x0000;
	shinyPaletteData[0] = 0x7FFF;
	shinyPaletteData[1] = palette->shinyColorA;
	shinyPaletteData[2] = palette->shinyColorB;
	shinyPaletteData[3] = 0x0000;

	const uint8_t* spritePointer = &rom()[address & (SIZE_ROM - 1)];
	lzDecompress(spritePointer, rawSpriteData, size * size * 16);

	for (unsigned tile = 0; tile < size * size; ++tile) {
		for (unsigned y = 0; y < 8; ++y) {
			uint16_t row = reinterpret_cast<uint16_t*>(rawSpriteData)[y + tile * 8];
			uint8_t lower = row & 0xFF;
			uint8_t upper = row >> 8;
			row = 0;
			for (int i = 0; i < 8; ++i) {
				row |= ((upper & (1 << i)) >> i) << (1 + i * 2);
				row |= ((lower & (1 << i)) >> i) << (i * 2);
			}
			reinterpret_cast<uint16_t*>(spriteData)[y * size + (tile % size) * 8 * size + tile / size] = row;
		}
	}

	delete [] rawSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(size * 8, size * 8, spriteData, paletteData, Sprite::GB_2);
	sprite->addPalette(shinyPaletteData);
	return std::unique_ptr<MultipaletteSprite>(sprite);
}

void Generation2::lzDecompress(const uint8_t* source, uint8_t* dest, size_t maxLength) const {
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
