#include "MultipaletteSprite.h"

MultipaletteSprite::MultipaletteSprite(unsigned width, unsigned height, uint8_t* pixelData, std::shared_ptr<const Palette> palette, Format format)
	: Sprite(width, height, pixelData, palette, format)
{
}

void MultipaletteSprite::addPalette(std::shared_ptr<const Palette> palette) {
	m_additionalPalettes.push_back(palette);
}

unsigned MultipaletteSprite::numPalettes() const {
	return 1 + m_additionalPalettes.size();
}

std::shared_ptr<const Palette> MultipaletteSprite::paletteById(unsigned id) const {
	if (!id) {
		return palette();
	}
	if (id >= numPalettes()) {
		return nullptr;
	}
	return m_additionalPalettes[id - 1];
}
