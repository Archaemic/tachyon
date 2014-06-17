#ifndef PTXN_GENERATION_2_H
#define PTXN_GENERATION_2_H

#include "common/GameBoyGame.h"
#include "common/MultipaletteSprite.h"

class Generation2 : public GameBoyGame {
public:
	enum {
		SIZE_SAV = 0x8000,
		SIZE_ROM = 0x200000,
	};

	Generation2(uint8_t* memory, const uint8_t* rom);

	virtual unsigned numBoxes() const override;

	virtual Version version() const override;
	virtual int generation() const { return 2; }

	virtual PokemonSpecies* species(PokemonSpecies::Id) override;

	virtual void finalize() override;

	static void registerLoader();

	std::unique_ptr<MultipaletteSprite> frontSprite(PokemonSpecies::Id, unsigned size) const;

private:
	const static ChecksumMapping s_checksums[];

	void lzDecompress(const uint8_t* source, uint8_t* dest, size_t maxLength) const;

	class Loader : public Game::Loader {
	public:
		virtual Generation2* load(uint8_t* memory, const uint8_t* rom) const override;
		virtual Version detect(const uint8_t* rom) const override;
	};
};

#endif
