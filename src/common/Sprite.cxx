#include "common/Sprite.h"

Sprite::Sprite(unsigned width, unsigned height, uint8_t* pixelData, Format format)
	: m_width(width)
	, m_height(height)
	, m_pixelData(pixelData)
	, m_palette(nullptr)
	, m_format(format)
{
}

Sprite::Sprite(unsigned width, unsigned height, uint8_t* pixelData, std::shared_ptr<const Palette> palette, Format format)
	: m_width(width)
	, m_height(height)
	, m_pixelData(pixelData)
	, m_palette(palette)
	, m_format(format)
{	
}

Sprite::~Sprite() {
	delete [] m_pixelData;
}

unsigned Sprite::width() const {
	return m_width;
}

unsigned Sprite::height() const {
	return m_height;
}

const uint8_t* Sprite::pixelData() const {
	return m_pixelData;
}

std::shared_ptr<const Palette> Sprite::palette() const {
	return m_palette;
}

Sprite::Format Sprite::format() const {
	return m_format;
}
