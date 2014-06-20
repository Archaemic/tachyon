#ifndef PTXN_GENERATION_3_H
#define PTXN_GENERATION_3_H

#include "common/Game.h"
#include "common/MultipaletteSprite.h"

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

	virtual unsigned numBoxes() const;

	virtual Edition version() const override;
	virtual int generation() const { return 3; }

	virtual const PokemonSpecies* species(PokemonSpecies::Id, PokemonSpecies::Forme = PokemonSpecies::FORME_NORMAL) override;

	virtual void finalize() override;

	Section* section(Section::ID sectionID);

	static void registerLoader();

	static void lz77Decompress(const uint8_t* source, uint8_t* dest, size_t maxLength);

	const static uint16_t reverseIdMapping[387];

private:
	struct NameMapping {
		uint32_t name;
		Game::Edition version;
	};

	const static NameMapping s_names[];

	Section* m_sections[Section::MAX_SECTIONS];
	std::unique_ptr<G3BasePokemonData[]> m_boxes;
	uint32_t m_version;

	void loadSprites(PokemonSpecies* species) const;

	static Edition version(const struct NameMapping* names, uint32_t name);
	virtual void stringToGameText(uint8_t* gameText, size_t len, const std::string&) const override;

	class Loader : public Game::Loader {
	public:
		virtual Generation3* load(uint8_t* memory, const uint8_t* rom) const override;
		virtual Edition detect(const uint8_t* rom) const override;
	};

public:
	std::string gameTextToUTF8(const uint8_t* gameText, size_t len) const;
};

#endif
