#ifndef PTXN_PALETTE_H
#define PTXN_PALETTE_H

#include <cstdint>
#include <cstring>

class Palette final {
public:
	Palette(const uint16_t* data, size_t entries);
	~Palette();

	uint16_t operator[](size_t at) const;
	size_t size() const;

private:
	uint16_t* m_data;
	size_t m_size;
};

#endif
