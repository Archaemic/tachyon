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

const static Pokemon::Id idMapping[256] = {
	Pokemon::MISSINGNO,
	Pokemon::RHYDON,
	Pokemon::KANGASKHAN,
	Pokemon::NIDORAN_M,
	Pokemon::CLEFAIRY,
	Pokemon::SPEAROW,
	Pokemon::VOLTORB,
	Pokemon::NIDOKING,
	Pokemon::SLOWBRO,
	Pokemon::IVYSAUR,
	Pokemon::EXEGGUTOR,
	Pokemon::LICKITUNG,
	Pokemon::EXEGGCUTE,
	Pokemon::GRIMER,
	Pokemon::GENGAR,
	Pokemon::NIDORAN_M,
	Pokemon::NIDOQUEEN,
	Pokemon::CUBONE,
	Pokemon::RHYHORN,
	Pokemon::LAPRAS,
	Pokemon::ARCANINE,
	Pokemon::MEW,
	Pokemon::GYARADOS,
	Pokemon::SHELLDER,
	Pokemon::TENTACOOL,
	Pokemon::GASTLY,
	Pokemon::SCYTHER,
	Pokemon::STARYU,
	Pokemon::BLASTOISE,
	Pokemon::PINSIR,
	Pokemon::TANGELA,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::GROWLITHE,
	Pokemon::ONIX,
	Pokemon::FEAROW,
	Pokemon::PIDGEY,
	Pokemon::SLOWPOKE,
	Pokemon::KADABRA,
	Pokemon::GRAVELER,
	Pokemon::CHANSEY,
	Pokemon::MACHOKE,
	Pokemon::MR_MIME,
	Pokemon::HITMONLEE,
	Pokemon::HITMONCHAN,
	Pokemon::ARBOK,
	Pokemon::PARASECT,
	Pokemon::PSYDUCK,
	Pokemon::DROWZEE,
	Pokemon::GOLEM,
	Pokemon::MISSINGNO,
	Pokemon::MAGMAR,
	Pokemon::MISSINGNO,
	Pokemon::ELECTABUZZ,
	Pokemon::MAGNETON,
	Pokemon::KOFFING,
	Pokemon::MISSINGNO,
	Pokemon::MANKEY,
	Pokemon::SEEL,
	Pokemon::DIGLETT,
	Pokemon::TAUROS,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::FARFETCH_D,
	Pokemon::VENONAT,
	Pokemon::DRAGONITE,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::DODUO,
	Pokemon::POLIWAG,
	Pokemon::JYNX,
	Pokemon::MOLTRES,
	Pokemon::ARTICUNO,
	Pokemon::ZAPDOS,
	Pokemon::DITTO,
	Pokemon::MEOWTH,
	Pokemon::KRABBY,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::VULPIX,
	Pokemon::NINETALES,
	Pokemon::PIKACHU,
	Pokemon::RAICHU,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::DRATINI,
	Pokemon::DRAGONAIR,
	Pokemon::KABUTO,
	Pokemon::KABUTOPS,
	Pokemon::HORSEA,
	Pokemon::SEADRA,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::SANDSHREW,
	Pokemon::SANDSLASH,
	Pokemon::OMANYTE,
	Pokemon::OMASTAR,
	Pokemon::JIGGLYPUFF,
	Pokemon::WIGGLYTUFF,
	Pokemon::EEVEE,
	Pokemon::FLAREON,
	Pokemon::JOLTEON,
	Pokemon::VAPOREON,
	Pokemon::MACHOP,
	Pokemon::ZUBAT,
	Pokemon::EKANS,
	Pokemon::PARAS,
	Pokemon::POLIWHIRL,
	Pokemon::POLIWRATH,
	Pokemon::WEEDLE,
	Pokemon::KAKUNA,
	Pokemon::BEEDRILL,
	Pokemon::MISSINGNO,
	Pokemon::DODRIO,
	Pokemon::PRIMEAPE,
	Pokemon::DUGTRIO,
	Pokemon::VENOMOTH,
	Pokemon::DEWGONG,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::CATERPIE,
	Pokemon::METAPOD,
	Pokemon::BUTTERFREE,
	Pokemon::MACHAMP,
	Pokemon::MISSINGNO,
	Pokemon::GOLDUCK,
	Pokemon::HYPNO,
	Pokemon::GOLBAT,
	Pokemon::MEWTWO,
	Pokemon::SNORLAX,
	Pokemon::MAGIKARP,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MUK,
	Pokemon::MISSINGNO,
	Pokemon::KINGLER,
	Pokemon::CLOYSTER,
	Pokemon::MISSINGNO,
	Pokemon::ELECTRODE,
	Pokemon::CLEFABLE,
	Pokemon::WEEZING,
	Pokemon::PERSIAN,
	Pokemon::MAROWAK,
	Pokemon::MISSINGNO,
	Pokemon::HAUNTER,
	Pokemon::ABRA,
	Pokemon::ALAKAZAM,
	Pokemon::PIDGEOTTO,
	Pokemon::PIDGEOT,
	Pokemon::STARMIE,
	Pokemon::BULBASAUR,
	Pokemon::VENUSAUR,
	Pokemon::TENTACRUEL,
	Pokemon::MISSINGNO,
	Pokemon::GOLDEEN,
	Pokemon::SEAKING,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::PONYTA,
	Pokemon::RAPIDASH,
	Pokemon::RATTATA,
	Pokemon::RATICATE,
	Pokemon::NIDORINO,
	Pokemon::NIDORINA,
	Pokemon::GEODUDE,
	Pokemon::PORYGON,
	Pokemon::AERODACTYL,
	Pokemon::MISSINGNO,
	Pokemon::MAGNEMITE,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::CHARMANDER,
	Pokemon::SQUIRTLE,
	Pokemon::CHARMELEON,
	Pokemon::WARTORTLE,
	Pokemon::CHARIZARD,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::MISSINGNO,
	Pokemon::ODDISH,
	Pokemon::GLOOM,
	Pokemon::VILEPLUME,
	Pokemon::BELLSPROUT,
	Pokemon::WEEPINBELL,
	Pokemon::VICTREEBEL
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

Pokemon::Id G1BasePokemon::species() const {
	return idMapping[m_data->pokemonId];
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
