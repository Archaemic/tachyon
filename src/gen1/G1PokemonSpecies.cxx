#include "gen1/G1PokemonSpecies.h"

#include "gen1/Generation1.h"
#include "gen1/G1BasePokemon.h"
#include "gen1/G1SpriteDecompressor.h"

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

	paletteData[0] = 0x7FFF;
	paletteData[1] = 0x6318;
	paletteData[2] = 0x318C;
	paletteData[3] = 0x0000;

	const uint8_t* spritePointer = &m_gen->rom()[address & (Generation1::SIZE_ROM - 1)];

	G1SpriteDecompressor decomp(spritePointer, 0x400);
	decomp.decompress();
	memcpy(rawSpriteData, decomp.output(), std::min<size_t>(width * height * 16, decomp.size()));

	for (unsigned tile = 0; tile < width * height; ++tile) {
		for (unsigned y = 0; y < 8; ++y) {
			uint16_t row = reinterpret_cast<uint16_t*>(rawSpriteData)[y + tile * 8];
			uint8_t lower = row & 0xFF;
			uint8_t upper = row >> 8;
			row = 0;
			for (int i = 0; i < 8; ++i) {
				row |= ((upper & (1 << i)) >> i) << (1 + i * 2);
				row |= ((lower & (1 << i)) >> i) << (i * 2);
			}
			reinterpret_cast<uint16_t*>(spriteData)[y * width + (tile % width) * 8 * width + tile / width] = row;
		}
	}

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
