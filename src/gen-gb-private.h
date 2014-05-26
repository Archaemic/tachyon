#ifndef PTXN_GEN_GB_PRIVATE_H
#define PTXN_GEN_GB_PRIVATE_H

#include "gen-gb.h"

#define R16(V) (((V) & 0xFF) << 8) | (((V) & 0xFF00) >> 8)
#define R24(V) (((V) & 0xFF) << 16) | ((V) & 0xFF00) | (((V) & 0xFF0000) >> 16)
#define R32(V) (((V) & 0xFF) << 24) | (((V) & 0xFF00) << 8) | (((V) & 0xFF0000) >> 8) | (((V) & 0xFF000000) >> 24)

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

struct GBMoveSet {
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
};

template <typename T>
class GBPokemon : public Pokemon {
public:
	GBPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot);

	virtual PokemonSpecies* species() const override;

	virtual uint16_t otId() const override;
	virtual unsigned xp() const override;
	virtual unsigned currentHp() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;

	virtual unsigned maxHp() const override;
	virtual unsigned attack() const override;
	virtual unsigned defense() const override;
	virtual unsigned speed() const override;
	virtual unsigned specialAttack() const override;
	virtual unsigned specialDefense() const override;

	virtual unsigned ivHp() const override;
	virtual unsigned ivAttack() const override;
	virtual unsigned ivDefense() const override;
	virtual unsigned ivSpeed() const override;
	virtual unsigned ivSpecialAttack() const override;
	virtual unsigned ivSpecialDefense() const override;

	virtual unsigned evHp() const override;
	virtual unsigned evAttack() const override;
	virtual unsigned evDefense() const override;
	virtual unsigned evSpeed() const override;
	virtual unsigned evSpecialAttack() const override;
	virtual unsigned evSpecialDefense() const override;

	virtual unsigned move1() const override;
	virtual unsigned move2() const override;
	virtual unsigned move3() const override;
	virtual unsigned move4() const override;

	unsigned stat(unsigned iv, unsigned base, unsigned ev) const;

private:
	GameBoyGame* m_gen;
	T* m_data;
};

template<typename T>
class GBPartyPokemon : public GBPokemon<T> {
public:
	GBPartyPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot);

	virtual unsigned level() const override;
	virtual unsigned maxHp() const override;
	virtual unsigned attack() const override;
	virtual unsigned defense() const override;
	virtual unsigned speed() const override;
	virtual unsigned specialAttack() const override;
	virtual unsigned specialDefense() const override;

private:
	T* m_data;
};

template <typename T>
GBPokemon<T>::GBPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot)
	: m_gen(gen)
	, m_data(reinterpret_cast<T*>(data))
{
	setName(GameBoyGame::gameTextToUTF8(name, 11));
	setOtName(GameBoyGame::gameTextToUTF8(ot, 8));
}

template <typename T>
PokemonSpecies* GBPokemon<T>::species() const {
	return m_gen->species(static_cast<PokemonSpecies::Id>(m_data->species));
}

template <typename T>
unsigned GBPokemon<T>::maxHp() const {
	PokemonSpecies* sp = species();
	return (ivHp() + sp->baseHp() + int(sqrt(evHp())) / 8 + 50) * level() / 50 + 10;
}

template <typename T>
unsigned GBPokemon<T>::attack() const {
	PokemonSpecies* sp = species();
	return stat(ivAttack(), sp->baseAttack(), evAttack());
}

template <typename T>
unsigned GBPokemon<T>::defense() const {
	PokemonSpecies* sp = species();
	return stat(ivDefense(), sp->baseDefense(), evDefense());
}

template <typename T>
unsigned GBPokemon<T>::speed() const {
	PokemonSpecies* sp = species();
	return stat(ivSpeed(), sp->baseSpeed(), evSpeed());
}

template <typename T>
unsigned GBPokemon<T>::specialAttack() const {
	PokemonSpecies* sp = species();
	return stat(ivSpecialAttack(), sp->baseSpecialAttack(), evSpecialAttack());
}

template <typename T>
unsigned GBPokemon<T>::specialDefense() const {
	PokemonSpecies* sp = species();
	return stat(ivSpecialDefense(), sp->baseSpecialDefense(), evSpecialDefense());
}

template <typename T>
unsigned GBPokemon<T>::stat(unsigned iv, unsigned base, unsigned ev) const {
	return (iv + base + int(sqrt(ev)) / 8) * level() / 50 + 5;
}

template <typename T>
uint16_t GBPokemon<T>::otId() const {
	return R16(m_data->otId);
}

template <typename T>
unsigned GBPokemon<T>::xp() const {
	return R24(m_data->xp);
}

template <typename T>
unsigned GBPokemon<T>::currentHp() const {
	return maxHp();
}

template <typename T>
Type GBPokemon<T>::type1() const {
	return species()->type1();
}

template <typename T>
Type GBPokemon<T>::type2() const {
	return species()->type2();
}

template <typename T>
unsigned GBPokemon<T>::ivHp() const {
	return
		((m_data->ivAttack & 1) << 3) |
		((m_data->ivDefense & 1) << 2) |
		((m_data->ivSpeed & 1) << 1) |
		(m_data->ivSpecial & 1);
}

template <typename T>
unsigned GBPokemon<T>::ivAttack() const {
	return m_data->ivAttack;
}

template <typename T>
unsigned GBPokemon<T>::ivDefense() const {
	return m_data->ivDefense;
}

template <typename T>
unsigned GBPokemon<T>::ivSpeed() const {
	return m_data->ivSpeed;
}

template <typename T>
unsigned GBPokemon<T>::ivSpecialAttack() const {
	return m_data->ivSpecial;
}

template <typename T>
unsigned GBPokemon<T>::ivSpecialDefense() const {
	return m_data->ivSpecial;
}

template <typename T>
unsigned GBPokemon<T>::evHp() const {
	return R16(m_data->evHp);
}

template <typename T>
unsigned GBPokemon<T>::evAttack() const {
	return R16(m_data->evAttack);
}

template <typename T>
unsigned GBPokemon<T>::evDefense() const {
	return R16(m_data->evDefense);
}

template <typename T>
unsigned GBPokemon<T>::evSpeed() const {
	return R16(m_data->evSpeed);
}

template <typename T>
unsigned GBPokemon<T>::evSpecialAttack() const {
	return R16(m_data->evSpecial);
}

template <typename T>
unsigned GBPokemon<T>::evSpecialDefense() const {
	return R16(m_data->evSpecial);
}

template <typename T>
unsigned GBPokemon<T>::move1() const {
	return m_data->moves.move1;
}

template <typename T>
unsigned GBPokemon<T>::move2() const {
	return m_data->moves.move2;
}

template <typename T>
unsigned GBPokemon<T>::move3() const {
	return m_data->moves.move3;
}

template <typename T>
unsigned GBPokemon<T>::move4() const {
	return m_data->moves.move4;
}

template <typename T>
GBPartyPokemon<T>::GBPartyPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot)
	: GBPokemon<T>(gen, data, name, ot)
	, m_data(reinterpret_cast<T*>(data))
{
}

template <typename T>
unsigned GBPartyPokemon<T>::level() const {
	return m_data->level;
}

template <typename T>
unsigned GBPartyPokemon<T>::maxHp() const {
	return R16(m_data->maxHp);
}

template <typename T>
unsigned GBPartyPokemon<T>::attack() const {
	return R16(m_data->attack);
}

template <typename T>
unsigned GBPartyPokemon<T>::defense() const {
	return R16(m_data->defense);
}

template <typename T>
unsigned GBPartyPokemon<T>::speed() const {
	return R16(m_data->speed);
}

template <typename T>
unsigned GBPartyPokemon<T>::specialAttack() const {
	return R16(m_data->specialAttack);
}

template <typename T>
unsigned GBPartyPokemon<T>::specialDefense() const {
	return R16(m_data->specialDefense);
}

#endif
