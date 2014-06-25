#include "gb/GameBoyGame.h"

#include <sstream>


static const char* charMapGBJp[0x100] = {
	// 0x0X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"ガ", u8"ギ", u8"グ",
	u8"ゲ", u8"ゴ", u8"ザ", u8"ジ", u8"ズ", u8"ゼ", u8"ゾ", u8"ダ",

	// 0x1X
	u8"ヂ", u8"ヅ", u8"デ", u8"ド", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"バ", u8"ビ", u8"ブ", u8"ボ", u8"�", u8"�", u8"�",

	// 0x2X
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"が", u8"ぎ",
	u8"ぐ", u8"げ", u8"ご", u8"ざ", u8"じ", u8"ず", u8"ぜ", u8"ぞ",

	// 0x3X
	u8"だ", u8"ぢ", u8"づ", u8"で", u8"ど", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"ば", u8"び", u8"ぶ", u8"ベ", u8"ぼ", u8"�",

	// 0x4X
	u8"パ", u8"ピ", u8"プ", u8"ポ", u8"ぱ", u8"ぴ", u8"ぷ", u8"ペ",
	u8"ぽ", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

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
	u8"ア", u8"イ", u8"ウ", u8"エ", u8"オ", u8"カ", u8"キ", u8"ク",
	u8"ケ", u8"コ", u8"サ", u8"シ", u8"ス", u8"セ", u8"ソ", u8"タ",

	// 0x9X
	u8"チ", u8"ツ", u8"テ", u8"ト", u8"ナ", u8"ニ", u8"ヌ", u8"ネ",
	u8"ノ", u8"ハ", u8"ヒ", u8"フ", u8"ホ", u8"マ", u8"ミ", u8"ム",

	// 0xAX
	u8"メ", u8"モ", u8"ヤ", u8"ユ", u8"ヨ", u8"ラ", u8"ル", u8"レ",
	u8"ロ", u8"ワ", u8"ヲ", u8"ン", u8"ッ", u8"ャ", u8"ュ", u8"ョ",

	// 0xBX
	u8"ィ", u8"あ", u8"い", u8"う", u8"え", u8"お", u8"か", u8"き",
	u8"く", u8"け", u8"こ", u8"さ", u8"し", u8"す", u8"せ", u8"そ",

	// 0xCX
	u8"た", u8"ち", u8"つ", u8"て", u8"と", u8"な", u8"に", u8"ぬ",
	u8"ね", u8"の", u8"は", u8"ひ", u8"ふ", u8"へ", u8"ほ", u8"ま",

	// 0xDX
	u8"み", u8"む", u8"め", u8"も", u8"や", u8"ゆ", u8"よ", u8"ら",
	u8"リ", u8"る", u8"れ", u8"ろ", u8"わ", u8"を", u8"ん", u8"っ",

	// 0xEX
	u8"ゃ", u8"ゅ", u8"ょ", u8"ー", u8"゜", u8"゛", u8"?", u8"!",
	u8"。", u8"ァ", u8"ゥ", u8"ェ", u8"▹", u8"▸", u8"▾", u8"♂",

	// 0xFX
	u8"円", u8"×", u8".", u8"/", u8"ォ", u8"♀", u8"0", u8"1",
	u8"2", u8"3", u8"4", u8"5", u8"6", u8"7", u8"8", u8"9"
};

static const char* charMapGBEn[0x100] = {
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
	u8"y", u8"z", u8"é", u8"ʼd", u8"ʼl", u8"ʼs", u8"ʼt", u8"ʼv",

	// 0xCX
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0xDX
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",
	u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�", u8"�",

	// 0xEX
	u8"'", u8"P\u200dk", u8"M\u200dn", u8"-", u8"ʼr", u8"ʼm", u8"?", u8"!",
	u8".", u8"ァ", u8"ゥ", u8"ェ", u8"▹", u8"▸", u8"▾", u8"♂",

	// 0xFX
	u8"$", u8"×", u8".", u8"/", u8",", u8"♀", u8"0", u8"1",
	u8"2", u8"3", u8"4", u8"5", u8"6", u8"7", u8"8", u8"9"
};

static const char* charMapGBDeFr[0x100] = {
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
	u8"y", u8"z", u8"à", u8"è", u8"é", u8"ù", u8"ß", u8"ç",

	// 0xCX
	u8"Ä", u8"Ö", u8"Ü", u8"ä", u8"ö", u8"ü", u8"ë", u8"ï",
	u8"â", u8"ô", u8"û", u8"ê", u8"î", u8"�", u8"�", u8"�",

	// 0xDX
	u8"�", u8"�", u8"�", u8"�", u8"cʼ", u8"dʼ", u8"jʼ", u8"lʼ",
	u8"mʼ", u8"nʼ", u8"pʼ", u8"sʼ", u8"ʼs", u8"tʼ", u8"uʼ", u8"yʼ",

	// 0xEX
	u8"'", u8"P\u200dk", u8"M\u200dn", u8"-", u8"¿", u8"¡", u8"?", u8"!",
	u8".", u8"ァ", u8"ゥ", u8"ェ", u8"▹", u8"▸", u8"▾", u8"♂",

	// 0xFX
	u8"$", u8"×", u8".", u8"/", u8",", u8"♀", u8"0", u8"1",
	u8"2", u8"3", u8"4", u8"5", u8"6", u8"7", u8"8", u8"9"
};

static const char* charMapGBItSp[0x100] = {
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
	u8"y", u8"z", u8"à", u8"è", u8"é", u8"ù", u8"À", u8"Á",

	// 0xCX
	u8"Ä", u8"Ö", u8"Ü", u8"ä", u8"ö", u8"ü", u8"È", u8"É",
	u8"Ì", u8"Í", u8"Ñ", u8"Ò", u8"Ó", u8"Ù", u8"Ú", u8"á",

	// 0xDX
	u8"ì", u8"í", u8"ñ", u8"ò", u8"ó", u8"ú", u8"º", u8"&",
	u8"ʼd", u8"ʼl", u8"ʼm", u8"ʼr", u8"ʼs", u8"ʼt", u8"ʼv", u8" ",

	// 0xEX
	u8"'", u8"P\u200dk", u8"M\u200dn", u8"-", u8"¿", u8"¡", u8"?", u8"!",
	u8".", u8"ァ", u8"ゥ", u8"ェ", u8"▹", u8"▸", u8"▾", u8"♂",

	// 0xFX
	u8"$", u8"×", u8".", u8"/", u8",", u8"♀", u8"0", u8"1",
	u8"2", u8"3", u8"4", u8"5", u8"6", u8"7", u8"8", u8"9"
};


const char** GameBoyGame::charMapGB[] = {
	charMapGBJp,
	charMapGBEn,
	charMapGBDeFr,
	charMapGBDeFr,
	charMapGBItSp,
	charMapGBItSp,
	nullptr
};

const Type GameBoyGame::typeMapping[256] = {
	NORMAL,
	FIGHTING,
	FLYING,
	POISON,
	GROUND,
	ROCK,
	BIRD,
	BUG,
	GHOST,
	STEEL,

	QQQ,
	QQQ,
	QQQ,
	QQQ,
	QQQ,
	QQQ,
	QQQ,
	QQQ,
	QQQ,

	QQQ,
	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	PSYCHIC,
	ICE,
	DRAGON,
	DARK
};

GameBoyGame::GameBoyGame(uint8_t* memory, const uint8_t* rom)
	: Game(memory, rom)
{
}

std::string GameBoyGame::gameTextToUTF8(const uint8_t* gameText, size_t len) const {
	std::stringstream stream;
	const char** map = charMapGB[(version() & MASK_LOCALIZATION) >> 4];
	for (size_t i = 0; i < len; ++i) {
		if (gameText[i] == 0x50) {
			break;
		}
		stream << map[gameText[i]];
	}
	return stream.str();
}

void GameBoyGame::stringToGameText(uint8_t* gameText, size_t len, const std::string& string) const {
	stringToMappedText(charMapGB[(version() & MASK_LOCALIZATION) >> 4], 0x50, gameText, len, string);
}

void GameBoyGame::arrangeTiles(const uint8_t* source, uint8_t* dest, unsigned width, unsigned height) {
	for (unsigned tile = 0; tile < width * height; ++tile) {
		for (unsigned y = 0; y < 8; ++y) {
			uint16_t row = reinterpret_cast<const uint16_t*>(source)[y + tile * 8];
			uint8_t lower = row & 0xFF;
			uint8_t upper = row >> 8;
			row = 0;
			for (int i = 0; i < 8; ++i) {
				row |= (upper & (1 << i)) << (i + 1);
				row |= (lower & (1 << i)) << i;
			}
			reinterpret_cast<uint16_t*>(dest)[y * width + tile % width + (tile / width) * 8 * width] = row;
		}
	}
}

void GameBoyGame::arrangeTilesTransposed(const uint8_t* source, uint8_t* dest, unsigned width, unsigned height) {
	for (unsigned tile = 0; tile < width * height; ++tile) {
		for (unsigned y = 0; y < 8; ++y) {
			uint16_t row = reinterpret_cast<const uint16_t*>(source)[y + tile * 8];
			uint8_t lower = row & 0xFF;
			uint8_t upper = row >> 8;
			row = 0;
			for (int i = 0; i < 8; ++i) {
				row |= (upper & (1 << i)) << (i + 1);
				row |= (lower & (1 << i)) << i;
			}
			reinterpret_cast<uint16_t*>(dest)[y * width + (tile % height) * 8 * width + tile / height] = row;
		}
	}
}
