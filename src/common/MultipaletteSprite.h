#ifndef PTXN_MULTIPALETTE_SPRITE_H
#define PTXN_MULTIPALETTE_SPRITE_H

#include "Sprite.h"

#include <vector>

class MultipaletteSprite : public Sprite {
public:
	MultipaletteSprite(unsigned width, unsigned height, uint8_t* pixelData, std::shared_ptr<const Palette> palette, Format format);

	void addPalette(std::shared_ptr<const Palette> palette);
	unsigned numPalettes() const;
	std::shared_ptr<const Palette> paletteById(unsigned id) const;

private:
	std::vector<std::shared_ptr<const Palette>> m_additionalPalettes;
};

#endif
