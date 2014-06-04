#ifndef PTXN_GEN_GB_H
#define PTXN_GEN_GB_H

#include "base.h"

class GameBoyGame : public Game {
public:
	GameBoyGame(uint8_t* memory, const uint8_t* rom);

private:
	const static char* charMapGBEn[0x100];

protected:
	struct ChecksumMapping {
		uint16_t checksum;
		Game::Version version;
	};

	static Version version(const ChecksumMapping* checksums, uint16_t checksum);

public:
	static std::string gameTextToUTF8(const uint8_t* gameText, size_t len);
};

#endif
