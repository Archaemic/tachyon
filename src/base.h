#ifndef PTXN_BASE_H
#define PTXN_BASE_H

#include <cwchar>
#include <cstdint>

enum Type {
	NORMAL = 0x10,
	FIGHTING,
	FLYING,
	POISON,
	GROUND,
	ROCK,
	BUG,
	GHOST,
	STEEL,

	FIRE = 0x20,
	WATER,
	GRASS,
	ELECTRIC,
	PSYCHIC,
	ICE,
	DRAGON,
	DARK,

	QQQ = 0
};

const wchar_t* TypeReadable(Type type);

class PokemonImpl {
public:
	PokemonImpl();
	virtual ~PokemonImpl() {}

	void ref();
	void deref();

	virtual const wchar_t* name() const = 0;
	virtual const wchar_t* otName() const = 0;
	virtual uint16_t otId() const = 0;
	virtual unsigned xp() const = 0;
	virtual unsigned currentHp() const = 0;
	virtual Type type1() const = 0;
	virtual Type type2() const = 0;

private:
	wchar_t m_name[11];
	wchar_t m_otName[8];
	int m_refs;
};

class Pokemon {
public:
	Pokemon(PokemonImpl* impl);
	Pokemon(const Pokemon& other);
	~Pokemon();

	const wchar_t* name() const;
	const wchar_t* otName() const;
	uint16_t otId() const;
	unsigned xp() const;
	unsigned currentHp() const;
	Type type1() const;
	Type type2() const;

	void enumerate() const;
private:
	PokemonImpl* m_impl;
};

class Game {
public:
	Game(uint8_t* memory);
	virtual ~Game() {}

	virtual const wchar_t* trainerName() const = 0;

	virtual Pokemon partyPokemon(int i) = 0;
	virtual unsigned nPartyPokemon() const = 0;
	virtual Pokemon boxPokemon(int box, int i) = 0;
	virtual unsigned nBoxPokemon(int box) const = 0;

protected:
	uint8_t* m_memory;
};

#endif
