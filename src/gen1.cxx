#include "gen1-private.h"

enum {
	G1_BOX_SIZE = 1122,

	G10E_TRAINER_NAME = 0x2598,
	G10E_PARTY_POKEMON = 0x2F2C,
	G10E_CURRENT_BOX = 0x30C0,
	G10E_BOX_1 = 0x4000,
	G10E_BOX_7 = 0x6000,

	G10E_ID_MAPPING = 0x041023,
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

Generation1::Generation1(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
{
	setTrainerName(gameTextToUTF8(&memory[G10E_TRAINER_NAME], 8));
}

std::unique_ptr<Group> Generation1::party() {
	return std::unique_ptr<Group>(new G1Party(this));
}

std::unique_ptr<Group> Generation1::box(unsigned box) {
	return std::unique_ptr<Group>(new G1Box(this, static_cast<GameBoyGame::Box>(box)));
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

PokemonSpecies* Generation1::species(PokemonSpecies::Id id) {
	PokemonSpecies* species = Game::species(id);
	if (!species) {
		if (id == PokemonSpecies::MEW && version() != Game::G11E_YELLOW) {
			const G1PokemonBaseStats* stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_MEW_STATS]);
			species = new G1PokemonSpecies(stats);
		} else if (id <= PokemonSpecies::MEW && id != PokemonSpecies::MISSINGNO) {
			const G1PokemonBaseStats* stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_BASE_STATS]);
			species = new G1PokemonSpecies(&stats[id - 1]);
		} else {
			const G1PokemonBaseStats* stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_BASE_STATS]);
			species = new G1PokemonSpecies(&stats[-1]);
		}
		putSpecies(id, species);
	}
	return species;
}

template <>
PokemonSpecies* GBPokemon<G1BasePokemonData>::species() const {
	const uint8_t* idMapping = &m_gen->rom()[G10E_ID_MAPPING];
	PokemonSpecies::Id id =  static_cast<PokemonSpecies::Id>(idMapping[m_data->pokemonId]);
	return m_gen->species(id);
}

template <>
PokemonSpecies* GBPokemon<G1PartyPokemonData>::species() const {
	const uint8_t* idMapping = &m_gen->rom()[G10E_ID_MAPPING];
	PokemonSpecies::Id id =  static_cast<PokemonSpecies::Id>(idMapping[m_data->pokemonId]);
	return m_gen->species(id);
}

template <>
unsigned GBPokemon<G1BasePokemonData>::currentHp() const {
	return R16(m_data->currentHp);
}

template <>
Type GBPokemon<G1BasePokemonData>::type1() const {
	return typeMapping[m_data->type1];
}

template <>
Type GBPokemon<G1BasePokemonData>::type2() const {
	return typeMapping[m_data->type2];
}

template <>
unsigned GBPartyPokemon<G1PartyPokemonData>::specialAttack() const {
	return R16(m_data->special);
}

template <>
unsigned GBPartyPokemon<G1PartyPokemonData>::specialDefense() const {
	return R16(m_data->special);
}

G1PokemonSpecies::G1PokemonSpecies(const G1PokemonBaseStats* data)
	: m_data(data)
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

G1Party::G1Party(Generation1* gen)
	: m_gen(gen)
	, m_start(&gen->ram()[G10E_PARTY_POKEMON])
{
}

std::unique_ptr<Pokemon> G1Party::at(unsigned i) {
	uint8_t* pstart = &m_start[2 + 6 + sizeof(G1PartyPokemonData) * i];
	uint8_t* nstart = &m_start[2 + (sizeof(G1PartyPokemonData) + 12) * 6 + 11 * i];
	uint8_t* tstart = &m_start[2 + (sizeof(G1PartyPokemonData) + 1) * 6 + 11 * i];
	return std::unique_ptr<Pokemon>(new G1PartyPokemon(m_gen, pstart, nstart, tstart));
}

unsigned G1Party::length() const {
	return m_start[0];
}

G1Box::G1Box(Generation1* gen, GameBoyGame::Box box)
	: m_gen(gen)
	, m_start(gen->ram())
{
	if (box == GameBoyGame::BOX_CURRENT) {
		m_start += G10E_CURRENT_BOX;
	} else if (box < GameBoyGame::BOX_07) {
		m_start += G10E_BOX_1 + (box - 1) * G1_BOX_SIZE;
	} else {
		m_start += G10E_BOX_7 + (box - 7) * G1_BOX_SIZE;
	}
}

std::unique_ptr<Pokemon> G1Box::at(unsigned i) {
	uint8_t* pstart = &m_start[2 + 20 + sizeof(G1BasePokemonData) * i];
	uint8_t* nstart = &m_start[2 + (sizeof(G1BasePokemonData) + 12) * 20 + 11 * i];
	uint8_t* tstart = &m_start[2 + (sizeof(G1BasePokemonData) + 1) * 20 + 11 * i];
	return std::unique_ptr<Pokemon>(new G1BasePokemon(m_gen, pstart, nstart, tstart));
}

unsigned G1Box::length() const {
	return m_start[0];
}

bool G1TMSet::containsTM(int tm) const {
	return m_set[tm >> 8] & (1 << (tm & 0x7));
}

bool G1TMSet::containsHM(int hm) const {
	return containsTM(hm + 50);
}
