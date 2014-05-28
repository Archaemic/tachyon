#include "gen-gb-private.h"

#include <sstream>

const char* GameBoyGame::charMapGBEn[0x100] = {
	// 0x0X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0x1X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0x2X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0x3X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0x4X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0x5X
	u8"", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0x6X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0x7X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8" ",

	// 0x8X
	u8"A", u8"B", u8"C", u8"D", u8"E", u8"F", u8"G", u8"H",
	u8"I", u8"J", u8"K", u8"L", u8"M", u8"N", u8"O", u8"P",

	// 0x9X
	u8"Q", u8"R", u8"S", u8"T", u8"U", u8"V", u8"W", u8"X",
	u8"Y", u8"Z", u8"(", u8")", u8":", u8";", u8"[", u8"]",

	// 0xAX
	u8"a", u8"b", u8"c", u8"d", u8"e", u8"f", u8"g", u8"h",
	u8"i", u8"j", u8"k", u8"l", u8"m", u8"n", u8"o", u8"p",

	// 0xBX
	u8"q", u8"r", u8"s", u8"t", u8"u", u8"v", u8"w", u8"x",
	u8"y", u8"z", u8"é", u8"d", u8"l", u8"s", u8"t", u8"v",

	// 0xCX
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0xDX
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0xEX
	u8"\'", u8"ᴾK", u8"ᴹN", u8"-", u8"r", u8"m", u8"?", u8"!",
	u8".", u8"ァ", u8"ゥ", u8"ェ", u8"▹", u8"▸", u8"▾", u8"♂",

	// 0xFX
	u8"$", u8"×", u8".", u8"/", u8",", u8"♀", u8"0", u8"1",
	u8"2", u8"3", u8"4", u8"5", u8"6", u8"7", u8"8", u8"9"
};

GameBoyGame::GameBoyGame(uint8_t* memory, const uint8_t* rom)
	: Game(memory, rom)
{
}

std::string GameBoyGame::gameTextToUTF8(const uint8_t* gameText, size_t len) {
	std::stringstream stream;
	for (size_t i = 0; i < len; ++i) {
		if (gameText[i] == 0x50) {
			break;
		}
		stream << charMapGBEn[gameText[i]];
	}
	return stream.str();
}

Game::Version GameBoyGame::version(const ChecksumMapping* mapping, uint16_t checksum) {
	while (mapping->checksum) {
		if (mapping->checksum == checksum) {
			break;
		}
		++mapping;
	}
	return mapping->version;
}
