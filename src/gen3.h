#ifndef PTXN_GEN_3_H
#define PTXN_GEN_3_H

#include "base.h"

struct G3BasePokemonData;

class Generation3 : public Game {
public:
	enum {
		SIZE_SAV = 0x20000,
		SIZE_ROM = 0x1000000,
	};

	struct Section {
		enum ID {
			TRAINER,
			BAG,
			UNKNOWN_0,
			UNKNOWN_1,
			RIVAL,
			PC_0,
			PC_1,
			PC_2,
			PC_3,
			PC_4,
			PC_5,
			PC_6,
			PC_7,
			PC_8,
			MAX_SECTIONS
		};

		uint8_t data[0xFF4];
		uint16_t id;
		uint16_t checksum;
		uint32_t padding;
		uint32_t index;
	};

	Generation3(uint8_t* memory, const uint8_t* rom);

	virtual std::unique_ptr<Group> party() override;
	virtual std::unique_ptr<Group> box(unsigned box) override;

	virtual Version version() const override;

	virtual PokemonSpecies* species(PokemonSpecies::Id) override;

	Section* section(Section::ID sectionID);

	static void registerLoader();

private:
	struct NameMapping {
		uint32_t name;
		Game::Version version;
	};

	const static NameMapping s_names[];

	Section* m_sections[Section::MAX_SECTIONS];
	std::unique_ptr<G3BasePokemonData[]> m_boxes;
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
