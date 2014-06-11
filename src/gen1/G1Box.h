#ifndef PTXN_G1_BOX_H
#define PTXN_G1_BOX_H

#include "common/GBGroup.h"
#include "gen1/G1BasePokemon.h"

class Generation1;

class G1Box : public GBGroup<G1BasePokemon> {
public:
	G1Box(Generation1* gen, unsigned box);

	virtual unsigned capacity() const override;
};

#endif
