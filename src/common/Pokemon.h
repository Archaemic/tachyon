#ifndef PTXN_POKEMON_H
#define PTXN_POKEMON_H

#include <cstdint>
#include <string>

#include "common/Type.h"

class Game;
class PokemonSpecies;

class Pokemon {
public:
	enum Gender {
		GENDERLESS = 0,
		MALE,
		FEMALE
	};

	enum Nature {
		NO_NATURE = -1,
		HARDY = 0,
		LONELY,
		BRAVE,
		ADAMANT,
		NAUGHTY,
		BOLD,
		DOCILE,
		RELAXED,
		IMPISH,
		LAX,
		TIMID,
		HASTY,
		SERIOUS,
		JOLLY,
		NAIVE,
		MODEST,
		MILD,
		QUIET,
		BASHFUL,
		RASH,
		CALM,
		GENTLE,
		SASSY,
		CAREFUL,
		QUIRKY,
		NATURE_MAX
	};

	virtual ~Pokemon() {}

	virtual const Game* game() const = 0;

	const std::string& name() const;
	virtual const PokemonSpecies* species() const = 0;
	const std::string& otName() const;
	virtual uint16_t otId() const = 0;
	virtual uint16_t otSecretId() const = 0;
	virtual Gender gender() const;
	virtual bool shiny() const = 0;
	virtual Nature nature() const = 0;
	virtual unsigned xp() const = 0;
	virtual unsigned currentHp() const = 0;
	virtual Type type1() const = 0;
	virtual Type type2() const = 0;
	virtual unsigned pokerusStrain() const = 0;
	virtual unsigned pokerusDays() const = 0;

	virtual unsigned level() const;
	virtual unsigned maxHp() const = 0;
	virtual unsigned attack() const = 0;
	virtual unsigned defense() const = 0;
	virtual unsigned speed() const = 0;
	virtual unsigned specialAttack() const = 0;
	virtual unsigned specialDefense() const = 0;

	virtual unsigned ivHp() const = 0;
	virtual unsigned ivAttack() const = 0;
	virtual unsigned ivDefense() const = 0;
	virtual unsigned ivSpeed() const = 0;
	virtual unsigned ivSpecialAttack() const = 0;
	virtual unsigned ivSpecialDefense() const = 0;

	virtual unsigned evHp() const = 0;
	virtual unsigned evAttack() const = 0;
	virtual unsigned evDefense() const = 0;
	virtual unsigned evSpeed() const = 0;
	virtual unsigned evSpecialAttack() const = 0;
	virtual unsigned evSpecialDefense() const = 0;

	virtual unsigned move1() const = 0;
	virtual unsigned move2() const = 0;
	virtual unsigned move3() const = 0;
	virtual unsigned move4() const = 0;

	static const char* natureReadable(Nature nature);
	const char* natureReadable() const;

	void setName(const std::string& name);
	void setOtName(const std::string& otName);
	virtual void setOtId(uint16_t) = 0;
	virtual void setOtSecretId(uint16_t) = 0;

	virtual void setXp(unsigned) = 0;

	virtual void setIvHp(unsigned) = 0;
	virtual void setIvAttack(unsigned) = 0;
	virtual void setIvDefense(unsigned) = 0;
	virtual void setIvSpeed(unsigned) = 0;
	virtual void setIvSpecialAttack(unsigned) = 0;
	virtual void setIvSpecialDefense(unsigned) = 0;

	virtual void setEvHp(unsigned) = 0;
	virtual void setEvAttack(unsigned) = 0;
	virtual void setEvDefense(unsigned) = 0;
	virtual void setEvSpeed(unsigned) = 0;
	virtual void setEvSpecialAttack(unsigned) = 0;
	virtual void setEvSpecialDefense(unsigned) = 0;

	virtual const uint8_t* data(unsigned* size) const = 0;
	virtual bool copy(const Pokemon& other) = 0;
	virtual std::unique_ptr<Pokemon> clone() = 0;
	virtual void recalculateStats() { };

protected:
	virtual uint8_t genderDeterminer() const = 0;

private:
	std::string m_name;
	std::string m_otName;
};

#endif
