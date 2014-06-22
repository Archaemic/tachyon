#include "gen1/G1SpriteDecompressor.h"

const unsigned G1SpriteDecompressor::table1[16] = { 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };
const unsigned G1SpriteDecompressor::table2[2][16] =
{
	{ 0x0, 0x1, 0x3, 0x2, 0x7, 0x6, 0x4, 0x5, 0xF, 0xE, 0xC, 0xD, 0x8, 0x9, 0xB, 0xA },
	{ 0xF, 0xE, 0xC, 0xD, 0x8, 0x9, 0xB, 0xA, 0x0, 0x1, 0x3, 0x2, 0x7, 0x6, 0x4, 0x5 }
};

G1SpriteDecompressor::G1SpriteDecompressor(const uint8_t* source, size_t length)
	: m_bits(source, length)
	, m_width(0)
	, m_height(0)
	, m_output(0)
{
}

G1SpriteDecompressor::~G1SpriteDecompressor() {
	delete [] m_output;
}

void G1SpriteDecompressor::decompress() {
	m_width = m_bits.readBits(4) * 8;
	m_height = m_bits.readBits(4);

	uint8_t* buffer1 = new uint8_t[m_width * m_height];
	uint8_t* buffer2 = new uint8_t[m_width * m_height];

	unsigned order = m_bits.readBit();
	int mode;

	uint8_t* o1 = order ? buffer2 : buffer1;
	uint8_t* o2 = order ? buffer1 : buffer2;

	fill(o1);
	mode = m_bits.readBit();
	if (mode) {
		mode += m_bits.readBit();
	}
	fill(o2);

	switch (mode) {
	case 0:
		decode(buffer1);
		decode(buffer2);
		break;
	case 1:
		decode(o1);
		xorBanks(o1, o2);
		break;
	case 2:
		decode(o2);
		decode(o1);
		xorBanks(o1, o2);
		break;
	}

	m_output = new uint8_t[m_width * m_height * 2];
	for (size_t i = 0; i < m_width * m_height; ++i) {
		m_output[2 * i] = buffer1[i];
		m_output[2 * i + 1] = buffer2[i];
	}

	delete [] buffer1;
	delete [] buffer2;
}

const uint8_t* G1SpriteDecompressor::output() const {
	return m_output;
}

size_t G1SpriteDecompressor::size() const {
	return m_width * m_height * 2;
}

void G1SpriteDecompressor::fill(uint8_t* bank) {
	int mode = m_bits.readBit();

	size_t size = m_width * m_height * 4;
	uint8_t* expandedBits = new uint8_t[size];

	size_t read = 0;
	while (read < size) {
		if (!mode) {
			read += decodeRle(expandedBits + read, size - read);
			mode = 1;
		} else {
			read += decodeData(expandedBits + read, size - read);
			mode = 0;
		}
	}

	size_t l = 0;
	for (unsigned y = 0; y < m_height; ++y) {
		for (unsigned x = 0; x < m_width; ++x) {
			bank[l] = expandedBits[4 * y * m_width + x] << 6;
			bank[l] |= expandedBits[(4 * y + 1) * m_width + x] << 4;
			bank[l] |= expandedBits[(4 * y + 2) * m_width + x] << 2;
			bank[l] |= expandedBits[(4 * y + 3) * m_width + x];
			++l;
		}
	}

	delete [] expandedBits;
}

size_t G1SpriteDecompressor::decodeRle(uint8_t* bank, size_t remaining) {
	unsigned index = 0;
	while (m_bits.readBit()) {
		++index;
	}

	if (index >= sizeof(table1) / sizeof(*table1)) {
		return 0;
	}

	unsigned n = table1[index];
	unsigned a = m_bits.readBits(index + 1);
	n += a;

	size_t read = 0;
	for (size_t i = 0; i < n; ++i) {
		if (read >= remaining) {
			return remaining;
		}
		bank[i] = 0;
		++read;
	}
	return read;
}

size_t G1SpriteDecompressor::decodeData(uint8_t* bank, size_t remaining) {
	size_t read = 0;
	while (read < remaining) {
		unsigned bits = m_bits.readBits(2);
		if (!bits) {
			break;
		}
		bank[read] = bits;
		++read;
	}
	return read;
}

void G1SpriteDecompressor::decode(uint8_t* bank) {
	for (unsigned x = 0; x < m_width; ++x) {
		unsigned bit = 0;
		for (unsigned y = 0; y < m_height; ++y) {
			unsigned i = y * m_width + x;

			unsigned high = bank[i] >> 4;
			unsigned low = bank[i] & 0xF;

			high = table2[bit][high];
			bit = high & 1;

			low = table2[bit][low];
			bit = low & 1;

			bank[i] = (high << 4) | low;
		}
	}
}

void G1SpriteDecompressor::xorBanks(uint8_t* bank1, uint8_t* bank2) {
	size_t size = m_width * m_height;

	for (size_t i = 0; i < size; ++i) {
		bank2[i] ^= bank1[i];
	}
}
