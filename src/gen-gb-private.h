#ifndef PTXN_GEN_GB_PRIVATE_H
#define PTXN_GEN_GB_PRIVATE_H

#include "gen-gb.h"

#include <cmath>
#include <cstring>

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
	typedef T DataType;

	static std::unique_ptr<GBPokemon<T>> copy(GameBoyGame* gen, const Pokemon&);

	GBPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot);
	GBPokemon(GameBoyGame* gen);

	virtual const GameBoyGame* game() const override;

	virtual PokemonSpecies* species() const override;

	virtual uint16_t otId() const override;
	virtual uint16_t otSecretId() const override;
	virtual bool shiny() const override;
	virtual Nature nature() const override;
	virtual unsigned xp() const override;
	virtual unsigned currentHp() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;
	virtual unsigned pokerusStrain() const override;
	virtual unsigned pokerusDays() const override;

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

	virtual const uint8_t* data(unsigned* size) const override;
	virtual bool copy(const Pokemon& other) override;

private:
	GBPokemon(const GBPokemon<T>& other);
	explicit GBPokemon(const Pokemon& other);

	virtual uint8_t genderDeterminer() const override;

	GameBoyGame* m_gen;

protected:
	std::unique_ptr<T> m_data;
};

template<typename T>
class GBPartyPokemon : public GBPokemon<T> {
public:
	static std::unique_ptr<GBPartyPokemon<T>> copy(GameBoyGame* gen, const Pokemon&);

	GBPartyPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot);
	GBPartyPokemon(GameBoyGame* gen);

	virtual unsigned level() const override;
	virtual unsigned maxHp() const override;
	virtual unsigned attack() const override;
	virtual unsigned defense() const override;
	virtual unsigned speed() const override;
	virtual unsigned specialAttack() const override;
	virtual unsigned specialDefense() const override;

	virtual bool copy(const Pokemon& other) override;

private:
	GBPartyPokemon(const GBPartyPokemon<T>& other);
	explicit GBPartyPokemon(const Pokemon& other);
};

template<typename T>
class GBGroup : public Group {
public:
	GBGroup(GameBoyGame* gen);

	virtual std::unique_ptr<Pokemon> at(unsigned i) override;
	virtual unsigned length() const override;

	virtual void remove(unsigned i) override;
	virtual bool insert(const Pokemon& pokemon) override;

protected:
	void setStart(uint8_t* start);

private:
	GameBoyGame* m_gen;
	uint8_t* m_start;
};

template <typename T>
GBPokemon<T>::GBPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot)
	: m_gen(gen)
	, m_data(new T(*reinterpret_cast<T*>(data)))
{
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
std::unique_ptr<GBPokemon<T>> GBPokemon<T>::copy(GameBoyGame* gen, const Pokemon& pokemon) {
	if (gen->generation() != T::GENERATION) {
		return nullptr;
	}

	std::unique_ptr<GBPokemon<T>> newPokemon(new GBPokemon<T>(gen));
	if (!newPokemon->copy(pokemon)) {
		return nullptr;
	}
	return newPokemon;
}

template <typename T>
const GameBoyGame* GBPokemon<T>::game() const {
	return m_gen;
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
unsigned GBPokemon<T>::pokerusStrain() const {
	return m_data->pokerus >> 4;
}

template <typename T>
unsigned GBPokemon<T>::pokerusDays() const {
	return m_data->pokerus & 0xF;
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
const uint8_t* GBPokemon<T>::data(unsigned* size) const {
	if (size) {
		*size = sizeof(T);
	}
	return reinterpret_cast<uint8_t*>(m_data.get());
}

template <typename T>
bool GBPokemon<T>::copy(const Pokemon& other) {
	if (other.game()->generation() != T::GENERATION) {
		return false;
	}

	unsigned size;
	const uint8_t* oldData = other.data(&size);
	memcpy(m_data.get(), oldData, std::min<unsigned>(size, sizeof(T)));
	m_data->level = other.level();
	return true;
}

template <typename T>
GBPartyPokemon<T>::GBPartyPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot)
	: GBPokemon<T>(gen, data, name, ot)
{
}

template <typename T>
GBPartyPokemon<T>::GBPartyPokemon(GameBoyGame* gen)
	: GBPokemon<T>(gen)
{
}

template <typename T>
std::unique_ptr<GBPartyPokemon<T>> GBPartyPokemon<T>::copy(GameBoyGame* gen, const Pokemon& pokemon) {
	if (gen->generation() != T::GENERATION) {
		return nullptr;
	}

	std::unique_ptr<GBPartyPokemon<T>> newPokemon(new GBPartyPokemon<T>(gen));
	if (!newPokemon->copy(pokemon)) {
		return nullptr;
	}
	return newPokemon;
}

template <typename T>
unsigned GBPartyPokemon<T>::level() const {
	return GBPokemon<T>::m_data->level;
}

template <typename T>
unsigned GBPartyPokemon<T>::maxHp() const {
	return R16(GBPokemon<T>::m_data->maxHp);
}

template <typename T>
unsigned GBPartyPokemon<T>::attack() const {
	return R16(GBPokemon<T>::m_data->attack);
}

template <typename T>
unsigned GBPartyPokemon<T>::defense() const {
	return R16(GBPokemon<T>::m_data->defense);
}

template <typename T>
unsigned GBPartyPokemon<T>::speed() const {
	return R16(GBPokemon<T>::m_data->speed);
}

template <typename T>
unsigned GBPartyPokemon<T>::specialAttack() const {
	return R16(GBPokemon<T>::m_data->specialAttack);
}

template <typename T>
unsigned GBPartyPokemon<T>::specialDefense() const {
	return R16(GBPokemon<T>::m_data->specialDefense);
}

template <typename T>
bool GBPartyPokemon<T>::copy(const Pokemon& other) {
	if (!GBPokemon<T>::copy(other)) {
		return false;
	}

	GBPokemon<T>::m_data->currentHp = R16(other.currentHp());
	GBPokemon<T>::m_data->level = GBPokemon<T>::level();
	GBPokemon<T>::m_data->maxHp = R16(GBPokemon<T>::maxHp());
	GBPokemon<T>::m_data->attack = R16(GBPokemon<T>::attack());
	GBPokemon<T>::m_data->defense = R16(GBPokemon<T>::defense());
	GBPokemon<T>::m_data->speed = R16(GBPokemon<T>::speed());
	GBPokemon<T>::m_data->specialAttack = R16(GBPokemon<T>::specialAttack());
	GBPokemon<T>::m_data->specialDefense = R16(GBPokemon<T>::specialDefense());
	return true;
}

template <typename T>
GBGroup<T>::GBGroup(GameBoyGame* gen)
	: m_gen(gen)
	, m_start(gen->ram())
{
}

template <typename T>
std::unique_ptr<Pokemon> GBGroup<T>::at(unsigned i) {
	if (i >= length()) {
		return nullptr;
	}
	uint8_t* pstart = &m_start[2 + capacity() + sizeof(typename T::DataType) * i];
	uint8_t* nstart = &m_start[2 + (sizeof(typename T::DataType) + 12) * capacity() + 11 * i];
	uint8_t* tstart = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + 11 * i];
	return std::unique_ptr<Pokemon>(new T(m_gen, pstart, nstart, tstart));
}

template <typename T>
unsigned GBGroup<T>::length() const {
	return m_start[0];
}

template <typename T>
bool GBGroup<T>::insert(const Pokemon& pokemon) {
	unsigned len = length();
	if (len >= capacity()) {
		return false;
	}

	std::unique_ptr<T> convertedPokemon = T::copy(m_gen, pokemon);
	if (!convertedPokemon) {
		return false;
	}

	const typename T::DataType* data = reinterpret_cast<const typename T::DataType*>(convertedPokemon->data(nullptr));

	++m_start[0];
	uint8_t* sstart = &m_start[1 + len];
	uint8_t* pstart = &m_start[2 + capacity() + sizeof(typename T::DataType) * len];
	uint8_t* nstart = &m_start[2 + (sizeof(typename T::DataType) + 12) * capacity() + 11 * len];
	uint8_t* tstart = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + 11 * len];
	*sstart = data->species;
	memmove(pstart, data, sizeof(typename T::DataType));
	m_gen->stringToGameText(nstart, 11, pokemon.name());
	m_gen->stringToGameText(tstart, 8, pokemon.otName());

	return true;
}

template <typename T>
void GBGroup<T>::remove(unsigned i) {
	unsigned len = length();
	if (i >= len) {
		return;
	}
	--m_start[0];
	uint8_t* sstart = &m_start[1 + i];
	uint8_t* snext = &m_start[1 + i + 1];
	uint8_t* send = &m_start[1 + m_start[0]];
	uint8_t* pstart = &m_start[2 + capacity() + sizeof(typename T::DataType) * i];
	uint8_t* pnext = &m_start[2 + capacity() + sizeof(typename T::DataType) * (i + 1)];
	uint8_t* pend = &m_start[2 + capacity() + sizeof(typename T::DataType) * m_start[0]];
	uint8_t* nstart = &m_start[2 + (sizeof(typename T::DataType) + 12) * capacity() + 11 * i];
	uint8_t* nnext = &m_start[2 + (sizeof(typename T::DataType) + 12) * capacity() + 11 * (i + 1)];
	uint8_t* nend = &m_start[2 + (sizeof(typename T::DataType) + 12) * capacity() + 11 * m_start[0]];
	uint8_t* tstart = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + 11 * i];
	uint8_t* tnext = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + 11 * (i + 1)];
	uint8_t* tend = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + 11 * m_start[0]];
	memmove(sstart, snext, len - i - 1);
	memset(send, 0xFF, capacity() - m_start[0]);
	memmove(pstart, pnext, sizeof(typename T::DataType) * (len - i - 1));
	memset(pend, 0, sizeof(typename T::DataType) * (capacity() - m_start[0]));
	memmove(nstart, nnext, 11 * (len - i - 1));
	memset(nend, 0, 11 * (capacity() - m_start[0]));
	memmove(tstart, tnext, 11 * (len - i - 1));
	memset(tend, 0, 11 * (capacity() - m_start[0]));
}

template <typename T>
void GBGroup<T>::setStart(uint8_t* start) {
	m_start = start;
}

#endif
