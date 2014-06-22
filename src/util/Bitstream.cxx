#include "util/Bitstream.h"

Bitstream::Bitstream(const uint8_t* bits, size_t length)
    : m_bits(bits)
    , m_length(length)
    , m_currentAddress(0)
    , m_currentBit(0)
{
}

unsigned Bitstream::readBits(int bits) {
    unsigned out = 0;
    for (int i = 0; i < bits; ++i) {
        out <<= 1;
        out |= readBit();
    }
    return out;
}

unsigned Bitstream::readBit() {
    if (eof()) {
        return 0;
    }
    uint8_t byte = m_bits[m_currentAddress];
    byte >>= 7 - m_currentBit;
    ++m_currentBit;
    if (m_currentBit == 8) {
        m_currentBit = 0;
        ++m_currentAddress;
    }
    return byte & 1;
}

bool Bitstream::eof() const {
    return m_currentAddress >= m_length;
}
