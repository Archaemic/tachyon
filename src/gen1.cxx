#include "gen1.h"

#define R16(V) (((V) & 0xFF) << 8) | (((V) & 0xFF00) >> 8)
#define R24(V) (((V) & 0xFF) << 16) | ((V) & 0xFF00) | (((V) & 0xFF0000) >> 16)
#define R32(V) (((V) & 0xFF) << 24) | (((V) & 0xFF00) << 8) | (((V) & 0xFF0000) >> 8) | (((V) & 0xFF000000) >> 24)

struct G1BasePokemonData {
	uint8_t pokemonId;
	uint16_t currentHp;
	uint8_t displayLevel;
	uint8_t status;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
	uint16_t otId;
	uint32_t xp : 24;
	uint16_t evHp;
	uint16_t evAttack;
	uint16_t evDefense;
	uint16_t evSpeed;
	uint16_t evSpecial;
	uint16_t ivs;
	uint8_t ppMove1;
	uint8_t ppMove2;
	uint8_t ppMove3;
	uint8_t ppMove4;
} __attribute__((packed));

struct G1PartyPokemonData : public G1BasePokemonData {
	uint8_t level;
	uint16_t maxHp;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t special;
} __attribute__((packed));

enum {
	G1_BOX_SIZE = 1122,

	G10E_TRAINER_NAME = 0x2598,
	G10E_PARTY_POKEMON = 0x2F2C,
	G10E_CURRENT_BOX = 0x30C0,
	G10E_BOX_1 = 0x4000
};

const static Type typeMapping[256] = {
	NORMAL,
	FIGHTING,
	FLYING,
	POISON,
	GROUND,
	ROCK,
	QQQ,
	BUG,
	GHOST,

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
	QQQ,

	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	PSYCHIC,
	ICE,
	DRAGON
};

const wchar_t Generation1::charMapGen1En[0x100] = {
	// 0x0X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x1X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x2X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x3X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x4X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x5X
	L'\0', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x6X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0x7X
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L' ',

	// 0x8X
	L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H',
	L'I', L'J', L'K', L'L', L'M', L'N', L'O', L'P',

	// 0x9X
	L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X',
	L'Y', L'Z', L'(', L')', L':', L';', L'[', L']',

	// 0xAX
	L'a', L'b', L'c', L'd', L'e', L'f', L'g', L'h',
	L'i', L'j', L'k', L'l', L'm', L'n', L'o', L'p',

	// 0xBX
	L'q', L'r', L's', L't', L'u', L'v', L'w', L'x',
	L'y', L'z', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xCX
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xDX
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',
	L'�', L'�', L'�', L'�', L'�', L'�', L'�', L'�',

	// 0xEX
	L'�', L'P', L'M', L'-', L'�', L'�', L'?', L'!',
	L'.', L'�', L'�', L'�', L'�', L'�', L'�', L'♂',

	// 0xFX
	L'�', L'×', L'�', L'/', L',', L'♀', L'0', L'1',
	L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' 
};

Generation1::Generation1(uint8_t* memory)
	: Game(memory)
{
	gameTextToWchar(m_trainerName, &memory[G10E_TRAINER_NAME], sizeof(m_trainerName) / sizeof(*m_trainerName));
}

void Generation1::gameTextToWchar(wchar_t* out, const uint8_t* gameText, size_t len) {
	int i;
	for (i = 0; i < len; ++i) {
		out[i] = charMapGen1En[gameText[i]];
	}
}

const wchar_t* Generation1::trainerName() const {
	return m_trainerName;
}

Pokemon Generation1::partyPokemon(int i) {
	uint8_t* pstart = &m_memory[G10E_PARTY_POKEMON + 2 + 6 + sizeof(G1PartyPokemonData) * i];
	uint8_t* nstart = &m_memory[G10E_PARTY_POKEMON + 2 + (sizeof(G1PartyPokemonData) + 12) * 6 + 11 * i];
	uint8_t* tstart = &m_memory[G10E_PARTY_POKEMON + 2 + (sizeof(G1PartyPokemonData) + 1) * 6 + 11 * i];
	return Pokemon(new G1PartyPokemon(pstart, nstart, tstart));
}

unsigned Generation1::nPartyPokemon() const {
	return m_memory[G10E_PARTY_POKEMON];
}

Pokemon Generation1::boxPokemon(int box, int i) {
	size_t start;
	if (box == BOX_CURRENT) {
		start = G10E_CURRENT_BOX;
	} else {
		start = G10E_BOX_1 + (box - 1) * G1_BOX_SIZE;
	}
	uint8_t* pstart = &m_memory[start + 2 + 20 + sizeof(G1BasePokemonData) * i];
	uint8_t* nstart = &m_memory[start + 2 + (sizeof(G1BasePokemonData) + 12) * 20 + 11 * i];
	uint8_t* tstart = &m_memory[start + 2 + (sizeof(G1BasePokemonData) + 1) * 20 + 11 * i];
	return Pokemon(new G1BasePokemon(pstart, nstart, tstart));
}

unsigned Generation1::nBoxPokemon(int box) const {
	size_t start;
	if (box == BOX_CURRENT) {
		start = G10E_CURRENT_BOX;
	} else {
		start = G10E_BOX_1 + (box - 1) * G1_BOX_SIZE;
	}
	return m_memory[start];
}

G1BasePokemon::G1BasePokemon(uint8_t* data, uint8_t* name, uint8_t* ot)
	: m_data(reinterpret_cast<G1BasePokemonData*>(data))
{
	Generation1::gameTextToWchar(m_name, name, sizeof(m_name) / sizeof(*m_name));
	Generation1::gameTextToWchar(m_ot, ot, sizeof(m_ot) / sizeof(*m_ot));
}

const wchar_t* G1BasePokemon::name() const {
	return m_name;
}

const wchar_t* G1BasePokemon::otName() const {
	return m_ot;
}

uint16_t G1BasePokemon::otId() const {
	return R16(m_data->otId);
}

unsigned G1BasePokemon::xp() const {
	return R24(m_data->xp);
}

unsigned G1BasePokemon::currentHp() const {
	return R16(m_data->currentHp);
}

Type G1BasePokemon::type1() const {
	return typeMapping[m_data->type1];
}

Type G1BasePokemon::type2() const {
	return typeMapping[m_data->type2];
}

G1PartyPokemon::G1PartyPokemon(uint8_t* data, uint8_t* name, uint8_t* ot)
	: G1BasePokemon(data, name, ot)
	, m_data(reinterpret_cast<G1PartyPokemonData*>(data))
{
}
