#include "gen2-private.h"

enum {
	G2_BOX_SIZE = 1104,

	G20E_TRAINER_NAME = 0x200B,
	G20E_PARTY_POKEMON = 0x288A,
	G20E_CURRENT_BOX = 0x2D6C,
	G20E_BOX_1 = 0x4000,
	G20E_BOX_8 = 0x6000,

	G21E_PARTY_POKEMON = 0x2865,
	G21E_CURRENT_BOX = 0x2D11,

	G20E_BASE_STATS = 0x051B0B,
	G21E_BASE_STATS = 0x051424,
};

const static struct ChecksumMapping {
	uint16_t checksum;
	Game::Version version;
} checksums[] = {
	{ 0x2D68, Game::G20E_GOLD },
	{ 0, Game::INVALID }
};

const static Type typeMapping[256] = {
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

Generation2::Generation2(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
{
	setTrainerName(gameTextToUTF8(&memory[G20E_TRAINER_NAME], 8));
}

std::unique_ptr<Pokemon> Generation2::partyPokemon(int i) {
	uint8_t* pstart = &m_memory[G20E_PARTY_POKEMON + 2 + 6 + sizeof(G2PartyPokemonData) * i];
	uint8_t* nstart = &m_memory[G20E_PARTY_POKEMON + 2 + (sizeof(G2PartyPokemonData) + 12) * 6 + 11 * i];
	uint8_t* tstart = &m_memory[G20E_PARTY_POKEMON + 2 + (sizeof(G2PartyPokemonData) + 1) * 6 + 11 * i];
	return std::unique_ptr<Pokemon>(new G2PartyPokemon(*this, pstart, nstart, tstart));
}

unsigned Generation2::nPartyPokemon() const {
	return m_memory[G20E_PARTY_POKEMON];
}

std::unique_ptr<Pokemon> Generation2::boxPokemon(int box, int i) {
	size_t start;
	if (box == BOX_CURRENT) {
		start = G20E_CURRENT_BOX;
	} else if (box < BOX_08) {
		start = G20E_BOX_1 + (box - 1) * G2_BOX_SIZE;
	} else {
		start = G20E_BOX_8 + (box - 8) * G2_BOX_SIZE;
	}
	uint8_t* pstart = &m_memory[start + 2 + 20 + sizeof(G2BasePokemonData) * i];
	uint8_t* nstart = &m_memory[start + 2 + (sizeof(G2BasePokemonData) + 12) * 20 + 11 * i];
	uint8_t* tstart = &m_memory[start + 2 + (sizeof(G2BasePokemonData) + 1) * 20 + 11 * i];
	return std::unique_ptr<Pokemon>(new G2BasePokemon(*this, pstart, nstart, tstart));
}

unsigned Generation2::nBoxPokemon(int box) const {
	size_t start;
	if (box == BOX_CURRENT) {
		start = G20E_CURRENT_BOX;
	} else if (box < BOX_08) {
		start = G20E_BOX_1 + (box - 1) * G2_BOX_SIZE;
	} else {
		start = G20E_BOX_8 + (box - 8) * G2_BOX_SIZE;
	}
	return m_memory[start];
}

Game::Version Generation2::version() const {
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

G2BasePokemon::G2BasePokemon(Generation2& gen, uint8_t* data, uint8_t* name, uint8_t* ot)
	: GBPokemon(name, ot)
	, m_gen(gen)
	, m_data(reinterpret_cast<G2BasePokemonData*>(data))
{
}

PokemonSpecies* G2BasePokemon::species() const {
	const G2PokemonBaseStats* stats = reinterpret_cast<const G2PokemonBaseStats*>(&m_gen.rom()[G20E_BASE_STATS]);
	if (m_data->species <= 251) {
		return new G2PokemonSpecies(m_gen, &stats[m_data->species - 1]);
	} else {
		return new G2PokemonSpecies(m_gen, &stats[-1]);
	}
}
uint16_t G2BasePokemon::otId() const {
	return R16(m_data->otId);
}

unsigned G2BasePokemon::xp() const {
	return R24(m_data->xp);
}

unsigned G2BasePokemon::currentHp() const {
	return maxHp();
}

unsigned G2BasePokemon::ivHp() const {
	return
		((m_data->ivAttack & 1) << 3) |
		((m_data->ivDefense & 1) << 2) |
		((m_data->ivSpeed & 1) << 1) |
		(m_data->ivSpecial & 1);
}

unsigned G2BasePokemon::ivAttack() const {
	return m_data->ivAttack;
}

unsigned G2BasePokemon::ivDefense() const {
	return m_data->ivDefense;
}

unsigned G2BasePokemon::ivSpeed() const {
	return m_data->ivSpeed;
}

unsigned G2BasePokemon::ivSpecialAttack() const {
	return m_data->ivSpecial;
}

unsigned G2BasePokemon::ivSpecialDefense() const {
	return m_data->ivSpecial;
}

unsigned G2BasePokemon::evHp() const {
	return R16(m_data->evHp);
}

unsigned G2BasePokemon::evAttack() const {
	return R16(m_data->evAttack);
}

unsigned G2BasePokemon::evDefense() const {
	return R16(m_data->evDefense);
}

unsigned G2BasePokemon::evSpeed() const {
	return R16(m_data->evSpeed);
}

unsigned G2BasePokemon::evSpecialAttack() const {
	return R16(m_data->evSpecial);
}

unsigned G2BasePokemon::evSpecialDefense() const {
	return R16(m_data->evSpecial);
}

Type G2BasePokemon::type1() const {
	return species()->type1();
}

Type G2BasePokemon::type2() const {
	return species()->type2();
}

unsigned G2BasePokemon::move1() const {
	return m_data->moves.move1;
}

unsigned G2BasePokemon::move2() const {
	return m_data->moves.move2;
}

unsigned G2BasePokemon::move3() const {
	return m_data->moves.move3;
}

unsigned G2BasePokemon::move4() const {
	return m_data->moves.move4;
}

G2PartyPokemon::G2PartyPokemon(Generation2& gen, uint8_t* data, uint8_t* name, uint8_t* ot)
	: G2BasePokemon(gen, data, name, ot)
	, m_data(reinterpret_cast<G2PartyPokemonData*>(data))
{
}

unsigned G2PartyPokemon::level() const {
	return m_data->level;
}

unsigned G2PartyPokemon::currentHp() const {
	return R16(m_data->currentHp);
}

unsigned G2PartyPokemon::maxHp() const {
	return R16(m_data->maxHp);
}

unsigned G2PartyPokemon::attack() const {
	return R16(m_data->attack);
}

unsigned G2PartyPokemon::defense() const {
	return R16(m_data->defense);
}

unsigned G2PartyPokemon::speed() const {
	return R16(m_data->speed);
}

unsigned G2PartyPokemon::specialAttack() const {
	return R16(m_data->specialAttack);
}

unsigned G2PartyPokemon::specialDefense() const {
	return R16(m_data->specialDefense);
}

G2PokemonSpecies::G2PokemonSpecies(Generation2& gen, const G2PokemonBaseStats* data)
	: m_gen(gen)
	, m_data(data)
{
}

PokemonSpecies::Id G2PokemonSpecies::id() const {
	return (PokemonSpecies::Id) m_data->species;
}

unsigned G2PokemonSpecies::baseHp() const {
	return m_data->hp;
}

unsigned G2PokemonSpecies::baseAttack() const {
	return m_data->attack;
}

unsigned G2PokemonSpecies::baseDefense() const {
	return m_data->defense;
}

unsigned G2PokemonSpecies::baseSpeed() const {
	return m_data->speed;
}

unsigned G2PokemonSpecies::baseSpecialAttack() const {
	return m_data->specialAttack;
}

unsigned G2PokemonSpecies::baseSpecialDefense() const {
	return m_data->specialDefense;
}

PokemonSpecies::GrowthRate G2PokemonSpecies::growthRate() const {
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

Type G2PokemonSpecies::type1() const {
	return typeMapping[m_data->type1];
}

Type G2PokemonSpecies::type2() const {
	return typeMapping[m_data->type2];
}

bool G2TMSet::containsTM(int tm) const {
	return m_set[tm >> 8] & (1 << (tm & 0x7));
}

bool G2TMSet::containsHM(int hm) const {
	return containsTM(hm + 50);
}
