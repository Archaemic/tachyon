#include "gen1/G1PokemonSpecies.h"

#include "gen1/Generation1.h"
#include "gen1/G1BasePokemon.h"
#include "gen1/G1SpriteDecompressor.h"

enum {
	G10E_PALETTE_MAPPING = 0x725C8,
	G10E_PALETTES = 0x72660
};

template <>
unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialAttack() const {
	return m_data->special;
}

template <>
unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialDefense() const {
	return m_data->special;
}

template <>
uint8_t GenericPokemonSpecies<G1PokemonBaseStats>::genderRatio() const {
	if (id() == PokemonSpecies::NIDORAN_F) {
		return 0xFE;
	}
	if (id() == PokemonSpecies::NIDORAN_M) {
		return 0x00;
	}
	return 0xFF;
}

G1PokemonSpecies::G1PokemonSpecies(const Generation1* gen, const G1PokemonBaseStats* data)
	: GenericPokemonSpecies<G1PokemonBaseStats>(data)
	, m_gen(gen)
{
	loadSprites();
}

void G1PokemonSpecies::loadSprites() {
	unsigned width = m_data->spriteDim >> 4;
	unsigned height = m_data->spriteDim & 0xF;

	// TODO: Handle glitch Pokemon
	const uint8_t* idMapping = &m_gen->rom()[G10E_ID_MAPPING];
	int gameId;
	for (gameId = 0; gameId < 256; ++gameId) {
		if (idMapping[gameId] == id()) {
			break;
		}
	}

	uint8_t mapping = m_gen->rom()[G10E_PALETTE_MAPPING + id()];

	const struct Palette {
		uint16_t color[4];
	} __attribute__((packed))* palette = &reinterpret_cast<const Palette*>(&m_gen->rom()[G10E_PALETTES])[mapping];

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

	unsigned address = m_data->frontSprite;
	address = bank * 0x4000 + (address & 0x3FFF);

	uint8_t* rawSpriteData = new uint8_t[width * height * 16];
	uint8_t* spriteData = new uint8_t[width * height * 16];
	uint16_t* paletteData = new uint16_t[16];

	paletteData[0] = palette->color[0];
	paletteData[1] = palette->color[1];
	paletteData[2] = palette->color[2];
	paletteData[3] = palette->color[3];

	const uint8_t* spritePointer = &m_gen->rom()[address & (Generation1::SIZE_ROM - 1)];

	G1SpriteDecompressor decomp(spritePointer, 0x400);
	decomp.decompress();
	memcpy(rawSpriteData, decomp.output(), std::min<size_t>(width * height * 16, decomp.size()));

	GameBoyGame::arrangeTiles(rawSpriteData, spriteData, width, height);

	delete [] rawSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(width * 8, height * 8, spriteData, paletteData, Sprite::GB_2);
	m_frontSprite = std::unique_ptr<MultipaletteSprite>(sprite);
}

const MultipaletteSprite* G1PokemonSpecies::frontSprite() const
{
	return m_frontSprite.get();
}

Type G1PokemonSpecies::mapType(unsigned unmapped) const {
	return GameBoyGame::typeMapping[static_cast<uint8_t>(unmapped)];
}
