#include "SpriteUtilities.h"

#include "common/MultipaletteSprite.h"

QImage spriteToQImage(const MultipaletteSprite& sprite, unsigned paletteId) {
	QImage image(QSize(sprite.width(), sprite.height()), QImage::Format_Indexed8);
	image.setColor(0, qRgba(0, 0, 0, 0));
	std::shared_ptr<const Palette> palette = sprite.paletteById(paletteId);
	for (size_t p = 1; p < palette->size(); ++p) {
		uint16_t paletteEntry = (*palette)[p];
		image.setColor(p, qRgb((paletteEntry & 0x1F) << 3, (paletteEntry >> 2) & 0xF8, (paletteEntry >> 7) & 0xF8));
	}

	switch (sprite.format()) {
	case Sprite::GBA_4:
		for (unsigned y = 0; y < sprite.height(); ++y) {
			for (unsigned x = 0; x < sprite.width() / 2; ++x) {
				image.setPixel(x * 2 + 1, y, sprite.pixelData()[y * sprite.width() / 2 + x] >> 4);
				image.setPixel(x * 2, y, sprite.pixelData()[y * sprite.width() / 2 + x] & 0xF);
			}
		}
		break;
	case Sprite::GB_2:
		for (unsigned y = 0; y < sprite.height(); ++y) {
			const uint16_t* row = reinterpret_cast<const uint16_t*>(&sprite.pixelData()[y * sprite.width() / 4]);
			for (unsigned x = 0; x < sprite.width() / 8; ++x) {
				uint16_t block = row[x];
				image.setPixel(x * 8, y, block >> 14);
				image.setPixel(x * 8 + 1, y, (block >> 12) & 0x3);
				image.setPixel(x * 8 + 2, y, (block >> 10) & 0x3);
				image.setPixel(x * 8 + 3, y, (block >> 8) & 0x3);
				image.setPixel(x * 8 + 4, y, (block >> 6) & 0x3);
				image.setPixel(x * 8 + 5, y, (block >> 4) & 0x3);
				image.setPixel(x * 8 + 6, y, (block >> 2) & 0x3);
				image.setPixel(x * 8 + 7, y, block & 0x3);
			}
		}
		break;
	}
	return image;
}

QImage fitToMargins(const QImage& image, int width, int height) {
	return image.copy((image.width() - width) / 2, (image.height() - height) / 2, width, height);
}
