#ifndef PTXN_SPRITE_H
#define PTXN_SPRITE_H

#include <cstdint>

class Sprite {
public:
	enum Format {
		GB_2,
		GBA_4,
	};

	Sprite(unsigned width, unsigned height, uint8_t* pixelData, Format format);
	Sprite(unsigned width, unsigned height, uint8_t* pixelData, uint16_t* palette, Format format);
	virtual ~Sprite();

	unsigned width() const;
	unsigned height() const;
	const uint8_t* pixelData() const;
	const uint16_t* palette() const;
	Format format() const;

private:
	unsigned m_width;
	unsigned m_height;
	uint8_t* m_pixelData;
	uint16_t* m_palette;
	Format m_format;
};

#endif
