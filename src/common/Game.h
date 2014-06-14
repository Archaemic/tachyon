#ifndef PTXN_GAME_H
#define PTXN_GAME_H

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/Group.h"
#include "common/PokemonSpecies.h"

class Pokemon;

class Game {
public:
	enum Version {
		INVALID = 0,

		G10J_RED,
		G10J_GREEN,
		G11J_BLUE,
		G12J_YELLOW,

		G10E_RED,
		G10E_BLUE,
		G11E_YELLOW,

		G20J_GOLD,
		G20J_SILVER,
		G21J_CRYSTAL,

		G20E_GOLD,
		G20E_SILVER,
		G21E_CRYSTAL,

		G30J_RUBY,
		G30J_SAPPHIRE,
		G31J_EMERALD,
		G32J_FIRE_RED,
		G32J_LEAF_GREEN,

		G30E_RUBY,
		G30E_SAPPHIRE,
		G31E_EMERALD,
		G32E_FIRE_RED,
		G32E_LEAF_GREEN
	};

	class Loader {
	public:
		virtual Game* load(uint8_t* memory, const uint8_t* rom) const = 0;
		static void registerLoader(std::unique_ptr<Loader> loader);
	};

	static std::unique_ptr<Game> load(uint8_t* memory, const uint8_t* rom);
	virtual ~Game() {}

	const std::string& trainerName() const;

	Group* party();
	Group* box(unsigned box);
	virtual unsigned numBoxes() const = 0;

	virtual Version version() const = 0;
	virtual int generation() const = 0;

	const uint8_t* rom() const { return m_rom; }
	uint8_t* ram() { return m_memory; }
	virtual void finalize() = 0;

	// This function does lazy evaluation and memoizes the result
	// Thus it is not const. PokemonSpecies objects are own by the Game
	virtual PokemonSpecies* species(PokemonSpecies::Id);

protected:
	Game(uint8_t* memory, const uint8_t* rom);

	void setTrainerName(const std::string& name);
	void putSpecies(PokemonSpecies::Id, PokemonSpecies*);

	void setParty(Group* party);
	void addBox(Group* box);

	virtual void stringToGameText(uint8_t* gameText, size_t len, const std::string&) = 0;
	void stringToMappedText(const char** mapping, char terminator, uint8_t* gameText, size_t len, const std::string&);

	std::string m_trainerName;

	uint8_t* m_memory;
	const uint8_t* m_rom;

private:
	static std::vector<std::unique_ptr<Loader>> s_loaders;
	std::unordered_map<int, std::unique_ptr<PokemonSpecies>> m_species;

	std::unique_ptr<Group> m_party;
	std::vector<std::unique_ptr<Group>> m_boxes;
};

#endif
