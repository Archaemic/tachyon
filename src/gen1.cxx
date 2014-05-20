#include "gen1-private.h"

#include <cmath>

#define R16(V) (((V) & 0xFF) << 8) | (((V) & 0xFF00) >> 8)
#define R24(V) (((V) & 0xFF) << 16) | ((V) & 0xFF00) | (((V) & 0xFF0000) >> 16)
#define R32(V) (((V) & 0xFF) << 24) | (((V) & 0xFF00) << 8) | (((V) & 0xFF0000) >> 8) | (((V) & 0xFF000000) >> 24)

enum {
	G1_BOX_SIZE = 1122,

	G10E_TRAINER_NAME = 0x2598,
	G10E_PARTY_POKEMON = 0x2F2C,
	G10E_CURRENT_BOX = 0x30C0,
	G10E_BOX_1 = 0x4000,
	G10E_BOX_7 = 0x6000,

	G10E_BASE_STATS = 0x0383DE,
	G10E_MEW_STATS = 0x00425B,
};

const static struct ChecksumMapping {
	uint16_t checksum;
	Game::Version version;
} checksums[] = {
	{ 0x66B8, Game::G10J_RED },
	{ 0xC1A2, Game::G10J_RED },
	{ 0xE691, Game::G10E_RED },
	{ 0, Game::INVALID }
};

const static PokemonSpecies::Id idMapping[256] = {
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::RHYDON,
	PokemonSpecies::KANGASKHAN,
	PokemonSpecies::NIDORAN_M,
	PokemonSpecies::CLEFAIRY,
	PokemonSpecies::SPEAROW,
	PokemonSpecies::VOLTORB,
	PokemonSpecies::NIDOKING,
	PokemonSpecies::SLOWBRO,
	PokemonSpecies::IVYSAUR,
	PokemonSpecies::EXEGGUTOR,
	PokemonSpecies::LICKITUNG,
	PokemonSpecies::EXEGGCUTE,
	PokemonSpecies::GRIMER,
	PokemonSpecies::GENGAR,
	PokemonSpecies::NIDORAN_M,
	PokemonSpecies::NIDOQUEEN,
	PokemonSpecies::CUBONE,
	PokemonSpecies::RHYHORN,
	PokemonSpecies::LAPRAS,
	PokemonSpecies::ARCANINE,
	PokemonSpecies::MEW,
	PokemonSpecies::GYARADOS,
	PokemonSpecies::SHELLDER,
	PokemonSpecies::TENTACOOL,
	PokemonSpecies::GASTLY,
	PokemonSpecies::SCYTHER,
	PokemonSpecies::STARYU,
	PokemonSpecies::BLASTOISE,
	PokemonSpecies::PINSIR,
	PokemonSpecies::TANGELA,
	PokemonSpecies::SCIZOR,
	PokemonSpecies::SHUCKLE,
	PokemonSpecies::GROWLITHE,
	PokemonSpecies::ONIX,
	PokemonSpecies::FEAROW,
	PokemonSpecies::PIDGEY,
	PokemonSpecies::SLOWPOKE,
	PokemonSpecies::KADABRA,
	PokemonSpecies::GRAVELER,
	PokemonSpecies::CHANSEY,
	PokemonSpecies::MACHOKE,
	PokemonSpecies::MR_MIME,
	PokemonSpecies::HITMONLEE,
	PokemonSpecies::HITMONCHAN,
	PokemonSpecies::ARBOK,
	PokemonSpecies::PARASECT,
	PokemonSpecies::PSYDUCK,
	PokemonSpecies::DROWZEE,
	PokemonSpecies::GOLEM,
	PokemonSpecies::HERACROSS,
	PokemonSpecies::MAGMAR,
	PokemonSpecies::HO_OH,
	PokemonSpecies::ELECTABUZZ,
	PokemonSpecies::MAGNETON,
	PokemonSpecies::KOFFING,
	PokemonSpecies::SNEASEL,
	PokemonSpecies::MANKEY,
	PokemonSpecies::SEEL,
	PokemonSpecies::DIGLETT,
	PokemonSpecies::TAUROS,
	PokemonSpecies::TEDDIURSA,
	PokemonSpecies::URSARING,
	PokemonSpecies::SLUGMA,
	PokemonSpecies::FARFETCH_D,
	PokemonSpecies::VENONAT,
	PokemonSpecies::DRAGONITE,
	PokemonSpecies::MAGCARGO,
	PokemonSpecies::SWINUB,
	PokemonSpecies::PILOSWINE,
	PokemonSpecies::DODUO,
	PokemonSpecies::POLIWAG,
	PokemonSpecies::JYNX,
	PokemonSpecies::MOLTRES,
	PokemonSpecies::ARTICUNO,
	PokemonSpecies::ZAPDOS,
	PokemonSpecies::DITTO,
	PokemonSpecies::MEOWTH,
	PokemonSpecies::KRABBY,
	PokemonSpecies::CORSOLA,
	PokemonSpecies::REMORAID,
	PokemonSpecies::OCTILLERY,
	PokemonSpecies::VULPIX,
	PokemonSpecies::NINETALES,
	PokemonSpecies::PIKACHU,
	PokemonSpecies::RAICHU,
	PokemonSpecies::DELIBIRD,
	PokemonSpecies::MANTINE,
	PokemonSpecies::DRATINI,
	PokemonSpecies::DRAGONAIR,
	PokemonSpecies::KABUTO,
	PokemonSpecies::KABUTOPS,
	PokemonSpecies::HORSEA,
	PokemonSpecies::SEADRA,
	PokemonSpecies::SKARMORY,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::HOUNDOUR,
	PokemonSpecies::SANDSLASH,
	PokemonSpecies::OMANYTE,
	PokemonSpecies::OMASTAR,
	PokemonSpecies::JIGGLYPUFF,
	PokemonSpecies::WIGGLYTUFF,
	PokemonSpecies::EEVEE,
	PokemonSpecies::FLAREON,
	PokemonSpecies::JOLTEON,
	PokemonSpecies::VAPOREON,
	PokemonSpecies::MACHOP,
	PokemonSpecies::ZUBAT,
	PokemonSpecies::EKANS,
	PokemonSpecies::PARAS,
	PokemonSpecies::POLIWHIRL,
	PokemonSpecies::POLIWRATH,
	PokemonSpecies::WEEDLE,
	PokemonSpecies::KAKUNA,
	PokemonSpecies::BEEDRILL,
	PokemonSpecies::HOUNDOOM,
	PokemonSpecies::DODRIO,
	PokemonSpecies::PRIMEAPE,
	PokemonSpecies::DUGTRIO,
	PokemonSpecies::VENOMOTH,
	PokemonSpecies::DEWGONG,
	PokemonSpecies::KINGDRA,
	PokemonSpecies::PHANPY,
	PokemonSpecies::CATERPIE,
	PokemonSpecies::METAPOD,
	PokemonSpecies::BUTTERFREE,
	PokemonSpecies::MACHAMP,
	PokemonSpecies::DONPHAN,
	PokemonSpecies::GOLDUCK,
	PokemonSpecies::HYPNO,
	PokemonSpecies::GOLBAT,
	PokemonSpecies::MEWTWO,
	PokemonSpecies::SNORLAX,
	PokemonSpecies::MAGIKARP,
	PokemonSpecies::PORYGON2,
	PokemonSpecies::STANTLER,
	PokemonSpecies::MUK,
	PokemonSpecies::SMEARGLE,
	PokemonSpecies::KINGLER,
	PokemonSpecies::CLOYSTER,
	PokemonSpecies::TYROGUE,
	PokemonSpecies::ELECTRODE,
	PokemonSpecies::CLEFABLE,
	PokemonSpecies::WEEZING,
	PokemonSpecies::PERSIAN,
	PokemonSpecies::MAROWAK,
	PokemonSpecies::HITMONTOP,
	PokemonSpecies::HAUNTER,
	PokemonSpecies::ABRA,
	PokemonSpecies::ALAKAZAM,
	PokemonSpecies::PIDGEOTTO,
	PokemonSpecies::PIDGEOT,
	PokemonSpecies::STARMIE,
	PokemonSpecies::BULBASAUR,
	PokemonSpecies::VENUSAUR,
	PokemonSpecies::TENTACRUEL,
	PokemonSpecies::SMOOCHUM,
	PokemonSpecies::GOLDEEN,
	PokemonSpecies::SEAKING,
	PokemonSpecies::ELEKID,
	PokemonSpecies::MAGBY,
	PokemonSpecies::MILTANK,
	PokemonSpecies::BLISSEY,
	PokemonSpecies::PONYTA,
	PokemonSpecies::RAPIDASH,
	PokemonSpecies::RATTATA,
	PokemonSpecies::RATICATE,
	PokemonSpecies::NIDORINO,
	PokemonSpecies::NIDORINA,
	PokemonSpecies::GEODUDE,
	PokemonSpecies::PORYGON,
	PokemonSpecies::AERODACTYL,
	PokemonSpecies::RAIKOU,
	PokemonSpecies::MAGNEMITE,
	PokemonSpecies::ENTEI,
	PokemonSpecies::SUICUNE,
	PokemonSpecies::CHARMANDER,
	PokemonSpecies::SQUIRTLE,
	PokemonSpecies::CHARMELEON,
	PokemonSpecies::WARTORTLE,
	PokemonSpecies::CHARIZARD,
	PokemonSpecies::LARVITAR,
	PokemonSpecies::PUPITAR,
	PokemonSpecies::TYRANITAR,
	PokemonSpecies::LUGIA,
	PokemonSpecies::ODDISH,
	PokemonSpecies::GLOOM,
	PokemonSpecies::VILEPLUME,
	PokemonSpecies::BELLSPROUT,
	PokemonSpecies::WEEPINBELL,
	PokemonSpecies::VICTREEBEL
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
	L'\'', L'P', L'M', L'-', L'�', L'�', L'?', L'!',
	L'.', L'�', L'�', L'�', L'�', L'�', L'�', L'♂',

	// 0xFX
	L'�', L'×', L'�', L'/', L',', L'♀', L'0', L'1',
	L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' 
};

Generation1::Generation1(uint8_t* memory, const uint8_t* rom)
	: Game(memory, rom)
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
	return Pokemon(new G1PartyPokemon(*this, pstart, nstart, tstart));
}

unsigned Generation1::nPartyPokemon() const {
	return m_memory[G10E_PARTY_POKEMON];
}

Pokemon Generation1::boxPokemon(int box, int i) {
	size_t start;
	if (box == BOX_CURRENT) {
		start = G10E_CURRENT_BOX;
	} else if (box < BOX_07) {
		start = G10E_BOX_1 + (box - 1) * G1_BOX_SIZE;
	} else {
		start = G10E_BOX_7 + (box - 7) * G1_BOX_SIZE;
	}
	uint8_t* pstart = &m_memory[start + 2 + 20 + sizeof(G1BasePokemonData) * i];
	uint8_t* nstart = &m_memory[start + 2 + (sizeof(G1BasePokemonData) + 12) * 20 + 11 * i];
	uint8_t* tstart = &m_memory[start + 2 + (sizeof(G1BasePokemonData) + 1) * 20 + 11 * i];
	return Pokemon(new G1BasePokemon(*this, pstart, nstart, tstart));
}

unsigned Generation1::nBoxPokemon(int box) const {
	size_t start;
	if (box == BOX_CURRENT) {
		start = G10E_CURRENT_BOX;
	} else if (box < BOX_07) {
		start = G10E_BOX_1 + (box - 1) * G1_BOX_SIZE;
	} else {
		start = G10E_BOX_7 + (box - 7) * G1_BOX_SIZE;
	}
	return m_memory[start];
}

Game::Version Generation1::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	const ChecksumMapping* mapping = checksums;
	while (mapping->checksum) {
		if (mapping->checksum == checksum) {
			break;
		}
		++mapping;
	}
	return mapping->version;
}

G1BasePokemon::G1BasePokemon(const Generation1& gen, uint8_t* data, uint8_t* name, uint8_t* ot)
	: m_gen(gen)
	, m_data(reinterpret_cast<G1BasePokemonData*>(data))
{
	Generation1::gameTextToWchar(m_name, name, sizeof(m_name) / sizeof(*m_name));
	Generation1::gameTextToWchar(m_ot, ot, sizeof(m_ot) / sizeof(*m_ot));
}

const wchar_t* G1BasePokemon::name() const {
	return m_name;
}

PokemonSpecies G1BasePokemon::species() const {
	PokemonSpecies::Id id = idMapping[m_data->pokemonId];
	if (id == PokemonSpecies::MEW && m_gen.version() != Game::G11E_YELLOW) {
		G1PokemonBaseStats* stats = (G1PokemonBaseStats*) &m_gen.rom()[G10E_MEW_STATS];
		return PokemonSpecies(new G1PokemonSpecies(m_gen, stats));
	} else if (id <= PokemonSpecies::MEW && id != PokemonSpecies::MISSINGNO) {
		G1PokemonBaseStats* stats = (G1PokemonBaseStats*) &m_gen.rom()[G10E_BASE_STATS];
		return PokemonSpecies(new G1PokemonSpecies(m_gen, &stats[id - 1]));
	} else {
		G1PokemonBaseStats* stats = (G1PokemonBaseStats*) &m_gen.rom()[G10E_BASE_STATS];
		return PokemonSpecies(new G1PokemonSpecies(m_gen, &stats[-1]));
	}
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

unsigned G1BasePokemon::ivHp() const {
	return
		((m_data->ivAttack & 1) << 3) |
		((m_data->ivDefense & 1) << 2) |
		((m_data->ivSpeed & 1) << 1) |
		(m_data->ivSpecial & 1);
}

unsigned G1BasePokemon::ivAttack() const {
	return m_data->ivAttack;
}

unsigned G1BasePokemon::ivDefense() const {
	return m_data->ivDefense;
}

unsigned G1BasePokemon::ivSpeed() const {
	return m_data->ivSpeed;
}

unsigned G1BasePokemon::ivSpecialAttack() const {
	return m_data->ivSpecial;
}

unsigned G1BasePokemon::ivSpecialDefense() const {
	return m_data->ivSpecial;
}

unsigned G1BasePokemon::evHp() const {
	return R16(m_data->evHp);
}

unsigned G1BasePokemon::evAttack() const {
	return R16(m_data->evAttack);
}

unsigned G1BasePokemon::evDefense() const {
	return R16(m_data->evDefense);
}

unsigned G1BasePokemon::evSpeed() const {
	return R16(m_data->evSpeed);
}

unsigned G1BasePokemon::evSpecialAttack() const {
	return R16(m_data->evSpecial);
}

unsigned G1BasePokemon::evSpecialDefense() const {
	return R16(m_data->evSpecial);
}

Type G1BasePokemon::type1() const {
	return typeMapping[m_data->type1];
}

Type G1BasePokemon::type2() const {
	return typeMapping[m_data->type2];
}

unsigned G1BasePokemon::maxHp() const {
	PokemonSpecies sp = species();
	return (ivHp() + sp.baseHp() + int(sqrt(evHp())) / 8 + 50) * level() / 50 + 10;
}

unsigned G1BasePokemon::attack() const {
	PokemonSpecies sp = species();
	return stat(ivAttack(), sp.baseAttack(), evAttack());
}

unsigned G1BasePokemon::defense() const {
	PokemonSpecies sp = species();
	return stat(ivDefense(), sp.baseDefense(), evDefense());
}

unsigned G1BasePokemon::speed() const {
	PokemonSpecies sp = species();
	return stat(ivSpeed(), sp.baseSpeed(), evSpeed());
}

unsigned G1BasePokemon::specialAttack() const {
	PokemonSpecies sp = species();
	return stat(ivSpecialAttack(), sp.baseSpecialAttack(), evSpecialAttack());
}

unsigned G1BasePokemon::specialDefense() const {
	PokemonSpecies sp = species();
	return stat(ivSpecialDefense(), sp.baseSpecialDefense(), evSpecialDefense());
}

unsigned G1BasePokemon::stat(unsigned iv, unsigned base, unsigned ev) const {
	return (iv + base + int(sqrt(ev)) / 8) * level() / 50 + 5;
}

G1PartyPokemon::G1PartyPokemon(const Generation1& gen, uint8_t* data, uint8_t* name, uint8_t* ot)
	: G1BasePokemon(gen, data, name, ot)
	, m_data(reinterpret_cast<G1PartyPokemonData*>(data))
{
}

unsigned G1PartyPokemon::level() const {
	return m_data->level;
}

unsigned G1PartyPokemon::maxHp() const {
	return R16(m_data->maxHp);
}

unsigned G1PartyPokemon::attack() const {
	return R16(m_data->attack);
}

unsigned G1PartyPokemon::defense() const {
	return R16(m_data->defense);
}

unsigned G1PartyPokemon::speed() const {
	return R16(m_data->speed);
}

unsigned G1PartyPokemon::specialAttack() const {
	return R16(m_data->special);
}

unsigned G1PartyPokemon::specialDefense() const {
	return R16(m_data->special);
}

G1PokemonSpecies::G1PokemonSpecies(const Generation1& gen, G1PokemonBaseStats* data)
	: m_gen(gen)
	, m_data(data)
{
}

PokemonSpecies::Id G1PokemonSpecies::id() const {
	return (PokemonSpecies::Id) m_data->species;
}

unsigned G1PokemonSpecies::baseHp() const {
	return m_data->hp;
}

unsigned G1PokemonSpecies::baseAttack() const {
	return m_data->attack;
}

unsigned G1PokemonSpecies::baseDefense() const {
	return m_data->defense;
}

unsigned G1PokemonSpecies::baseSpeed() const {
	return m_data->speed;
}

unsigned G1PokemonSpecies::baseSpecialAttack() const {
	return m_data->special;
}

unsigned G1PokemonSpecies::baseSpecialDefense() const {
	return m_data->special;
}

PokemonSpecies::GrowthRate G1PokemonSpecies::growthRate() const {
	switch (m_data->growthRate) {
	case 0:
		return PokemonSpecies::LEVEL_MEDIUM_FAST;
	case 3:
		return PokemonSpecies::LEVEL_MEDIUM_SLOW;
	case 4:
		return PokemonSpecies::LEVEL_FAST;
	case 5:
		return PokemonSpecies::LEVEL_SLOW;
	default:
		return PokemonSpecies::LEVEL_MEDIUM_FAST;
	}
}

Type G1PokemonSpecies::type1() const {
	return typeMapping[m_data->type1];
}

Type G1PokemonSpecies::type2() const {
	return typeMapping[m_data->type2];
}

bool G1TMSet::containsTM(int tm) const {
	return m_set[tm >> 8] & (1 << (tm & 0x7));
}

bool G1TMSet::containsHM(int hm) const {
	return containsTM(hm + 50);
}
