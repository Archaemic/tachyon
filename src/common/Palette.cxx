#include "Palette.h"

Palette::Palette(const uint16_t* data, size_t entries)
	: m_data(new uint16_t[entries])
	, m_size(entries)
{
	memcpy(m_data, data, entries * sizeof(uint16_t));
}

Palette::~Palette() {
	delete [] m_data;
	m_data = nullptr;
}

uint16_t Palette::operator[](size_t at) const {
	if (at < m_size) {
		return m_data[at];
	}
	return 0;
}

size_t Palette::size() const {
	return m_size;
}
