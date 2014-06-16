#include "MultipaletteSprite.h"

MultipaletteSprite::MultipaletteSprite(unsigned width, unsigned height, uint8_t* pixelData, uint16_t* palette, Format format)
	: Sprite(width, height, pixelData, palette, format)
{
}

MultipaletteSprite::~MultipaletteSprite() {
	for (auto palette : m_additionalPalettes) {
		delete [] palette;
	}
}

void MultipaletteSprite::addPalette(uint16_t* palette) {
	m_additionalPalettes.push_back(palette);
}

unsigned MultipaletteSprite::numPalettes() const {
	return 1 + m_additionalPalettes.size();
}

const uint16_t* MultipaletteSprite::paletteById(unsigned id) const {
	if (!id) {
		return palette();
	}
	if (id >= numPalettes()) {
		return nullptr;
	}
	return m_additionalPalettes[id - 1];
}
