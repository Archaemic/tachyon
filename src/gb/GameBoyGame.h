#ifndef PTXN_GAME_BOY_GAME_H
#define PTXN_GAME_BOY_GAME_H

#include "common/Game.h"

#define R16(V) (((V) & 0xFF) << 8) | (((V) & 0xFF00) >> 8)
#define R24(V) (((V) & 0xFF) << 16) | ((V) & 0xFF00) | (((V) & 0xFF0000) >> 16)
#define R32(V) (((V) & 0xFF) << 24) | (((V) & 0xFF00) << 8) | (((V) & 0xFF0000) >> 8) | (((V) & 0xFF000000) >> 24)

class GameBoyGame : public Game {
public:
	GameBoyGame(uint8_t* memory, const uint8_t* rom);

private:
	const static char** charMapGB[];

protected:
	struct ChecksumMapping {
		uint16_t checksum;
		Game::Edition version;
	};

	static Game::Edition findVersion(const ChecksumMapping* checksums, uint16_t checksum);

public:
	static const Type typeMapping[256];
	std::string gameTextToUTF8(const uint8_t* gameText, size_t len) const;
	virtual void stringToGameText(uint8_t* gameText, size_t len, const std::string&) const override;

	static void arrangeTiles(const uint8_t* src, uint8_t* dest, unsigned width, unsigned height);
	static void arrangeTilesTransposed(const uint8_t* src, uint8_t* dest, unsigned width, unsigned height);
};

struct GBMoveSet {
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
};

#endif
