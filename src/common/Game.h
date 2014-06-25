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
class Sprite;

class Game {
public:
	enum Localization {
		JAPANESE = 0x0,
		ENGLISH = 0x10,
		GERMAN = 0x20,
		FRENCH = 0x30,
		SPANISH = 0x40,
		ITALIAN = 0x50,
		KOREAN = 0x60,
		LOCALIZATION_MAX = 0x70
	};

	enum Version {
		INVALID = 0,

		G10_RED = 0x101,
		G10_GREEN = 0x102,
		G10_BLUE = 0x102,
		G11_BLUE = 0x103,
		G12_YELLOW = 0x104,
		G13_YELLOW = 0x105,

		G20_GOLD = 0x201,
		G20_SILVER = 0x202,
		G21_CRYSTAL = 0x203,

		G30_RUBY = 0x301,
		G30_SAPPHIRE = 0x302,
		G31_EMERALD = 0x303,
		G32_FIRE_RED = 0x304,
		G32_LEAF_GREEN = 0x305,
	};

	enum {
		MASK_GENERATION = 0xF00,
		MASK_LOCALIZATION = 0x0F0,
		MASK_GAME = 0xF0F,
		MASK_VERSION = 0x00F,
	};

	typedef uint16_t Edition;

	class Loader {
	public:
		virtual Game* load(uint8_t* memory, const uint8_t* rom) const = 0;
		virtual Game::Edition detect(const uint8_t* rom) const = 0;
		static void registerLoader(std::unique_ptr<Loader> loader);
	};

	static std::unique_ptr<Game> load(uint8_t* memory, const uint8_t* rom);
	static Edition detect(const uint8_t* rom);
	virtual ~Game() {}

	const std::string& trainerName() const;

	Group* party();
	Group* box(unsigned box);
	virtual unsigned numBoxes() const = 0;

	virtual Edition version() const = 0;
	uint8_t* ram() { return m_memory; }
	virtual void finalize() = 0;

	virtual PokemonSpecies::Id mapId(unsigned id) const { return static_cast<PokemonSpecies::Id>(id); }

	// This function does lazy evaluation and memoizes the result
	// Thus it is not const. PokemonSpecies objects are own by the Game
	virtual const PokemonSpecies* species(PokemonSpecies::Id, PokemonSpecies::Forme = PokemonSpecies::FORME_NORMAL);

protected:
	Game(uint8_t* memory, const uint8_t* rom);

	void setTrainerName(const std::string& name);
	void putSpecies(PokemonSpecies::Id, PokemonSpecies*, PokemonSpecies::Forme = PokemonSpecies::FORME_NORMAL);

	void setParty(Group* party);
	void addBox(Group* box);

	const uint8_t* rom() const { return m_rom; }

	virtual void stringToGameText(uint8_t* gameText, size_t len, const std::string&) const = 0;
	void stringToMappedText(const char** mapping, char terminator, uint8_t* gameText, size_t len, const std::string&) const;

	std::string m_trainerName;

	uint8_t* m_memory;
	const uint8_t* m_rom;

private:
	static std::vector<std::unique_ptr<Loader>> s_loaders;
	std::unordered_map<int, std::unique_ptr<PokemonSpecies>> m_species;
	std::unordered_map<int, std::unordered_map<int, std::unique_ptr<PokemonSpecies>>> m_formes;

	std::unique_ptr<Group> m_party;
	std::vector<std::unique_ptr<Group>> m_boxes;
};

#endif
