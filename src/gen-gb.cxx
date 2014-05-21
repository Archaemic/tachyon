#include "gen-gb-private.h"

#include <cmath>

unsigned GBPokemon::maxHp() const {
	PokemonSpecies sp = species();
	return (ivHp() + sp.baseHp() + int(sqrt(evHp())) / 8 + 50) * level() / 50 + 10;
}

unsigned GBPokemon::attack() const {
	PokemonSpecies sp = species();
	return stat(ivAttack(), sp.baseAttack(), evAttack());
}

unsigned GBPokemon::defense() const {
	PokemonSpecies sp = species();
	return stat(ivDefense(), sp.baseDefense(), evDefense());
}

unsigned GBPokemon::speed() const {
	PokemonSpecies sp = species();
	return stat(ivSpeed(), sp.baseSpeed(), evSpeed());
}

unsigned GBPokemon::specialAttack() const {
	PokemonSpecies sp = species();
	return stat(ivSpecialAttack(), sp.baseSpecialAttack(), evSpecialAttack());
}

unsigned GBPokemon::specialDefense() const {
	PokemonSpecies sp = species();
	return stat(ivSpecialDefense(), sp.baseSpecialDefense(), evSpecialDefense());
}

unsigned GBPokemon::stat(unsigned iv, unsigned base, unsigned ev) const {
	return (iv + base + int(sqrt(ev)) / 8) * level() / 50 + 5;
}
