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

const GameBoyGame::ChecksumMapping Generation1::s_checksums[] = {
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

void Generation1::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Game* Generation1::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	if (GameBoyGame::version(Generation1::s_checksums, checksum)) {
		return new Generation1(memory, rom);
	}
	return nullptr;
}

std::unique_ptr<Group> Generation1::party() {
	return std::unique_ptr<Group>(new G1Party(this));
}

std::unique_ptr<Group> Generation1::box(unsigned box) {
	return std::unique_ptr<Group>(new G1Box(this, static_cast<GameBoyGame::Box>(box)));
}

Game::Version Generation1::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	return GameBoyGame::version(s_checksums, checksum);
}

PokemonSpecies* Generation1::species(PokemonSpecies::Id id) {
	PokemonSpecies* species = Game::species(id);
	if (!species) {
		if (id == PokemonSpecies::MEW && version() != Game::G11E_YELLOW) {
			const G1PokemonBaseStats* stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_MEW_STATS]);
			species = new G1PokemonSpecies(stats);
		} else {
			const G1PokemonBaseStats* stats = reinterpret_cast<const G1PokemonBaseStats*>(&rom()[G10E_BASE_STATS]);
			species = new G1PokemonSpecies(&stats[id - 1]);
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

template <>
unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialAttack() const {
	return m_data->special;
}

template <>
unsigned GenericPokemonSpecies<G1PokemonBaseStats>::baseSpecialDefense() const {
	return m_data->special;
}

template <>
uint8_t GenericPokemonSpecies<G1PokemonBaseStats>::genderRatio() const {
	if (id() == PokemonSpecies::NIDORAN_F) {
		return 0xFE;
	}
	if (id() == PokemonSpecies::NIDORAN_M) {
		return 0x00;
	}
	return 0xFF;
}

G1PokemonSpecies::G1PokemonSpecies(const G1PokemonBaseStats* data)
	: GenericPokemonSpecies<G1PokemonBaseStats>(data)
{
}

Type G1PokemonSpecies::mapType(unsigned unmapped) const {
	return typeMapping[static_cast<uint8_t>(unmapped)];
}

G1Party::G1Party(Generation1* gen)
	: GBGroup<G1PartyPokemon>(gen, &gen->ram()[G10E_PARTY_POKEMON])
{
}

unsigned G1Party::capacity() const {
	return 6;
}

G1Box::G1Box(Generation1* gen, GameBoyGame::Box box)
	: GBGroup<G1BasePokemon>(gen, gen->ram() + (
		(box == GameBoyGame::BOX_CURRENT) ? G10E_CURRENT_BOX :
		(box < GameBoyGame::BOX_07) ? (G10E_BOX_1 + (box - 1) * G1_BOX_SIZE) :
		(box <= GameBoyGame::BOX_12) ? (G10E_BOX_7 + (box - 7) * G1_BOX_SIZE) :
		G10E_CURRENT_BOX))
{
}

unsigned G1Box::capacity() const {
	return 20;
}

bool G1TMSet::containsTM(int tm) const {
	return m_set[tm >> 8] & (1 << (tm & 0x7));
}

bool G1TMSet::containsHM(int hm) const {
	return containsTM(hm + 50);
}
