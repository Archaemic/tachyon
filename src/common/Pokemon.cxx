#include "common/Pokemon.h"

#include "common/PokemonSpecies.h"

const static char* natureNames[] = {
	u8"Hardy",
	u8"Lonely",
	u8"Brave",
	u8"Adamant",
	u8"Naughty",
	u8"Bold",
	u8"Docile",
	u8"Relaxed",
	u8"Impish",
	u8"Lax",
	u8"Timid",
	u8"Hasty",
	u8"Serious",
	u8"Jolly",
	u8"Naive",
	u8"Modest",
	u8"Mild",
	u8"Quiet",
	u8"Bashful",
	u8"Rash",
	u8"Calm",
	u8"Gentle",
	u8"Sassy",
	u8"Careful",
	u8"Quirky"
};

unsigned Pokemon::level() const {
	switch (species()->growthRate()) {
	case PokemonSpecies::LEVEL_FAST:
		for (unsigned i = 0; i <= 100; ++i) {
			unsigned xpNeeded = 4 * i * i * i / 5;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		break;
	case PokemonSpecies::LEVEL_MEDIUM_FAST:
		for (unsigned i = 0; i <= 100; ++i) {
			unsigned xpNeeded = i * i * i;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		break;
	case PokemonSpecies::LEVEL_MEDIUM_SLOW:
		// Complex roots make programmers sad
		for (unsigned i = 2; i <= 100; ++i) {
			unsigned xpNeeded = 6 * i * i * i / 5 - 15 * i * i + 100 * i - 140;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		break;
	case PokemonSpecies::LEVEL_SLOW:
		for (unsigned i = 0; i <= 100; ++i) {
			unsigned xpNeeded = 5 * i * i * i / 4;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		break;
	case PokemonSpecies::LEVEL_ERRATIC:
		for (unsigned i = 0; i <= 50; ++i) {
			unsigned xpNeeded = (i * i * i * (100 - i)) / 50;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		for (unsigned i = 51; i <= 68; ++i) {
			unsigned xpNeeded = (i * i * i * (150 - i)) / 100;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		for (unsigned i = 69; i <= 98; ++i) {
			unsigned xpNeeded = (i * i * i * (1911 - 10 * i) / 3) / 500;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		for (unsigned i = 99; i <= 100; ++i) {
			unsigned xpNeeded = (i * i * i * (160 - i)) / 100;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		break;
	case PokemonSpecies::LEVEL_FLUCTUATING:
		for (unsigned i = 0; i <= 15; ++i) {
			unsigned xpNeeded = i * i * i * ((i + 1) / 3 + 24) / 50;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		for (unsigned i = 16; i <= 36; ++i) {
			unsigned xpNeeded = (i * i * i * (i + 14)) / 50;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		for (unsigned i = 37; i <= 100; ++i) {
			unsigned xpNeeded = i * i * i * (i / 2 + 32) / 50;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
		break;
	}
	return 100;
}

Pokemon::Gender Pokemon::gender() const {
	uint8_t ratio = species()->genderRatio();
	if (ratio == 0xFF) {
		return GENDERLESS;
	}
	if (ratio == 0xFE) {
		return FEMALE;
	}
	if (genderDeterminer() < ratio) {
		return FEMALE;
	}
	return MALE;
}

const char* Pokemon::natureReadable(Pokemon::Nature nature) {
	if (nature == NO_NATURE) {
		return u8"---";
	}
	if (nature >= NATURE_MAX) {
		return u8"???";
	}
	return natureNames[nature];
}

const char* Pokemon::natureReadable() const {
	return natureReadable(nature());
}

const std::string& Pokemon::name() const {
	return m_name;
}

void Pokemon::setName(const std::string& name) {
	m_name = name;
}

const std::string& Pokemon::otName() const {
	return m_otName;
}

void Pokemon::setOtName(const std::string& otName) {
	m_otName = otName;
}
