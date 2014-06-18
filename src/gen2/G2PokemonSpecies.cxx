#include "gen2/G2PokemonSpecies.h"

#include "common/GameBoyGame.h"
#include "gen2/Generation2.h"

enum {
	G20E_SPRITE_MAPPING_BASE = 0x048000,
	G21E_SPRITE_MAPPING_BASE = 0x120000,

	G20E_UNOWN_SPRITE_MAPPING_BASE = 0x07C000,
	G21E_UNOWN_SPRITE_MAPPING_BASE = 0x124000,

	G20E_PALETTES = 0x00AD45,
	G21E_PALETTES = 0x00A8D6,
};

G2PokemonSpecies::G2PokemonSpecies(const Generation2* gen, const G2PokemonBaseStats* data, PokemonSpecies::Forme forme)
	: GenericPokemonSpecies<G2PokemonBaseStats>(data)
	, m_gen(gen)
	, m_forme(forme)
	, m_frontSprite(nullptr)
{
	loadSprites();
}

void G2PokemonSpecies::loadSprites() {
	if (id() > PokemonSpecies::CELEBI) {
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

	switch (m_gen->version()) {
	case Game::G20E_GOLD:
	case Game::G20J_GOLD:
	case Game::G20E_SILVER:
	case Game::G20J_SILVER:
	default:
		if (id() != PokemonSpecies::UNOWN) {
			mapping = &reinterpret_cast<const Mapping*>(&m_gen->rom()[G20E_SPRITE_MAPPING_BASE])[id() - 1];
		} else {
			mapping = &reinterpret_cast<const Mapping*>(&m_gen->rom()[G20E_UNOWN_SPRITE_MAPPING_BASE])[m_forme];
		}
		palette = &reinterpret_cast<const Palette*>(&m_gen->rom()[G20E_PALETTES])[id() - 1];
		break;
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
		if (id() != PokemonSpecies::UNOWN) {
			mapping = &reinterpret_cast<const Mapping*>(&m_gen->rom()[G21E_SPRITE_MAPPING_BASE])[id() - 1];
		} else {
			mapping = &reinterpret_cast<const Mapping*>(&m_gen->rom()[G21E_UNOWN_SPRITE_MAPPING_BASE])[m_forme];
		}
		palette = &reinterpret_cast<const Palette*>(&m_gen->rom()[G21E_PALETTES])[id() - 1];
		break;
	}

	unsigned bank = mapping->frontBank;
	switch (m_gen->version()) {
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
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

	unsigned size = m_data->spriteDim & 0xF;

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

	const uint8_t* spritePointer = &m_gen->rom()[address & (Generation2::SIZE_ROM - 1)];
	m_gen->lzDecompress(spritePointer, rawSpriteData, size * size * 16);

	GameBoyGame::arrangeTiles(rawSpriteData, spriteData, size, size);

	delete [] rawSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(size * 8, size * 8, spriteData, paletteData, Sprite::GB_2);
	sprite->addPalette(shinyPaletteData);
	m_frontSprite = std::unique_ptr<MultipaletteSprite>(sprite);
}

PokemonSpecies::Forme G2PokemonSpecies::forme() const {
	return m_forme;
}

const MultipaletteSprite* G2PokemonSpecies::frontSprite() const {
	return m_frontSprite.get();
}

Type G2PokemonSpecies::mapType(unsigned unmapped) const {
	return GameBoyGame::typeMapping[static_cast<uint8_t>(unmapped)];
}
