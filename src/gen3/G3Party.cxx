#include "gen3/G3Party.h"

#include "gen3/Generation3.h"
#include "gen3/G3PartyPokemon.h"

enum {
	G30E_PARTY_POKEMON = 0x0234,
};

G3Party::G3Party(Generation3* gen)
	: m_gen(gen)
	, m_start(&gen->section(Generation3::Section::BAG)->data[G30E_PARTY_POKEMON])
{
}

std::unique_ptr<Pokemon> G3Party::at(unsigned i) {
	if (i >= length()) {
		return nullptr;
	}
	uint8_t* pstart = &m_start[4 + sizeof(G3PartyPokemonData) * i];
	return std::unique_ptr<Pokemon>(new G3PartyPokemon(m_gen, reinterpret_cast<G3PartyPokemonData*>(pstart)));
}

unsigned G3Party::length() const {
	return m_start[0];
}

unsigned G3Party::capacity() const {
	return 6;
}

void G3Party::remove(unsigned i) {
	unsigned len = length();
	if (i >= len) {
		return;
	}
	--m_start[0];
	uint8_t* pstart = &m_start[4 + sizeof(G3PartyPokemonData) * i];
	uint8_t* pnext = &m_start[4 + sizeof(G3PartyPokemonData) * (i + 1)];
	uint8_t* pend = &m_start[4 + sizeof(G3PartyPokemonData) * m_start[0]];
	memmove(pstart, pnext, sizeof(G3PartyPokemonData) * (len - i - 1));
	memset(pend, 0, sizeof(G3PartyPokemonData) * (capacity() - m_start[0]));
}

bool G3Party::insert(const Pokemon& pokemon) {
	unsigned len = length();
	if (len >= capacity()) {
		return false;
	}

	std::unique_ptr<G3PartyPokemon> convertedPokemon = G3PartyPokemon::copy(m_gen, pokemon);
	if (!convertedPokemon) {
		return false;
	}

	convertedPokemon->crypt();
	const G3PartyPokemonData* data = reinterpret_cast<const G3PartyPokemonData*>(convertedPokemon->data(nullptr));

	++m_start[0];
	uint8_t* pstart = &m_start[4 + sizeof(G3PartyPokemonData) * len];
	memmove(pstart, data, sizeof(G3PartyPokemonData));

	return true;
}
