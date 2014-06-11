#ifndef PTXN_GENERATION_1_H
#define PTXN_GENERATION_1_H

#include "common/GameBoyGame.h"

class Generation1 : public GameBoyGame {
public:
	enum {
		SIZE_SAV = 0x8000,
		SIZE_ROM = 0x100000,
	};

	Generation1(uint8_t* memory, const uint8_t* rom);

	virtual std::unique_ptr<Group> party() override;
	virtual std::unique_ptr<Group> box(unsigned box) override;
	virtual unsigned numBoxes() const override;

	virtual Version version() const override;
	virtual int generation() const { return 1; }

	virtual PokemonSpecies* species(PokemonSpecies::Id) override;

	virtual void finalize() override;

	static void registerLoader();

private:
	const static ChecksumMapping s_checksums[];

	class Loader : public Game::Loader {
	public:
		virtual Game* load(uint8_t* memory, const uint8_t* rom) const override;
	};
};

#endif
