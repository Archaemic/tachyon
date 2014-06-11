#ifndef PTXN_G1_PARTY_H
#define PTXN_G1_PARTY_H

#include "common/GBGroup.h"
#include "gen1/G1PartyPokemon.h"

class Generation1;

class G1Party : public GBGroup<G1PartyPokemon> {
public:
	G1Party(Generation1* gen);

	virtual unsigned capacity() const override;
};

#endif
