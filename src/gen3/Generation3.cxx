#include "gen3/Generation3.h"

#include <sstream>

#include "gen3/G3BasePokemon.h"
#include "gen3/G3Box.h"
#include "gen3/G3Party.h"

enum {
	G3_BOXES = 14,

	G30E_PARTY_POKEMON = 0x0234,
	G30E_BOX_NAMES = 0x0744,

	G30E_RUBY_BASE_STATS = 0x1FEC34,
	G30E_SAPPHIRE_BASE_STATS = 0x1FEBC4,

	G31J_BASE_STATS = 0x2F0D70,
	G31E_BASE_STATS = 0x3203E8,

	G32J_FIRE_RED_BASE_STATS = 0x2111A8,
	G32E_FIRE_RED_BASE_STATS = 0x2547A0,

	G32J_LEAF_GREEN_BASE_STATS = 0x211184,
	G32E_LEAF_GREEN_BASE_STATS = 0x25477C,

	G30E_RUBY_FRONT_SPRITE_MAPPING = 0x1E8354,
	G30E_SAPPHIRE_FRONT_SPRITE_MAPPING = 0x1E82E4,
	G32E_FIRE_RED_FRONT_SPRITE_MAPPING = 0x2350AC,

	G30E_RUBY_BACK_SPRITE_MAPPING = 0x1E97F4,
	G30E_SAPPHIRE_BACK_SPRITE_MAPPING = 0x1E9784,
	G32E_FIRE_RED_BACK_SPRITE_MAPPING = 0x23654C,

	G30E_RUBY_MENU_SPRITE_MAPPING = 0x3BBD20,
	G32E_FIRE_RED_MENU_SPRITE_MAPPING = 0x3D37A0,

	G30E_RUBY_PALETTE_MAPPING = 0x1EA5B4,
	G30E_SAPPHIRE_PALETTE_MAPPING = 0x1EA544,
	G32E_FIRE_RED_PALETTE_MAPPING = 0x23730C,

	G30E_RUBY_SHINY_PALETTE_MAPPING = 0x1EB374,
	G30E_SAPPHIRE_SHINY_PALETTE_MAPPING = 0x1EB304,
	G32E_FIRE_RED_SHINY_PALETTE_MAPPING = 0x2380CC,

	G30E_RUBY_MENU_PALETTES = 0xE966D8,
	G32E_FIRE_RED_MENU_PALETTES = 0x3D3740,

	G30E_RUBY_MENU_PALETTE_MAPPING = 0x3BC400,
	G32E_FIRE_RED_MENU_PALETTE_MAPPING = 0x3D3E80,

	// TODO: Find the real offsets
	G30E_RUBY_MENU_SHINY_PALETTE_MAPPING = 0x3BC400,
	G32E_FIRE_RED_MENU_SHINY_PALETTE_MAPPING = 0x3D3E80,
};

static const char* charMapEn[0x100] = {
	// 0x0X
	u8" ",	u8"À",	u8"Á",	u8"Â",	u8"Ç",	u8"È",	u8"É",	u8"Ê",
	u8"Ë",	u8"Ì",	u8"こ",	u8"Î",	u8"Ï",	u8"Ò",	u8"Ó",	u8"Ô",

	// 0x1X
	u8"Œ",	u8"Ù",	u8"Ú",	u8"Û",	u8"Ñ",	u8"ß",	u8"à",	u8"á",
	u8"ね",	u8"ç",	u8"è",	u8"é",	u8"ê",	u8"ë",	u8"ì",	u8"ま",

	// 0x2X
	u8"î",	u8"ï",	u8"ò",	u8"ó",	u8"ô",	u8"œ",	u8"ù",	u8"ú",
	u8"û",	u8"ñ",	u8"º",	u8"ª",	u8"�",	u8"&",	u8"+",	u8"あ",

	// 0x3X
	u8"ぃ",	u8"ぅ",	u8"ぇ",	u8"ぉ",	u8"v",	u8"=",	u8"ょ",	u8"が",
	u8"ぎ",	u8"ぐ",	u8"げ",	u8"ご",	u8"ざ",	u8"じ",	u8"ず",	u8"ぜ",

	// 0x4X
	u8"ぞ",	u8"だ",	u8"ぢ",	u8"づ",	u8"で",	u8"ど",	u8"ば",	u8"び",
	u8"ぶ",	u8"べ",	u8"ぼ",	u8"ぱ",	u8"ぴ",	u8"ぷ",	u8"ぺ",	u8"ぽ",

	// 0x5X
	u8"っ",	u8"¿",	u8"¡",	u8"P\u200dk", u8"M\u200dn", u8"P\u200do", u8"K\u200dé",	u8"�",
	u8"�",	u8"�",	u8"Í",	u8"%",	u8"(",	u8")",	u8"セ",	u8"ソ",

	// 0x6X
	u8"タ",	u8"チ",	u8"ツ",	u8"テ",	u8"ト",	u8"ナ",	u8"ニ",	u8"ヌ",
	u8"â",	u8"ノ",	u8"ハ",	u8"ヒ",	u8"フ",	u8"ヘ",	u8"ホ",	u8"í",

	// 0x7X
	u8"ミ",	u8"ム",	u8"メ",	u8"モ",	u8"ヤ",	u8"ユ",	u8"ヨ",	u8"ラ",
	u8"リ",	u8"⬆",	u8"⬇",	u8"⬅",	u8"➡",	u8"ヲ",	u8"ン",	u8"ァ",

	// 0x8X
	u8"ィ",	u8"ゥ",	u8"ェ",	u8"ォ",	u8"ャ",	u8"ュ",	u8"ョ",	u8"ガ",
	u8"ギ",	u8"グ",	u8"ゲ",	u8"ゴ",	u8"ザ",	u8"ジ",	u8"ズ",	u8"ゼ",

	// 0x9X
	u8"ゾ",	u8"ダ",	u8"ヂ",	u8"ヅ",	u8"デ",	u8"ド",	u8"バ",	u8"ビ",
	u8"ブ",	u8"ベ",	u8"ボ",	u8"パ",	u8"ピ",	u8"プ",	u8"ペ",	u8"ポ",

	// 0xAX
	u8"ッ",	u8"0",	u8"1",	u8"2",	u8"3",	u8"4",	u8"5",	u8"6",
	u8"7",	u8"8",	u8"9",	u8"!",	u8"?",	u8".",	u8"-",	u8"・",

	// 0xBX
	u8"…",	u8"“",	u8"”",	u8"‘",	u8"’",	u8"♂",	u8"♀",	u8"$",
	u8",",	u8"×",	u8"/",	u8"A",	u8"B",	u8"C",	u8"D",	u8"E",

	// 0xCX
	u8"F",	u8"G",	u8"H",	u8"I",	u8"J",	u8"K",	u8"L",	u8"M",
	u8"N",	u8"O",	u8"P",	u8"Q",	u8"R",	u8"S",	u8"T",	u8"U",

	// 0xDX
	u8"V",	u8"W",	u8"X",	u8"Y",	u8"Z",	u8"a",	u8"b",	u8"c",
	u8"d",	u8"e",	u8"f",	u8"g",	u8"h",	u8"i",	u8"j",	u8"k",

	// 0xEX
	u8"l",	u8"m",	u8"n",	u8"o",	u8"p",	u8"q",	u8"r",	u8"s",
	u8"t",	u8"u",	u8"v",	u8"w",	u8"x",	u8"y",	u8"z",	u8"▶",

	// 0xFX
	u8":",	u8"Ä",	u8"Ö",	u8"Ü",	u8"ä",	u8"ö",	u8"ü",	u8"⬆",
	u8"⬇",	u8"⬅",	u8"�",	u8"�",	u8"�",	u8"�",	u8"�",	u8""
};

const uint16_t Generation3::reverseIdMapping[387] = {
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	106,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	138,
	139,
	140,
	141,
	142,
	143,
	144,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
	153,
	154,
	155,
	156,
	157,
	158,
	159,
	160,
	161,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	171,
	172,
	173,
	174,
	175,
	176,
	177,
	178,
	179,
	180,
	181,
	182,
	183,
	184,
	185,
	186,
	187,
	188,
	189,
	190,
	191,
	192,
	193,
	194,
	195,
	196,
	197,
	198,
	199,
	200,
	201,
	202,
	203,
	204,
	205,
	206,
	207,
	208,
	209,
	210,
	211,
	212,
	213,
	214,
	215,
	216,
	217,
	218,
	219,
	220,
	221,
	222,
	223,
	224,
	225,
	226,
	227,
	228,
	229,
	230,
	231,
	232,
	233,
	234,
	235,
	236,
	237,
	238,
	239,
	240,
	241,
	242,
	243,
	244,
	245,
	246,
	247,
	248,
	249,
	250,
	251,
	277,
	278,
	279,
	280,
	281,
	282,
	283,
	284,
	285,
	286,
	287,
	288,
	289,
	290,
	291,
	292,
	293,
	294,
	295,
	296,
	297,
	298,
	299,
	300,
	304,
	305,
	309,
	310,
	392,
	393,
	394,
	311,
	312,
	306,
	307,
	364,
	365,
	366,
	301,
	302,
	303,
	370,
	371,
	372,
	335,
	336,
	350,
	320,
	315,
	316,
	322,
	355,
	382,
	383,
	384,
	356,
	357,
	337,
	338,
	353,
	354,
	386,
	387,
	363,
	367,
	368,
	330,
	331,
	313,
	314,
	339,
	340,
	321,
	351,
	352,
	308,
	332,
	333,
	334,
	344,
	345,
	358,
	359,
	380,
	379,
	348,
	349,
	323,
	324,
	326,
	327,
	318,
	319,
	388,
	389,
	390,
	391,
	328,
	329,
	385,
	317,
	377,
	378,
	361,
	362,
	369,
	411,
	376,
	360,
	346,
	347,
	341,
	342,
	343,
	373,
	374,
	375,
	381,
	325,
	395,
	396,
	397,
	398,
	399,
	400,
	401,
	402,
	403,
	407,
	408,
	404,
	405,
	406,
	409,
	410
};

const Generation3::NameMapping Generation3::s_names[] = {
	{ 'JVXA', Game::G30_RUBY | Game::JAPANESE },
	{ 'EVXA', Game::G30_RUBY | Game::ENGLISH },
	{ 'JPXA', Game::G30_SAPPHIRE | Game::JAPANESE },
	{ 'EPXA', Game::G30_SAPPHIRE | Game::ENGLISH },
	{ 'JEPB', Game::G31_EMERALD | Game::JAPANESE },
	{ 'EEPB', Game::G31_EMERALD | Game::ENGLISH },
	{ 'JRPB', Game::G32_FIRE_RED | Game::JAPANESE },
	{ 'ERPB', Game::G32_FIRE_RED | Game::ENGLISH },
	{ 'JGPB', Game::G32_LEAF_GREEN | Game::JAPANESE },
	{ 'EGPB', Game::G32_LEAF_GREEN | Game::ENGLISH },
	{ 0, Game::INVALID }
};

enum {
	G30E_TRAINER_NAME = 0x000,
};

Generation3::Generation3(uint8_t* memory, const uint8_t* rom)
	: Game(memory, rom)
	, m_boxes(new G3BasePokemonData[G3_POKEMON_PER_BOX * G3_BOXES])
{
	Section* section = reinterpret_cast<Section*>(memory);
	m_version = section->index;
	if (section[Section::MAX_SECTIONS].index > m_version) {
		section = &section[Section::MAX_SECTIONS];
		m_version = section->index;
	}

	for (unsigned i = 0; i < Section::MAX_SECTIONS; ++i) {
		m_sections[i] = nullptr;
	}

	for (unsigned i = 0; i < Section::MAX_SECTIONS; ++i) {
		unsigned sectionID = section[i].id;
		if (sectionID < Section::MAX_SECTIONS) {
			m_sections[sectionID] = &section[i];
		}
	}

	unsigned remaining = sizeof(G3BasePokemonData) * G3_BOXES * G3_POKEMON_PER_BOX;
	uint8_t* boxData = reinterpret_cast<uint8_t*>(m_boxes.get());
	for (unsigned i = Section::PC_0; i < Section::MAX_SECTIONS; ++i) {
		uint8_t* data = this->section(static_cast<Section::ID>(i))->data;
		unsigned thisBox = std::min<unsigned>(remaining, 3968);
		if (i == Section::PC_0) {
			data += 4;
			thisBox -= 4;
		}
		memcpy(boxData, data, thisBox);
		remaining -= thisBox;
		boxData += thisBox;
	}

	setTrainerName(gameTextToUTF8(&m_sections[0]->data[G30E_TRAINER_NAME], 8));
	setParty(new G3Party(this));
	for (unsigned box = 0; box < numBoxes(); ++box) {
		uint8_t* boxName = &this->section(Section::PC_8)->data[G30E_BOX_NAMES + box * 9];
		addBox(new G3Box(this, &m_boxes[G3_POKEMON_PER_BOX * box], gameTextToUTF8(boxName, 9)));
	}
}

void Generation3::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Generation3* Generation3::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	if (detect(rom)) {
		return new Generation3(memory, rom);
	}
	return nullptr;
}

Game::Edition Generation3::Loader::detect(const uint8_t* rom) const {
	uint32_t name = *(uint32_t*) &rom[0xAC];
	return version(s_names, name);
}

std::string Generation3::gameTextToUTF8(const uint8_t* gameText, size_t len) const {
	std::stringstream stream;
	for (size_t i = 0; i < len; ++i) {
		if (gameText[i] == 0xFF) {
			break;
		}
		stream << charMapEn[gameText[i]];
	}
	return stream.str();
}

unsigned Generation3::numBoxes() const {
	return 14;
}

Game::Edition Generation3::version() const {
	uint32_t name = *(uint32_t*) &rom()[0xAC];
	return version(s_names, name);
}

const PokemonSpecies* Generation3::species(PokemonSpecies::Id id, PokemonSpecies::Forme forme) {
	const PokemonSpecies* species = Game::species(id, forme);
	if (!species && id <= PokemonSpecies::DEOXYS) {
		const G3PokemonBaseStats* stats;
		switch (version()) {
		case Game::G30_RUBY | Game::ENGLISH:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G30E_RUBY_BASE_STATS]);
			break;
		case Game::G30_SAPPHIRE | Game::ENGLISH:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G30E_SAPPHIRE_BASE_STATS]);
			break;
		case Game::G31_EMERALD | Game::JAPANESE:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G31J_BASE_STATS]);
			break;
		case Game::G31_EMERALD | Game::ENGLISH:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G31E_BASE_STATS]);
			break;
		case Game::G32_FIRE_RED | Game::JAPANESE:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32J_FIRE_RED_BASE_STATS]);
			break;
		case Game::G32_FIRE_RED | Game::ENGLISH:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32E_FIRE_RED_BASE_STATS]);
			break;
		case Game::G32_LEAF_GREEN | Game::JAPANESE:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32J_LEAF_GREEN_BASE_STATS]);
			break;
		case Game::G32_LEAF_GREEN | Game::ENGLISH:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32E_LEAF_GREEN_BASE_STATS]);
			break;
		default:
			return nullptr;
		}
		PokemonSpecies* newSpecies;
		if (id == PokemonSpecies::UNOWN && forme && forme <= PokemonSpecies::UNOWN_QUESTION) {
			newSpecies = new G3PokemonSpecies(&stats[G3PokemonSpecies::UNOWN_BASE + forme - 1], id, forme);
		} else {
			newSpecies = new G3PokemonSpecies(&stats[reverseIdMapping[id] - 1], id);
		}
		putSpecies(id, newSpecies, forme);
		loadSprites(newSpecies);
		species = newSpecies;
	}
	return species;
}

Game::Edition Generation3::version(const NameMapping* mapping, uint32_t name) {
	while (mapping->name) {
		if (mapping->name == name) {
			break;
		}
		++mapping;
	}
	return mapping->version;
}

Generation3::Section* Generation3::section(Section::ID sectionID) {
	if (sectionID >= Section::MAX_SECTIONS) {
		return nullptr;
	}
	return m_sections[sectionID];
}

const Generation3::Section* Generation3::section(Section::ID sectionID) const {
	if (sectionID >= Section::MAX_SECTIONS) {
		return nullptr;
	}
	return m_sections[sectionID];
}

void Generation3::finalize() {
	unsigned remaining = sizeof(G3BasePokemonData) * G3_BOXES * G3_POKEMON_PER_BOX;
	uint8_t* boxData = reinterpret_cast<uint8_t*>(m_boxes.get());
	for (unsigned i = Section::PC_0; i < Section::MAX_SECTIONS; ++i) {
		uint8_t* data = this->section(static_cast<Section::ID>(i))->data;
		unsigned thisBox = std::min<unsigned>(remaining, 3968);
		if (i == Section::PC_0) {
			data += 4;
			thisBox -= 4;
		}
		memcpy(data, boxData, thisBox);
		remaining -= thisBox;
		boxData += thisBox;
	}

	for (int sid = 0; sid < Section::MAX_SECTIONS; ++sid) {
		Section* s = section(static_cast<Section::ID>(sid));
		s->checksum = checksum(static_cast<Section::ID>(sid));
	}
}

bool Generation3::testChecksum() const {
	for (int sid = 0; sid < Section::MAX_SECTIONS; ++sid) {
		const Section* s = section(static_cast<Section::ID>(sid));
		if (s->checksum != checksum(static_cast<Section::ID>(sid))) {
			return false;
		}
	}
	return true;
}

uint16_t Generation3::checksum(Section::ID sid) const {
	uint32_t checksum = 0;
	const Section* s = section(sid);
	const uint32_t* memory = reinterpret_cast<const uint32_t*>(s->data);
	for (unsigned offset = 0; offset < sizeof(s->data) / sizeof(uint32_t); ++offset) {
		checksum += memory[offset];
	}
	return checksum + (checksum >> 16);
}

void Generation3::loadSprites(PokemonSpecies* species) const {
	if (species->id() > PokemonSpecies::DEOXYS) {
		return;
	}

	unsigned gameId;
	if (species->id() != PokemonSpecies::UNOWN || !species->forme()) {
		gameId = reverseIdMapping[species->id()];
	} else {
		gameId = G3PokemonSpecies::UNOWN_BASE + species->forme() - 1;
	}
	struct Mapping {
		uint32_t pointer;
		uint16_t unknown;
		uint16_t id;
	};

	const Mapping* spriteMapping;
	const Mapping* backSpriteMapping;
	const Mapping* paletteMapping;
	const Mapping* shinyPaletteMapping;
	const uint32_t* menuSpriteMapping;
	const uint8_t* menuPaletteMapping;
	const uint8_t* shinyMenuPaletteMapping;
	uint32_t menuPaletteBase;

	switch (version()) {
	case Game::G30_RUBY | Game::ENGLISH:
		spriteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_RUBY_FRONT_SPRITE_MAPPING]);
		backSpriteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_RUBY_BACK_SPRITE_MAPPING]);
		paletteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_RUBY_PALETTE_MAPPING]);
		shinyPaletteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_RUBY_SHINY_PALETTE_MAPPING]);
		menuSpriteMapping = reinterpret_cast<const uint32_t*>(&rom()[G30E_RUBY_MENU_SPRITE_MAPPING]);
		menuPaletteMapping = reinterpret_cast<const uint8_t*>(&rom()[G30E_RUBY_MENU_PALETTE_MAPPING]);
		shinyMenuPaletteMapping = reinterpret_cast<const uint8_t*>(&rom()[G30E_RUBY_MENU_SHINY_PALETTE_MAPPING]);
		menuPaletteBase = G30E_RUBY_MENU_PALETTES;
		break;
	case Game::G30_SAPPHIRE | Game::ENGLISH:
		spriteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_SAPPHIRE_FRONT_SPRITE_MAPPING]);
		backSpriteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_SAPPHIRE_FRONT_SPRITE_MAPPING]);
		paletteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_SAPPHIRE_PALETTE_MAPPING]);
		shinyPaletteMapping = reinterpret_cast<const Mapping*>(&rom()[G30E_SAPPHIRE_SHINY_PALETTE_MAPPING]);
		// TODO: Find Sapphire mappings
		menuSpriteMapping = reinterpret_cast<const uint32_t*>(&rom()[G30E_RUBY_MENU_SPRITE_MAPPING]);
		menuPaletteMapping = reinterpret_cast<const uint8_t*>(&rom()[G30E_RUBY_MENU_PALETTE_MAPPING]);
		shinyMenuPaletteMapping = reinterpret_cast<const uint8_t*>(&rom()[G30E_RUBY_MENU_SHINY_PALETTE_MAPPING]);
		menuPaletteBase = G30E_RUBY_MENU_PALETTES;
		break;
	case Game::G32_FIRE_RED | Game::ENGLISH:
		spriteMapping = reinterpret_cast<const Mapping*>(&rom()[G32E_FIRE_RED_FRONT_SPRITE_MAPPING]);
		backSpriteMapping = reinterpret_cast<const Mapping*>(&rom()[G32E_FIRE_RED_BACK_SPRITE_MAPPING]);
		paletteMapping = reinterpret_cast<const Mapping*>(&rom()[G32E_FIRE_RED_PALETTE_MAPPING]);
		shinyPaletteMapping = reinterpret_cast<const Mapping*>(&rom()[G32E_FIRE_RED_SHINY_PALETTE_MAPPING]);
		menuSpriteMapping = reinterpret_cast<const uint32_t*>(&rom()[G32E_FIRE_RED_MENU_SPRITE_MAPPING]);
		menuSpriteMapping = reinterpret_cast<const uint32_t*>(&rom()[G32E_FIRE_RED_MENU_SPRITE_MAPPING]);
		menuPaletteMapping = reinterpret_cast<const uint8_t*>(&rom()[G32E_FIRE_RED_MENU_PALETTE_MAPPING]);
		shinyMenuPaletteMapping = reinterpret_cast<const uint8_t*>(&rom()[G32E_FIRE_RED_MENU_SHINY_PALETTE_MAPPING]);
		menuPaletteBase = G32E_FIRE_RED_MENU_PALETTES;
		break;
	default:
		return;
	}

	uint8_t* rawSpriteData = new uint8_t[64 * 32];
	uint8_t* spriteData = new uint8_t[64 * 32];
	uint8_t* rawBackSpriteData = new uint8_t[64 * 32];
	uint8_t* backSpriteData = new uint8_t[64 * 32];
	uint8_t* menuSpriteData = new uint8_t[32 * 16];
	uint16_t* paletteData = new uint16_t[16];
	uint16_t* shinyPaletteData = new uint16_t[16];
	uint16_t* backPaletteData = new uint16_t[16];
	uint16_t* shinyBackPaletteData = new uint16_t[16];
	uint16_t* menuPaletteData = new uint16_t[16];
	uint16_t* shinyMenuPaletteData = new uint16_t[16];

	const uint8_t* spritePointer = &rom()[spriteMapping[gameId].pointer & (SIZE_ROM - 1)];
	const uint8_t* backSpritePointer = &rom()[backSpriteMapping[gameId].pointer & (SIZE_ROM - 1)];
	const uint8_t* palettePointer = &rom()[paletteMapping[gameId].pointer & (SIZE_ROM - 1)];
	const uint8_t* shinyPalettePointer = &rom()[shinyPaletteMapping[gameId].pointer & (SIZE_ROM - 1)];
	const uint8_t* menuSpritePointer = &rom()[menuSpriteMapping[gameId] & (SIZE_ROM - 1)];
	const uint8_t* menuPalettePointer = &rom()[menuPaletteMapping[gameId] * 32 + menuPaletteBase];
	const uint8_t* shinyMenuPalettePointer = &rom()[shinyMenuPaletteMapping[gameId] * 32 + menuPaletteBase];

	lz77Decompress(spritePointer, rawSpriteData, 64 * 32);
	lz77Decompress(backSpritePointer, rawBackSpriteData, 64 * 32);
	lz77Decompress(palettePointer, reinterpret_cast<uint8_t*>(paletteData), 32);
	lz77Decompress(shinyPalettePointer, reinterpret_cast<uint8_t*>(shinyPaletteData), 32);

	for (unsigned tile = 0; tile < 64; ++tile) {
		for (unsigned y = 0; y < 8; ++y) {
			reinterpret_cast<uint32_t*>(spriteData)[y * 8 + (tile & 7) + (tile >> 3) * 64] = reinterpret_cast<uint32_t*>(rawSpriteData)[y + tile * 8];
			reinterpret_cast<uint32_t*>(backSpriteData)[y * 8 + (tile & 7) + (tile >> 3) * 64] = reinterpret_cast<uint32_t*>(rawBackSpriteData)[y + tile * 8];
		}
	}

	for (unsigned tile = 0; tile < 12; ++tile) {
		for (unsigned y = 0; y < 8; ++y) {
			reinterpret_cast<uint32_t*>(menuSpriteData)[y * 4 + (tile & 3) + (tile >> 2) * 32] = reinterpret_cast<const uint32_t*>(menuSpritePointer)[y + (tile + 4) * 8];
		}
	}

	memcpy(backPaletteData, paletteData, 32);
	memcpy(shinyBackPaletteData, shinyPaletteData, 32);
	memcpy(menuPaletteData, menuPalettePointer, 16 * 2);
	memcpy(shinyMenuPaletteData, shinyMenuPalettePointer, 16 * 2);

	delete [] rawSpriteData;
	delete [] rawBackSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(64, 64, spriteData, paletteData, Sprite::GBA_4);
	sprite->addPalette(shinyPaletteData);
	species->setFrontSprite(sprite);

	sprite = new MultipaletteSprite(64, 64, backSpriteData, backPaletteData, Sprite::GBA_4);
	sprite->addPalette(shinyBackPaletteData);
	species->setBackSprite(sprite);

	sprite = new MultipaletteSprite(32, 24, menuSpriteData, menuPaletteData, Sprite::GBA_4);
	sprite->addPalette(shinyMenuPaletteData);
	species->setMenuSprite(sprite);
}

void Generation3::stringToGameText(uint8_t* gameText, size_t len, const std::string& string) const {
	stringToMappedText(charMapEn, 0xFF, gameText, len, string);
}

void Generation3::lz77Decompress(const uint8_t* source, uint8_t* dest, size_t maxLength) {
	int remaining = std::min<int>(*reinterpret_cast<const uint32_t*>(source) >> 8, maxLength);
	int blockHeader;
	int blocksRemaining = 0;

	source += 4;

	while (remaining > 0) {
		if (blocksRemaining) {
			if (blockHeader & 0x80) {
				int block = source[0] | (source[1] << 8);
				source += 2;
				uint8_t* uncompressed = dest - (((block & 0x000F) << 8) | ((block & 0xFF00) >> 8)) - 1;
				int bytes = ((block & 0x00F0) >> 4) + 3;

				while (bytes && remaining) {
					*dest = *uncompressed;
					++uncompressed;
					++dest;
					--remaining;
					--bytes;
				}
			} else {
				*dest = *source;
				++source;
				++dest;
				--remaining;
			}
			blockHeader <<= 1;
			--blocksRemaining;
		} else {
			blockHeader = *source;
			++source;
			blocksRemaining = 8;
		}
	}
}
