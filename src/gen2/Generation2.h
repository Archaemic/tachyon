#ifndef PTXN_GENERATION_2_H
#define PTXN_GENERATION_2_H

#include "common/MultipaletteSprite.h"
#include "gb/GameBoyGame.h"

struct G2PokemonBaseStats;

class Generation2 : public GameBoyGame {
public:
	enum {
		SIZE_SAV = 0x8000,
		SIZE_ROM = 0x200000,
	};

	struct Offsets {
		unsigned baseStats;
		unsigned spriteMapping;
		unsigned unownSpriteMapping;
		unsigned menuSpriteMapping;
		unsigned menuSprites;
		unsigned palettes;
		unsigned partyPokemon;
		unsigned boxSize;
		unsigned boxHigh;
		unsigned currentBoxId;
		unsigned boxNames;
		unsigned currentBox;
	};

	Generation2(uint8_t* memory, const uint8_t* rom);

	virtual unsigned numBoxes() const override;

	virtual Edition version() const override;
	virtual int generation() const { return 2; }
	const Offsets* offsets() const;

	virtual const PokemonSpecies* species(PokemonSpecies::Id, PokemonSpecies::Forme = PokemonSpecies::FORME_NORMAL) override;

	virtual void finalize() override;

	static void registerLoader();

	static void lzDecompress(const uint8_t* source, uint8_t* dest, size_t maxLength);

private:
	void loadSprites(PokemonSpecies* species, const G2PokemonBaseStats*) const;

	const static ChecksumMapping<Offsets> s_checksums[];
	const Offsets* m_offsets;

	class Loader : public Game::Loader {
	public:
		virtual Generation2* load(uint8_t* memory, const uint8_t* rom) const override;
		virtual Edition detect(const uint8_t* rom) const override;
	};
};

#endif
