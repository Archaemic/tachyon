#ifndef PTXN_G2_BOX_H
#define PTXN_G2_BOX_H

#include "gen-gb-private.h"
#include "gen2/G2BasePokemon.h"

class Generation2;

class G2Box : public GBGroup<G2BasePokemon> {
public:
	G2Box(Generation2* gen, unsigned box);

	virtual unsigned capacity() const override;
};

#endif
