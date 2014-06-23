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
	unsigned baseLevel = 0;
	if (species()->growthRate() == PokemonSpecies::LEVEL_MEDIUM_SLOW) {
		baseLevel = 2;
	}
	for (uint8_t i = baseLevel; i <= 100; ++i) {
		if (species()->expToLevel(i) > xp()) {
			return i - 1;
		}
	}
	return 1;
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
