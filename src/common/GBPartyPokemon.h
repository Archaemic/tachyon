#ifndef PTXN_GB_PARTY_POKEMON_H
#define PTXN_GB_PARTY_POKEMON_H

#include "common/GBPokemon.h"

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

#endif
