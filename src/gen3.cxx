#include "gen3.h"

#include <sstream>

static const char* charMapEn[0x100] = {
	u8" ",	u8"À",	u8"Á",	u8"Â",	u8"Ç",	u8"È",	u8"É",	u8"Ê",	u8"Ë",	u8"Ì",	u8"こ",	u8"Î",	u8"Ï",	u8"Ò",	u8"Ó",	u8"Ô",
	u8"Œ",	u8"Ù",	u8"Ú",	u8"Û",	u8"Ñ",	u8"ß",	u8"à",	u8"á",	u8"ね",	u8"ç",	u8"è",	u8"é",	u8"ê",	u8"ë",	u8"ì",	u8"ま",
	u8"î",	u8"ï",	u8"ò",	u8"ó",	u8"ô",	u8"œ",	u8"ù",	u8"ú",	u8"û",	u8"ñ",	u8"º",	u8"ª",	u8"�",	u8"&",	u8"+",	u8"あ",
	u8"ぃ",	u8"ぅ",	u8"ぇ",	u8"ぉ",	u8"v",	u8"=",	u8"ょ",	u8"が",	u8"ぎ",	u8"ぐ",	u8"げ",	u8"ご",	u8"ざ",	u8"じ",	u8"ず",	u8"ぜ",
	u8"ぞ",	u8"だ",	u8"ぢ",	u8"づ",	u8"で",	u8"ど",	u8"ば",	u8"び",	u8"ぶ",	u8"べ",	u8"ぼ",	u8"ぱ",	u8"ぴ",	u8"ぷ",	u8"ぺ",	u8"ぽ",
	u8"っ",	u8"¿",	u8"¡",	u8"ᴾK",	u8"ᴹN",	u8"ᴾO",	u8"ᴷé",	u8"�",	u8"�",	u8"�",	u8"Í",	u8"%",	u8"(",	u8")",	u8"セ",	u8"ソ",
	u8"タ",	u8"チ",	u8"ツ",	u8"テ",	u8"ト",	u8"ナ",	u8"ニ",	u8"ヌ",	u8"â",	u8"ノ",	u8"ハ",	u8"ヒ",	u8"フ",	u8"ヘ",	u8"ホ",	u8"í",
	u8"ミ",	u8"ム",	u8"メ",	u8"モ",	u8"ヤ",	u8"ユ",	u8"ヨ",	u8"ラ",	u8"リ",	u8"⬆",	u8"⬇",	u8"⬅",	u8"➡",	u8"ヲ",	u8"ン",	u8"ァ",
	u8"ィ",	u8"ゥ",	u8"ェ",	u8"ォ",	u8"ャ",	u8"ュ",	u8"ョ",	u8"ガ",	u8"ギ",	u8"グ",	u8"ゲ",	u8"ゴ",	u8"ザ",	u8"ジ",	u8"ズ",	u8"ゼ",
	u8"ゾ",	u8"ダ",	u8"ヂ",	u8"ヅ",	u8"デ",	u8"ド",	u8"バ",	u8"ビ",	u8"ブ",	u8"ベ",	u8"ボ",	u8"パ",	u8"ピ",	u8"プ",	u8"ペ",	u8"ポ",
	u8"ッ",	u8"0",	u8"1",	u8"2",	u8"3",	u8"4",	u8"5",	u8"6",	u8"7",	u8"8",	u8"9",	u8"!",	u8"?",	u8".",	u8"-",	u8"・",
	u8"…",	u8"“",	u8"”",	u8"‘",	u8"’",	u8"♂",	u8"♀",	u8"$",	u8",",	u8"×",	u8"/",	u8"A",	u8"B",	u8"C",	u8"D",	u8"E",
	u8"F",	u8"G",	u8"H",	u8"I",	u8"J",	u8"K",	u8"L",	u8"M",	u8"N",	u8"O",	u8"P",	u8"Q",	u8"R",	u8"S",	u8"T",	u8"U",
	u8"V",	u8"W",	u8"X",	u8"Y",	u8"Z",	u8"a",	u8"b",	u8"c",	u8"d",	u8"e",	u8"f",	u8"g",	u8"h",	u8"i",	u8"j",	u8"k",
	u8"l",	u8"m",	u8"n",	u8"o",	u8"p",	u8"q",	u8"r",	u8"s",	u8"t",	u8"u",	u8"v",	u8"w",	u8"x",	u8"y",	u8"z",	u8"▶",
	u8":",	u8"Ä",	u8"Ö",	u8"Ü",	u8"ä",	u8"ö",	u8"ü",	u8"⬆",	u8"⬇",	u8"⬅",	u8"�",	u8"�",	u8"�",	u8"�",	u8"�",	u8""
};

const Generation3::NameMapping Generation3::s_names[] = {
	{ 'JVXA', Game::G30J_RUBY },
	{ 'EVXA', Game::G30E_RUBY },
	{ 'JPXA', Game::G30J_SAPPHIRE },
	{ 'EPXA', Game::G30E_SAPPHIRE },
	{ 'JEPB', Game::G31J_EMERALD },
	{ 'EEPB', Game::G31E_EMERALD },
	{ 'JRPB', Game::G32J_FIRE_RED },
	{ 'ERPB', Game::G32E_FIRE_RED },
	{ 'JGPB', Game::G32J_LEAF_GREEN },
	{ 'EGPB', Game::G32E_LEAF_GREEN },
	{ 0, Game::INVALID }
};

enum {
	G30E_TRAINER_NAME = 0x000
};

Generation3::Generation3(uint8_t* memory, const uint8_t* rom)
	: Game(memory, rom)
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

	setTrainerName(gameTextToUTF8(&m_sections[0]->data[G30E_TRAINER_NAME], 8));
}

void Generation3::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Game* Generation3::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	uint32_t name = *(uint32_t*) &rom[0xAC];
	if (version(s_names, name)) {
		return new Generation3(memory, rom);
	}
	return nullptr;
}

std::string Generation3::gameTextToUTF8(const uint8_t* gameText, size_t len) {
	std::stringstream stream;
	for (size_t i = 0; i < len; ++i) {
		if (gameText[i] == 0xFF) {
			break;
		}
		stream << charMapEn[gameText[i]];
	}
	return stream.str();
}

std::unique_ptr<Group> Generation3::party() {
	return std::unique_ptr<Group>(nullptr);
}

std::unique_ptr<Group> Generation3::box(unsigned box) {
	return std::unique_ptr<Group>(nullptr);
}

Game::Version Generation3::version() const {
	uint32_t name = *(uint32_t*) &rom()[0xAC];
	return version(s_names, name);
}

PokemonSpecies* Generation3::species(PokemonSpecies::Id id) {
	PokemonSpecies* species = Game::species(id);
	return species;
}

Game::Version Generation3::version(const NameMapping* mapping, uint32_t name) {
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
