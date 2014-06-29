#include "gen3/G3PartyPokemon.h"

G3PartyPokemon::G3PartyPokemon(Generation3* gen, G3PartyPokemonData* data)
	: G3Pokemon<G3PartyPokemonData>(gen, data)
{
}

G3PartyPokemon::G3PartyPokemon(Generation3* gen)
	: G3Pokemon<G3PartyPokemonData>(gen)
{
}

std::unique_ptr<G3PartyPokemon> G3PartyPokemon::copy(Generation3* gen, const Pokemon& pokemon) {
	if (gen->generation() != 3) {
		return nullptr;
	}

	std::unique_ptr<G3PartyPokemon> newPokemon(new G3PartyPokemon(gen));
	if (!newPokemon->copy(pokemon)) {
		return nullptr;
	}
	return newPokemon;
}

unsigned G3PartyPokemon::level() const {
	return m_data->level;
}

unsigned G3PartyPokemon::currentHp() const {
	return m_data->currentHp;
}

unsigned G3PartyPokemon::maxHp() const {
	return m_data->maxHp;
}

unsigned G3PartyPokemon::attack() const {
	return m_data->attack;
}

unsigned G3PartyPokemon::defense() const {
	return m_data->defense;
}

unsigned G3PartyPokemon::speed() const {
	return m_data->speed;
}

unsigned G3PartyPokemon::specialAttack() const {
	return m_data->specialAttack;
}

unsigned G3PartyPokemon::specialDefense() const {
	return m_data->specialDefense;
}

unsigned G3PartyPokemon::pokerusDays() const {
	return m_data->pokerus & 0xF;
}

bool G3PartyPokemon::copy(const Pokemon& other) {
	if (!G3Pokemon<G3PartyPokemonData>::copy(other)) {
		return false;
	}

	G3Pokemon<G3PartyPokemonData>::m_data->currentHp = other.currentHp();
	recalculateStats();
	return true;
}

void G3PartyPokemon::recalculateStats() {
	G3Pokemon<G3PartyPokemonData>::m_data->level = G3Pokemon<G3PartyPokemonData>::level();
	G3Pokemon<G3PartyPokemonData>::m_data->maxHp = G3Pokemon<G3PartyPokemonData>::maxHp();
	G3Pokemon<G3PartyPokemonData>::m_data->attack = G3Pokemon<G3PartyPokemonData>::attack();
	G3Pokemon<G3PartyPokemonData>::m_data->defense = G3Pokemon<G3PartyPokemonData>::defense();
	G3Pokemon<G3PartyPokemonData>::m_data->speed = G3Pokemon<G3PartyPokemonData>::speed();
	G3Pokemon<G3PartyPokemonData>::m_data->specialAttack = G3Pokemon<G3PartyPokemonData>::specialAttack();
	G3Pokemon<G3PartyPokemonData>::m_data->specialDefense = G3Pokemon<G3PartyPokemonData>::specialDefense();
	G3Pokemon<G3PartyPokemonData>::m_data->pokerus = G3Pokemon<G3PartyPokemonData>::pokerusDays();
}
