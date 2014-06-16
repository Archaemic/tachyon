#ifndef PTXN_MULTIPALETTE_SPRITE_H
#define PTXN_MULTIPALETTE_SPRITE_H

#include "Sprite.h"

#include <vector>

class MultipaletteSprite : public Sprite {
public:
	MultipaletteSprite(unsigned width, unsigned height, uint8_t* pixelData, uint16_t* palette, Format format);
	virtual ~MultipaletteSprite();

	void addPalette(uint16_t* palette);
	unsigned numPalettes() const;
	const uint16_t* paletteById(unsigned id) const;

private:
	std::vector<uint16_t*> m_additionalPalettes;
};

#endif
