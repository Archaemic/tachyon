#ifndef PTXN_G3_BOX_H
#define PTXN_G3_BOX_H

#include "common/Group.h"

enum {
	G3_POKEMON_PER_BOX = 30,
};

class Generation3;
struct G3BasePokemonData;

class G3Box : public Group {
public:
	G3Box(Generation3* gen, G3BasePokemonData* start);

	virtual std::unique_ptr<Pokemon> at(unsigned i) override;
	virtual unsigned length() const override;
	virtual unsigned capacity() const override;

	virtual void remove(unsigned i) override;
	virtual bool insert(const Pokemon& pokemon) override;

private:
	Generation3* m_gen;
	G3BasePokemonData* m_start;
};

#endif
