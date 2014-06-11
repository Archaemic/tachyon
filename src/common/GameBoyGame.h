#ifndef PTXN_GAME_BOY_GAME_H
#define PTXN_GAME_BOY_GAME_H

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
	static const Type typeMapping[256];
	static std::string gameTextToUTF8(const uint8_t* gameText, size_t len);
	virtual void stringToGameText(uint8_t* gameText, size_t len, const std::string&) override;
};

struct GBMoveSet {
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
};

#endif
