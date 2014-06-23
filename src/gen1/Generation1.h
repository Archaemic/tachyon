#ifndef PTXN_GENERATION_1_H
#define PTXN_GENERATION_1_H

#include "gb/GameBoyGame.h"

struct G1PokemonBaseStats;

class Generation1 : public GameBoyGame {
public:
	enum {
		SIZE_SAV = 0x8000,
		SIZE_ROM = 0x100000,
	};

	Generation1(uint8_t* memory, const uint8_t* rom);
	~Generation1();

	virtual unsigned numBoxes() const override;

	virtual Edition version() const override;
	virtual int generation() const { return 1; }

	virtual const PokemonSpecies* species(PokemonSpecies::Id, PokemonSpecies::Forme = PokemonSpecies::FORME_NORMAL) override;

	virtual void finalize() override;

	virtual PokemonSpecies::Id mapId(unsigned id) const override;

	static void registerLoader();

private:
	void loadSprites(PokemonSpecies* species, const G1PokemonBaseStats* data) const;
	void prepareSprites();
	static uint8_t mirrorByte(uint8_t byte);

	const static ChecksumMapping s_checksums[];

	uint8_t* m_spriteMemory;

	class Loader : public Game::Loader {
	public:
		virtual Generation1* load(uint8_t* memory, const uint8_t* rom) const override;
		virtual Edition detect(const uint8_t* rom) const override;
	};
};

#endif
