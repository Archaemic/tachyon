#ifndef PTXN_GB_POKEMON_H
#define PTXN_GB_POKEMON_H

#include "common/Pokemon.h"
#include "gb/GameBoyGame.h"

template <typename T>
class GBPokemon : public Pokemon {
public:
	typedef T DataType;

	static std::unique_ptr<GBPokemon<T>> copy(GameBoyGame* gen, const Pokemon&);

	GBPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot);
	GBPokemon(GameBoyGame* gen);

	virtual const GameBoyGame* game() const override;

	virtual const PokemonSpecies* species() const override;

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

	virtual void setXp(unsigned) override;

	virtual void setIvHp(unsigned) override;
	virtual void setIvAttack(unsigned) override;
	virtual void setIvDefense(unsigned) override;
	virtual void setIvSpeed(unsigned) override;
	virtual void setIvSpecialAttack(unsigned) override;
	virtual void setIvSpecialDefense(unsigned) override;

	virtual void setEvHp(unsigned) override;
	virtual void setEvAttack(unsigned) override;
	virtual void setEvDefense(unsigned) override;
	virtual void setEvSpeed(unsigned) override;
	virtual void setEvSpecialAttack(unsigned) override;
	virtual void setEvSpecialDefense(unsigned) override;

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

template <typename T>
GBPokemon<T>::GBPokemon(GameBoyGame* gen, uint8_t* data, const uint8_t* name, const uint8_t* ot)
	: m_gen(gen)
	, m_data(new T(*reinterpret_cast<T*>(data)))
{
	setName(gen->gameTextToUTF8(name, 11));
	setOtName(gen->gameTextToUTF8(ot, 8));
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
	if ((gen->version() & Game::MASK_GENERATION) != T::GENERATION) {
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
const PokemonSpecies* GBPokemon<T>::species() const {
	PokemonSpecies::Id id = static_cast<PokemonSpecies::Id>(m_data->species);
	PokemonSpecies::Forme forme = PokemonSpecies::FORME_NORMAL;
	if (id == PokemonSpecies::UNOWN) {
		forme = static_cast<PokemonSpecies::Forme>(
			(((m_data->ivAttack & 0x6) << 5) |
			((m_data->ivDefense & 0x6) << 3) |
			((m_data->ivSpeed & 0x6) << 1) |
			((m_data->ivSpecial & 0x6) >> 1)) / 10);
	}
	return m_gen->species(id, forme);
}

template <typename T>
unsigned GBPokemon<T>::maxHp() const {
	const PokemonSpecies* sp = species();
	return (sp->baseHp() * 2 + ivHp() + int(ceil(sqrt(evHp()))) / 4 + 100) * level() / 100 + 10;
}

template <typename T>
unsigned GBPokemon<T>::attack() const {
	const PokemonSpecies* sp = species();
	return stat(ivAttack(), sp->baseAttack(), evAttack());
}

template <typename T>
unsigned GBPokemon<T>::defense() const {
	const PokemonSpecies* sp = species();
	return stat(ivDefense(), sp->baseDefense(), evDefense());
}

template <typename T>
unsigned GBPokemon<T>::speed() const {
	const PokemonSpecies* sp = species();
	return stat(ivSpeed(), sp->baseSpeed(), evSpeed());
}

template <typename T>
unsigned GBPokemon<T>::specialAttack() const {
	const PokemonSpecies* sp = species();
	return stat(ivSpecialAttack(), sp->baseSpecialAttack(), evSpecialAttack());
}

template <typename T>
unsigned GBPokemon<T>::specialDefense() const {
	const PokemonSpecies* sp = species();
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
void GBPokemon<T>::setXp(unsigned xp) {
	m_data->xp = R24(xp);
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
void GBPokemon<T>::setEvHp(unsigned ev) {
	m_data->evHp = R16(ev);
}

template <typename T>
void GBPokemon<T>::setEvAttack(unsigned ev) {
	m_data->evAttack = R16(ev);
}

template <typename T>
void GBPokemon<T>::setEvDefense(unsigned ev) {
	m_data->evDefense = R16(ev);
}

template <typename T>
void GBPokemon<T>::setEvSpeed(unsigned ev) {
	m_data->evSpeed = R16(ev);
}

template <typename T>
void GBPokemon<T>::setEvSpecialAttack(unsigned ev) {
	m_data->evSpecial = R16(ev);
}

template <typename T>
void GBPokemon<T>::setEvSpecialDefense(unsigned ev) {
	m_data->evSpecial = R16(ev);
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
	if ((other.game()->version() & Game::MASK_GENERATION) != T::GENERATION) {
		return false;
	}

	unsigned size;
	const uint8_t* oldData = other.data(&size);
	memcpy(m_data.get(), oldData, std::min<unsigned>(size, sizeof(T)));
	m_data->level = other.level();
	return true;
}

#endif
