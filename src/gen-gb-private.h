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
	GBPokemon(GameBoyGame* gen);

	virtual PokemonSpecies* species() const override;

	virtual uint16_t otId() const override;
	virtual uint16_t otSecretId() const override;
	virtual bool shiny() const override;
	virtual Nature nature() const override;
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

	virtual void setOtId(uint16_t) override;
	virtual void setOtSecretId(uint16_t) override;

	virtual void setIvHp(unsigned) override;
	virtual void setIvAttack(unsigned) override;
	virtual void setIvDefense(unsigned) override;
	virtual void setIvSpeed(unsigned) override;
	virtual void setIvSpecialAttack(unsigned) override;
	virtual void setIvSpecialDefense(unsigned) override;

	unsigned stat(unsigned iv, unsigned base, unsigned ev) const;

private:
	virtual uint8_t genderDeterminer() const override;

	GameBoyGame* m_gen;
	std::unique_ptr<T> m_data;
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
	, m_data(new T)
{
	memcpy(m_data.get(), data, sizeof(T));
	setName(GameBoyGame::gameTextToUTF8(name, 11));
	setOtName(GameBoyGame::gameTextToUTF8(ot, 8));
}

template <typename T>
GBPokemon<T>::GBPokemon(GameBoyGame* gen)
	: m_gen(gen)
	, m_data(new T)
{
	memset(m_data.get(), 0, sizeof(T));
}

template <typename T>
PokemonSpecies* GBPokemon<T>::species() const {
	return m_gen->species(static_cast<PokemonSpecies::Id>(m_data->species));
}

template <typename T>
unsigned GBPokemon<T>::maxHp() const {
	PokemonSpecies* sp = species();
	return (sp->baseHp() * 2 + ivHp() + int(ceil(sqrt(evHp()))) / 4 + 100) * level() / 100 + 10;
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
	return (base * 2 + iv + int(ceil(sqrt(ev))) / 4) * level() / 100 + 5;
}

template <typename T>
uint16_t GBPokemon<T>::otId() const {
	return R16(m_data->otId);
}

template <typename T>
uint16_t GBPokemon<T>::otSecretId() const {
	return 0;
}

template <typename T>
bool GBPokemon<T>::shiny() const {
	if (m_data->ivDefense != 10) {
		return false;
	}
	if (m_data->ivSpeed != 10) {
		return false;
	}
	if (m_data->ivSpecial != 10) {
		return false;
	}
	return m_data->ivAttack == 2 ||
		m_data->ivAttack == 3 ||
		m_data->ivAttack == 6 ||
		m_data->ivAttack == 7 ||
		m_data->ivAttack == 10 ||
		m_data->ivAttack == 11 ||
		m_data->ivAttack == 14 ||
		m_data->ivAttack == 15;
}

template <typename T>
Pokemon::Nature GBPokemon<T>::nature() const {
	return NO_NATURE;
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
		(((m_data->ivAttack & 1) << 3) |
		((m_data->ivDefense & 1) << 2) |
		((m_data->ivSpeed & 1) << 1) |
		(m_data->ivSpecial & 1)) * 2;
}

template <typename T>
unsigned GBPokemon<T>::ivAttack() const {
	return m_data->ivAttack * 2;
}

template <typename T>
unsigned GBPokemon<T>::ivDefense() const {
	return m_data->ivDefense * 2;
}

template <typename T>
unsigned GBPokemon<T>::ivSpeed() const {
	return m_data->ivSpeed * 2;
}

template <typename T>
unsigned GBPokemon<T>::ivSpecialAttack() const {
	return m_data->ivSpecial * 2;
}

template <typename T>
unsigned GBPokemon<T>::ivSpecialDefense() const {
	return m_data->ivSpecial * 2;
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
void GBPokemon<T>::setOtId(uint16_t id) {
	m_data->otId = id;
}

template <typename T>
void GBPokemon<T>::setOtSecretId(uint16_t) {
}

template <typename T>
void GBPokemon<T>::setIvHp(unsigned iv) {
	iv >>= 1;
	m_data->ivAttack &= ~1;
	m_data->ivDefense &= ~1;
	m_data->ivSpeed &= ~1;
	m_data->ivSpecial &= ~1;
	m_data->ivAttack |= (iv >> 3) & 1;
	m_data->ivDefense |= (iv >> 2) & 1;
	m_data->ivSpeed |= (iv >> 1) & 1;
	m_data->ivSpecial |= iv & 1;
}

template <typename T>
void GBPokemon<T>::setIvAttack(unsigned iv) {
	m_data->ivAttack = iv >> 1;
}

template <typename T>
void GBPokemon<T>::setIvDefense(unsigned iv) {
	m_data->ivDefense = iv >> 1;
}

template <typename T>
void GBPokemon<T>::setIvSpeed(unsigned iv) {
	m_data->ivSpeed = iv >> 1;
}

template <typename T>
void GBPokemon<T>::setIvSpecialAttack(unsigned iv) {
	m_data->ivSpecial = iv >> 1;
}

template <typename T>
void GBPokemon<T>::setIvSpecialDefense(unsigned iv) {
	m_data->ivSpecial = iv >> 1;
}

template <typename T>
uint8_t GBPokemon<T>::genderDeterminer() const {
	return m_data->ivAttack << 4;
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
