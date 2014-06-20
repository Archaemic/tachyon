#include "common/Game.h"

#include <codecvt>
#include <iostream>

std::vector<std::unique_ptr<Game::Loader>> Game::s_loaders;

Game::Game(uint8_t* memory, const uint8_t* rom)
	: m_memory(memory)
	, m_rom(rom)
{
}

void Game::Loader::registerLoader(std::unique_ptr<Game::Loader> loader) {
	s_loaders.push_back(std::move(loader));
}

std::unique_ptr<Game> Game::load(uint8_t* memory, const uint8_t* rom) {
	Game* game;
	for (auto iter = s_loaders.begin(); iter < s_loaders.end(); ++iter) {
		game = (*iter)->load(memory, rom);
		if (game) {
			return std::unique_ptr<Game>(game);
		}
	}
	return nullptr;
}

Game::Edition Game::detect(const uint8_t* rom) {
	Game::Edition edition;
	for (auto iter = s_loaders.begin(); iter < s_loaders.end(); ++iter) {
		edition = (*iter)->detect(rom);
		if (edition) {
			return edition;
		}
	}
	return Game::INVALID;
}

const std::string& Game::trainerName() const {
	return m_trainerName;
}

void Game::setTrainerName(const std::string& name) {
	m_trainerName = name;
}

Group* Game::party() {
	return m_party.get();
}

void Game::setParty(Group* party) {
	m_party = std::unique_ptr<Group>(party);
}

Group* Game::box(unsigned box) {
	if (box > m_boxes.size()) {
		return nullptr;
	}
	return m_boxes[box].get();
}

void Game::addBox(Group* box) {
	m_boxes.push_back(std::unique_ptr<Group>(box));
}

const PokemonSpecies* Game::species(PokemonSpecies::Id id, PokemonSpecies::Forme forme) {
	if (!forme) {
		return m_species[id].get();
	} else {
		return m_formes[id][forme].get();
	}
}

void Game::putSpecies(PokemonSpecies::Id id, PokemonSpecies* species, PokemonSpecies::Forme forme) {
	if (!forme) {
		m_species[id] = std::unique_ptr<PokemonSpecies>(species);
	} else {
		m_formes[id][forme] = std::unique_ptr<PokemonSpecies>(species);
	}
}

void Game::stringToMappedText(const char** map, char terminator, uint8_t* mappedText, size_t len, const std::string& string) const {
	if (!len) {
		return;
	}
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
	std::u32string widestring = utf32conv.from_bytes(string);
	auto iter = widestring.begin();
	while (len && iter != widestring.end()) {
		std::u32string current;
		current.push_back(*iter);
		for (size_t m = 0; m < 0x100; ++m) {
			std::u32string mapItem = utf32conv.from_bytes(map[m]);
			auto oldIter = iter;
			std::u32string fullCurrent(current);
			for (size_t i = 0; i < mapItem.size(); ++i) {
				if (mapItem[i] == fullCurrent[i]) {
					if (mapItem == fullCurrent) {
						*mappedText = m;
						--len;
						++mappedText;
						goto loopEnd;
					}
					++iter;
					if (iter == widestring.end()) {
						break;
						iter = oldIter;
					}
					fullCurrent.push_back(*iter);
				}
			}
		}
		loopEnd:
		++iter;
	}
	for (size_t i = 0; i < len; ++i) {
		mappedText[i] = terminator;
	}
	if (!len) {
		mappedText[-1] = terminator;
	}
}
