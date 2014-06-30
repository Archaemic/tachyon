#ifndef PTXN_G3_BASE_POKEMON_H
#define PTXN_G3_BASE_POKEMON_H

#include "common/Pokemon.h"
#include "gen3/Generation3.h"
#include "gen3/G3PokemonSpecies.h"

struct G3PokemonGrowth {
	uint16_t species;
	uint16_t heldItem;
	uint32_t xp;
	uint8_t pp;
	uint8_t friendship;
	uint16_t unknown;
} __attribute__((packed));

struct G3PokemonAttacks {
	uint16_t moves[4];
	uint8_t pp[4];
} __attribute__((packed));

struct G3PokemonEVs {
	uint8_t hp;
	uint8_t attack;
	uint8_t defense;
	uint8_t speed;
	uint8_t specialAttack;
	uint8_t specialDefense;
	uint8_t coolness;
	uint8_t beauty;
	uint8_t cuteness;
	uint8_t smartness;
	uint8_t toughness;
	uint8_t feel;
} __attribute__((packed));

struct G3PokemonMisc {
	uint8_t pokerus;
	uint8_t met;
	uint16_t origin;
	uint32_t ivHp : 5;
	uint32_t ivAttack : 5;
	uint32_t ivDefense : 5;
	uint32_t ivSpeed : 5;
	uint32_t ivSpecialAttack : 5;
	uint32_t ivSpecialDefense : 5;
	uint32_t egg : 1;
	uint32_t ability : 1;
	uint32_t cool : 3;
	uint32_t beauty : 3;
	uint32_t cute : 3;
	uint32_t smart : 3;
	uint32_t tough : 3;
	uint32_t champion : 1;
	uint32_t winning : 1;
	uint32_t victory : 1;
	uint32_t artist : 1;
	uint32_t effort : 1;
	uint32_t special1 : 1;
	uint32_t special2 : 1;
	uint32_t special3 : 1;
	uint32_t special4 : 1;
	uint32_t special5 : 1;
	uint32_t special6 : 1;
	uint32_t padding : 4;
	uint32_t obedience : 1;
} __attribute__((packed));

union G3PokemonField {
	G3PokemonGrowth g;
	G3PokemonAttacks a;
	G3PokemonEVs e;
	G3PokemonMisc m;
	uint32_t raw[3];
} __attribute__((packed));

struct G3PokemonSubdata {
	G3PokemonField f0;
	G3PokemonField f1;
	G3PokemonField f2;
	G3PokemonField f3;
} __attribute__((packed));

struct G3BasePokemonData {
	uint32_t personality;
	uint32_t otId;
	uint8_t name[10];
	uint16_t language;
	uint8_t otName[7];
	uint8_t markings;
	uint16_t checksum;
	uint16_t padding;
	G3PokemonSubdata data;

	G3PokemonGrowth* growth();
	G3PokemonAttacks* attacks();
	G3PokemonEVs* evs();
	G3PokemonMisc* misc();
} __attribute__((packed));

template <typename T>
class G3Pokemon : public Pokemon {
public:
	static std::unique_ptr<G3Pokemon<T>> copy(Generation3* gen, const Pokemon&);

	G3Pokemon(Generation3* gen, T* data);
	G3Pokemon(Generation3* gen);

	virtual const Generation3* game() const override;

	virtual const PokemonSpecies* species() const override;

	virtual uint16_t otId() const override;
	virtual uint16_t otSecretId() const override;
	virtual bool shiny() const override;
	virtual Nature nature() const override;
	virtual unsigned xp() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;
	virtual unsigned pokerusStrain() const override;
	virtual unsigned pokerusDays() const override;

	virtual unsigned currentHp() const override;
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

	virtual const uint8_t* data(unsigned* size) const override;
	virtual bool copy(const Pokemon& other) override;
	virtual std::unique_ptr<Pokemon> clone();
	void crypt();
	void checksum();

protected:
	Generation3* game();

private:
	virtual uint8_t genderDeterminer() const override;
	unsigned stat(unsigned iv, unsigned base, unsigned ev, int nature) const;

	Generation3* m_gen;

protected:
	std::unique_ptr<T> m_data;
};

typedef G3Pokemon<G3BasePokemonData> G3BasePokemon;

template <typename T>
G3Pokemon<T>::G3Pokemon(Generation3* gen, T* data)
	: m_gen(gen)
	, m_data(new T(*data))
{
	crypt();
	setName(gen->gameTextToUTF8(m_data->name, 10));
	setOtName(gen->gameTextToUTF8(m_data->otName, 7));
}

template <typename T>
G3Pokemon<T>::G3Pokemon(Generation3* gen)
	: m_gen(gen)
	, m_data(new T)
{
}

template <typename T>
std::unique_ptr<G3Pokemon<T>> G3Pokemon<T>::copy(Generation3* gen, const Pokemon& pokemon) {
	if (gen->generation() != 3) {
		return nullptr;
	}

	std::unique_ptr<G3Pokemon<T>> newPokemon(new G3Pokemon<T>(gen));
	if (!newPokemon->copy(pokemon)) {
		return nullptr;
	}
	return newPokemon;
}

template <typename T>
const Generation3* G3Pokemon<T>::game() const {
	return m_gen;
}

template <typename T>
Generation3* G3Pokemon<T>::game() {
	return m_gen;
}

template <typename T>
const PokemonSpecies* G3Pokemon<T>::species() const {
	unsigned unmappedId = m_data->growth()->species;
	if (unmappedId < sizeof(G3PokemonSpecies::idMapping) / sizeof(*G3PokemonSpecies::idMapping)) {
		PokemonSpecies::Id id = G3PokemonSpecies::idMapping[unmappedId];
		PokemonSpecies::Forme forme = PokemonSpecies::FORME_NORMAL;
		if (id == PokemonSpecies::UNOWN) {
			uint32_t letter = m_data->personality;
			letter = (letter & 0x3) | ((letter >> 6) & 0xC) | ((letter >> 12) & 0x30) | ((letter >> 18) & 0xC0);
			letter %= 28;
			forme = static_cast<PokemonSpecies::Forme>(letter);
		}
		return m_gen->species(id, forme);
	}
	return m_gen->species(PokemonSpecies::MISSINGNO);
}

template <typename T>
uint16_t G3Pokemon<T>::otId() const {
	return m_data->otId & 0xFFFF;
}

template <typename T>
uint16_t G3Pokemon<T>::otSecretId() const {
	return m_data->otId >> 16;
}

template <typename T>
bool G3Pokemon<T>::shiny() const {
	return (otId() ^ otSecretId() ^ (m_data->personality >> 16) ^ (m_data->personality & 0xFFFF)) < 8;
}

template <typename T>
Pokemon::Nature G3Pokemon<T>::nature() const {
	return static_cast<Nature>(m_data->personality % 25);
}

template <typename T>
unsigned G3Pokemon<T>::xp() const {
	return m_data->growth()->xp;
}

template <typename T>
Type G3Pokemon<T>::type1() const {
	return species()->type1();
}

template <typename T>
unsigned G3Pokemon<T>::pokerusStrain() const {
	return m_data->misc()->pokerus >> 4;
}

template <typename T>
unsigned G3Pokemon<T>::pokerusDays() const {
	return m_data->misc()->pokerus & 0xF;
}

template <typename T>
Type G3Pokemon<T>::type2() const {
	return species()->type2();
}

template <typename T>
unsigned G3Pokemon<T>::currentHp() const {
	return maxHp();
}

template <typename T>
unsigned G3Pokemon<T>::maxHp() const {
	return ((ivHp() + species()->baseHp() * 2 + evHp() / 4 + 100) * level()) / 100 + 10;
}

template <typename T>
unsigned G3Pokemon<T>::attack() const {
	switch (nature()) {
	case LONELY:
	case BRAVE:
	case ADAMANT:
	case NAUGHTY:
		return stat(ivAttack(), species()->baseAttack(), evAttack(), 1);
	case BOLD:
	case TIMID:
	case MODEST:
	case CALM:
		return stat(ivAttack(), species()->baseAttack(), evAttack(), -1);
	default:
		return stat(ivAttack(), species()->baseAttack(), evAttack(), 0);
	}
}

template <typename T>
unsigned G3Pokemon<T>::defense() const {
	switch (nature()) {
	case BOLD:
	case RELAXED:
	case IMPISH:
	case LAX:
		return stat(ivDefense(), species()->baseDefense(), evDefense(), 1);
	case LONELY:
	case HASTY:
	case MILD:
	case GENTLE:
		return stat(ivDefense(), species()->baseDefense(), evDefense(), -1);
	default:
		return stat(ivDefense(), species()->baseDefense(), evDefense(), 0);
	}
}

template <typename T>
unsigned G3Pokemon<T>::speed() const {
	switch (nature()) {
	case TIMID:
	case HASTY:
	case JOLLY:
	case NAIVE:
		return stat(ivSpeed(), species()->baseSpeed(), evSpeed(), 1);
	case BRAVE:
	case RELAXED:
	case QUIET:
	case SASSY:
		return stat(ivSpeed(), species()->baseSpeed(), evSpeed(), -1);
	default:
		return stat(ivSpeed(), species()->baseSpeed(), evSpeed(), 0);
	}
}

template <typename T>
unsigned G3Pokemon<T>::specialAttack() const {
	switch (nature()) {
	case MODEST:
	case MILD:
	case QUIET:
	case RASH:
		return stat(ivSpecialAttack(), species()->baseSpecialAttack(), evSpecialAttack(), 1);
	case ADAMANT:
	case IMPISH:
	case JOLLY:
	case CAREFUL:
		return stat(ivSpecialAttack(), species()->baseSpecialAttack(), evSpecialAttack(), -1);
	default:
		return stat(ivSpecialAttack(), species()->baseSpecialAttack(), evSpecialAttack(), 0);
	}
}

template <typename T>
unsigned G3Pokemon<T>::specialDefense() const {
	switch (nature()) {
	case CALM:
	case GENTLE:
	case SASSY:
	case CAREFUL:
		return stat(ivSpecialDefense(), species()->baseSpecialDefense(), evSpecialDefense(), 1);
	case NAUGHTY:
	case LAX:
	case NAIVE:
	case RASH:
		return stat(ivSpecialDefense(), species()->baseSpecialDefense(), evSpecialDefense(), -1);
	default:
		return stat(ivSpecialDefense(), species()->baseSpecialDefense(), evSpecialDefense(), 0);
	}
}

template <typename T>
unsigned G3Pokemon<T>::ivHp() const {
	return m_data->misc()->ivHp;
}

template <typename T>
unsigned G3Pokemon<T>::ivAttack() const {
	return m_data->misc()->ivAttack;
}

template <typename T>
unsigned G3Pokemon<T>::ivDefense() const {
	return m_data->misc()->ivDefense;
}

template <typename T>
unsigned G3Pokemon<T>::ivSpeed() const {
	return m_data->misc()->ivSpeed;
}

template <typename T>
unsigned G3Pokemon<T>::ivSpecialAttack() const {
	return m_data->misc()->ivSpecialAttack;
}

template <typename T>
unsigned G3Pokemon<T>::ivSpecialDefense() const {
	return m_data->misc()->ivSpecialDefense;
}

template <typename T>
unsigned G3Pokemon<T>::evHp() const {
	return m_data->evs()->hp;
}

template <typename T>
unsigned G3Pokemon<T>::evAttack() const {
	return m_data->evs()->attack;
}

template <typename T>
unsigned G3Pokemon<T>::evDefense() const {
	return m_data->evs()->defense;
}

template <typename T>
unsigned G3Pokemon<T>::evSpeed() const {
	return m_data->evs()->speed;
}

template <typename T>
unsigned G3Pokemon<T>::evSpecialAttack() const {
	return m_data->evs()->specialAttack;
}

template <typename T>
unsigned G3Pokemon<T>::evSpecialDefense() const {
	return m_data->evs()->specialDefense;
}

template <typename T>
unsigned G3Pokemon<T>::move1() const {
	return m_data->attacks()->moves[0];
}

template <typename T>
unsigned G3Pokemon<T>::move2() const {
	return m_data->attacks()->moves[1];
}

template <typename T>
unsigned G3Pokemon<T>::move3() const {
	return m_data->attacks()->moves[2];
}

template <typename T>
unsigned G3Pokemon<T>::move4() const {
	return m_data->attacks()->moves[3];
}

template <typename T>
void G3Pokemon<T>::setOtId(uint16_t id) {
	m_data->otId &= ~0xFFFF;
	m_data->otId |= id;
}

template <typename T>
void G3Pokemon<T>::setOtSecretId(uint16_t id) {
	m_data->otId &= ~0xFFFF0000;
	m_data->otId |= id << 16;
}

template <typename T>
void G3Pokemon<T>::setXp(unsigned xp) {
	m_data->growth()->xp = xp;
}

template <typename T>
void G3Pokemon<T>::setIvHp(unsigned iv) {
	m_data->misc()->ivHp = iv;
}

template <typename T>
void G3Pokemon<T>::setIvAttack(unsigned iv) {
	m_data->misc()->ivAttack = iv;
}

template <typename T>
void G3Pokemon<T>::setIvDefense(unsigned iv) {
	m_data->misc()->ivDefense = iv;
}

template <typename T>
void G3Pokemon<T>::setIvSpeed(unsigned iv) {
	m_data->misc()->ivSpeed = iv;
}

template <typename T>
void G3Pokemon<T>::setIvSpecialAttack(unsigned iv) {
	m_data->misc()->ivSpecialAttack = iv;
}

template <typename T>
void G3Pokemon<T>::setIvSpecialDefense(unsigned iv) {
	m_data->misc()->ivSpecialDefense = iv;
}

template <typename T>
void G3Pokemon<T>::setEvHp(unsigned ev) {
	m_data->evs()->hp = ev;
}

template <typename T>
void G3Pokemon<T>::setEvAttack(unsigned ev) {
	m_data->evs()->attack = ev;
}

template <typename T>
void G3Pokemon<T>::setEvDefense(unsigned ev) {
	m_data->evs()->defense = ev;
}

template <typename T>
void G3Pokemon<T>::setEvSpeed(unsigned ev) {
	m_data->evs()->speed = ev;
}

template <typename T>
void G3Pokemon<T>::setEvSpecialAttack(unsigned ev) {
	m_data->evs()->specialAttack = ev;
}

template <typename T>
void G3Pokemon<T>::setEvSpecialDefense(unsigned ev) {
	m_data->evs()->specialDefense = ev;
}

template <typename T>
unsigned G3Pokemon<T>::stat(unsigned iv, unsigned base, unsigned ev, int nature) const {
	return (((iv + base * 2 + ev / 4) * level()) / 100 + 5) * (1.f + (nature / 10.f));
}

template <typename T>
void G3Pokemon<T>::crypt() {
	uint32_t key = m_data->otId ^ m_data->personality;
	for (int i = 0; i < 3; ++i) {
		m_data->data.f0.raw[i] ^= key;
		m_data->data.f1.raw[i] ^= key;
		m_data->data.f2.raw[i] ^= key;
		m_data->data.f3.raw[i] ^= key;
	}
}

template <typename T>
void G3Pokemon<T>::checksum() {
	uint16_t sum = 0;
	for (int i = 0; i < 3; ++i) {
		sum += m_data->data.f0.raw[i];
		sum += m_data->data.f0.raw[i] >> 16;
		sum += m_data->data.f1.raw[i];
		sum += m_data->data.f1.raw[i] >> 16;
		sum += m_data->data.f2.raw[i];
		sum += m_data->data.f2.raw[i] >> 16;
		sum += m_data->data.f3.raw[i];
		sum += m_data->data.f3.raw[i] >> 16;
	}
	m_data->checksum = sum;
}

template <typename T>
uint8_t G3Pokemon<T>::genderDeterminer() const {
	return m_data->personality & 0xFF;
}

template <typename T>
const uint8_t* G3Pokemon<T>::data(unsigned* size) const {
	if (size) {
		*size = sizeof(G3BasePokemonData);
	}
	return reinterpret_cast<uint8_t*>(m_data.get());
}

template <typename T>
std::unique_ptr<Pokemon> G3Pokemon<T>::clone() {
	Pokemon* pokemon = new G3Pokemon<T>(m_gen);
	pokemon->copy(*this);
	return std::unique_ptr<Pokemon>(pokemon);
}

template <typename T>
bool G3Pokemon<T>::copy(const Pokemon& other) {
	if ((other.game()->version() & Game::MASK_GENERATION) != 0x300) {
		return false;
	}

	unsigned size;
	const uint8_t* oldData = other.data(&size);
	memcpy(m_data.get(), oldData, std::min<unsigned>(size, sizeof(T)));
	return true;
}

#endif
