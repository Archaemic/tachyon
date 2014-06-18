#ifndef PTXN_G1_SPRITE_DECOMPRESSOR_H
#define PTXN_G1_SPRITE_DECOMPRESSOR_H

#include "common/Bitstream.h"

class G1SpriteDecompressor {
public:
	G1SpriteDecompressor(const uint8_t* source, size_t length);
	~G1SpriteDecompressor();

	void decompress();
	const uint8_t* output() const;
	size_t size() const;
	unsigned width() const;
	unsigned height() const;

private:
	void fill(uint8_t* bank);
	void decode(uint8_t* bank);
	void xorBanks(uint8_t* bank1, uint8_t* bank2);

	size_t decodeRle(uint8_t* bank, size_t remaining);
	size_t decodeData(uint8_t* bank, size_t remaining);

	Bitstream m_bits;

	unsigned m_width;
	unsigned m_height;

	uint8_t* m_output;

	const static unsigned table1[16];
	const static unsigned table2[4][16];
};

#endif
