#ifndef PTXN_GEN_3_H
#define PTXN_GEN_3_H

#include "base.h"

enum {
	SIZE_GEN_3_SAV = 0x20000,
	SIZE_GEN_3_ROM = 0x1000000,
};

class Generation3 : public Game {
public:
	Generation3(uint8_t* memory, const uint8_t* rom);

	virtual std::unique_ptr<Group> party() override;
	virtual std::unique_ptr<Group> box(unsigned box) override;

	virtual Version version() const override;

	virtual PokemonSpecies* species(PokemonSpecies::Id) override;

	static void registerLoader();

private:
	const static unsigned MAX_SECTIONS = 14;

	struct NameMapping {
		uint32_t name;
		Game::Version version;
	};

	struct Section {
		uint8_t data[0xFF4];
		uint16_t id;
		uint16_t checksum;
		uint32_t padding;
		uint32_t index;
	};

	const static NameMapping s_names[];

	Section* m_sections[MAX_SECTIONS];
	uint32_t m_version;

	static Version version(const struct NameMapping* names, uint32_t name);
	class Loader : public Game::Loader {
	public:
		virtual Game* load(uint8_t* memory, const uint8_t* rom) const override;
	};

public:
	static std::string gameTextToUTF8(const uint8_t* gameText, size_t len);
};

#endif
