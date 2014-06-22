#ifndef PTXN_BITSTREAM_H
#define PTXN_BITSTREAM_H

#include <cstdint>
#include <cstring>

class Bitstream {
public:
	Bitstream(const uint8_t* bits, size_t length);

	unsigned readBits(int bits);
	unsigned readBit();
	bool eof() const;

private:
	const uint8_t* m_bits;
	size_t m_length;

	size_t m_currentAddress;
	unsigned m_currentBit;
};

#endif
