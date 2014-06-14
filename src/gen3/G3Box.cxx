#include "gen3/G3Box.h"

#include "gen3/G3BasePokemon.h"

G3Box::G3Box(Generation3* gen, G3BasePokemonData* start, const std::string& name)
	: m_gen(gen)
	, m_start(start)
	, m_name(name)
{
}

std::unique_ptr<Pokemon> G3Box::at(unsigned i) {
	if (i >= length()) {
		return nullptr;
	}
	G3BasePokemonData* data = &m_start[i];
	if (data->checksum == 0) {
		return nullptr;
	}
	return std::unique_ptr<Pokemon>(new G3BasePokemon(m_gen, data));
}

unsigned G3Box::length() const {
	return G3_POKEMON_PER_BOX;
}

unsigned G3Box::capacity() const {
	return G3_POKEMON_PER_BOX;
}

std::string G3Box::name() const {
	return m_name;
}

void G3Box::remove(unsigned i) {
	unsigned len = length();
	if (i >= len) {
		return;
	}
	G3BasePokemonData* pstart = &m_start[i];
	memset(pstart, 0, sizeof(G3BasePokemonData));
}

bool G3Box::insert(const Pokemon& pokemon) {
	size_t i;
	for (i = 0; i < capacity(); ++i) {
		G3BasePokemonData* data = &m_start[i];
		if (data->checksum == 0) {
			break;
		}
	}
	if (i == capacity()) {
		return false;
	}

	std::unique_ptr<G3BasePokemon> convertedPokemon = G3BasePokemon::copy(m_gen, pokemon);
	if (!convertedPokemon) {
		return false;
	}

	convertedPokemon->checksum();
	convertedPokemon->crypt();
	const G3BasePokemonData* data = reinterpret_cast<const G3BasePokemonData*>(convertedPokemon->data(nullptr));

	G3BasePokemonData* pstart = &m_start[i];
	memmove(pstart, data, sizeof(G3BasePokemonData));

	return true;
}
