#include "gen2-private.h"

struct Range {
	unsigned start;
	unsigned end;
};

static const Range checksumRegionsG20E[2][5] = {
	{
		{ 0x2009, 0x222F },
		{ 0x222F, 0x23D9 },
		{ 0x23D9, 0x2856 },
		{ 0x2856, 0x288A },
		{ 0x288A, 0x2D69 }
	},
	{
		{ 0x15C7, 0x17ED },
		{ 0x3D96, 0x3F40 },
		{ 0x0C6B, 0x10E8 },
		{ 0x7E39, 0x7E6D },
		{ 0x10E8, 0x15C7 }
	}
};

static const Range checksumRegionsG21E[2] = {
	{ 0x2009, 0x2B83 },
	{ 0x1209, 0x1D83 }
};

enum {
	G2_BOX_SIZE = 1104,

	G20E_TRAINER_NAME = 0x200B,
	G20E_CURRENT_BOX_ID = 0x2724,
	G21E_CURRENT_BOX_ID = 0x2700,
	G20E_PARTY_POKEMON = 0x288A,
	G21E_PARTY_POKEMON = 0x2865,
	G20E_CHECKSUM_1 = 0x2D69,
	G20E_CHECKSUM_2 = 0x7E6D,
	G21E_CHECKSUM_1 = 0x2D0D,
	G21E_CHECKSUM_2 = 0x1F0D,
	G20E_CURRENT_BOX = 0x2D6C,
	G21E_CURRENT_BOX = 0x2D11,
	G20E_BOX_1 = 0x4000,
	G20E_BOX_8 = 0x6000,

	G20E_BASE_STATS = 0x051B0B,
	G21E_BASE_STATS = 0x051424,
};

const GameBoyGame::ChecksumMapping Generation2::s_checksums[] = {
	{ 0x2D68, Game::G20E_GOLD },
	{ 0, Game::INVALID }
};

Generation2::Generation2(uint8_t* memory, const uint8_t* rom)
	: GameBoyGame(memory, rom)
{
	setTrainerName(gameTextToUTF8(&memory[G20E_TRAINER_NAME], 8));
}

void Generation2::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Game* Generation2::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	uint16_t checksum = *(uint16_t*) &rom[0x14E];
	if (GameBoyGame::version(Generation2::s_checksums, checksum)) {
		return new Generation2(memory, rom);
	}
	return nullptr;
}

std::unique_ptr<Group> Generation2::party() {
	return std::unique_ptr<Group>(new G2Party(this));
}

std::unique_ptr<Group> Generation2::box(unsigned box) {
	return std::unique_ptr<Group>(new G2Box(this, box));
}

unsigned Generation2::numBoxes() const {
	return 14;
}

Game::Version Generation2::version() const {
	uint16_t checksum = *(uint16_t*) &m_rom[0x14E];
	return GameBoyGame::version(s_checksums, checksum);
}

PokemonSpecies* Generation2::species(PokemonSpecies::Id id) {
	PokemonSpecies* species = Game::species(id);
	if (!species) {
		const G2PokemonBaseStats* stats;
		switch (version()) {
		case Game::G20E_GOLD:
		case Game::G20J_GOLD:
		case Game::G20E_SILVER:
		case Game::G20J_SILVER:
		default:
			stats = reinterpret_cast<const G2PokemonBaseStats*>(&rom()[G20E_BASE_STATS]);
			break;
		case Game::G21E_CRYSTAL:
		case Game::G21J_CRYSTAL:
			stats = reinterpret_cast<const G2PokemonBaseStats*>(&rom()[G20E_BASE_STATS]);
			break;
		}
		if (id <= 251) {
			species = new G2PokemonSpecies(&stats[id - 1]);
		} else {
			species = new G2PokemonSpecies(&stats[-1]);
		}
		putSpecies(id, species);
	}
	return species;
}

void Generation2::finalize() {
	uint16_t checksum = 0;
	uint8_t* memory = ram();
	switch (version()) {
	case Game::G20E_GOLD:
	case Game::G20J_GOLD:
	case Game::G20E_SILVER:
	case Game::G20J_SILVER:
	default:
		for (unsigned i = 0; i < 5; ++i) {
			unsigned start = checksumRegionsG20E[0][i].start;
			unsigned newStart = checksumRegionsG20E[1][i].start;
			unsigned end = checksumRegionsG20E[0][i].end;
			for (unsigned offset = 0; offset < end - start; ++offset) {
				checksum += memory[start + offset];
				memory[newStart + offset] = memory[start + offset];
			}
		}
		*reinterpret_cast<uint16_t*>(&memory[G20E_CHECKSUM_1]) = checksum;
		*reinterpret_cast<uint16_t*>(&memory[G20E_CHECKSUM_2]) = checksum;
		break;
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
		unsigned start = checksumRegionsG21E[0].start;
		unsigned newStart = checksumRegionsG21E[1].start;
		unsigned end = checksumRegionsG21E[0].end;
		for (unsigned offset = 0; offset < end - start; ++offset) {
			checksum += memory[start + offset];
			memory[newStart + offset] = memory[start + offset];
		}
		*reinterpret_cast<uint16_t*>(&memory[G21E_CHECKSUM_1]) = checksum;
		*reinterpret_cast<uint16_t*>(&memory[G21E_CHECKSUM_2]) = checksum;
		break;
	}
}

G2PokemonSpecies::G2PokemonSpecies(const G2PokemonBaseStats* data)
	: GenericPokemonSpecies<G2PokemonBaseStats>(data)
{
}

Type G2PokemonSpecies::mapType(unsigned unmapped) const {
	return typeMapping[static_cast<uint8_t>(unmapped)];
}

G2Party::G2Party(Generation2* gen)
	: GBGroup<G2PartyPokemon>(gen)
{
	switch (gen->version()) {
	case Game::G20E_GOLD:
	case Game::G20J_GOLD:
	case Game::G20E_SILVER:
	case Game::G20J_SILVER:
	default:
		setStart(&gen->ram()[G20E_PARTY_POKEMON]);
		break;
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
		setStart(&gen->ram()[G21E_PARTY_POKEMON]);
		break;
	}
}

unsigned G2Party::capacity() const {
	return 6;
}

G2Box::G2Box(Generation2* gen, unsigned box)
	: GBGroup<G2BasePokemon>(gen)
{
	uint8_t* start = gen->ram();
	switch (gen->version()) {
	case Game::G20E_GOLD:
	case Game::G20J_GOLD:
	case Game::G20E_SILVER:
	case Game::G20J_SILVER:
	default:
		if (box == (gen->ram()[G20E_CURRENT_BOX_ID] & 0xF)) {
			start += G20E_CURRENT_BOX;
		} else if (box < 7) {
			start += G20E_BOX_1 + box * G2_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G20E_BOX_8 + (box - 7) * G2_BOX_SIZE;
		} else {
			start += G20E_CURRENT_BOX;
		}
		break;
	case Game::G21E_CRYSTAL:
	case Game::G21J_CRYSTAL:
		if (box == (gen->ram()[G21E_CURRENT_BOX_ID] & 0xF)) {
			start += G21E_CURRENT_BOX;
		} else if (box < 7) {
			start += G20E_BOX_1 + box * G2_BOX_SIZE;
		} else if (box < gen->numBoxes()) {
			start += G20E_BOX_8 + (box - 7) * G2_BOX_SIZE;
		} else {
			start += G21E_CURRENT_BOX;
		}
		break;
	}

	setStart(start);
}

unsigned G2Box::capacity() const {
	return 20;
}

bool G2TMSet::containsTM(int tm) const {
	return m_set[tm >> 8] & (1 << (tm & 0x7));
}

bool G2TMSet::containsHM(int hm) const {
	return containsTM(hm + 50);
}
