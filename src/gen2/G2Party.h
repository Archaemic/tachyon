#ifndef PTXN_G2_PARTY_H
#define PTXN_G2_PARTY_H

#include "gb/GBGroup.h"
#include "gen2/G2PartyPokemon.h"

class Generation2;

class G2Party : public GBGroup<G2PartyPokemon> {
public:
	G2Party(Generation2* gen);

	virtual unsigned capacity() const override;
	virtual std::string name() const override;

private:
	std::string m_name;
};

#endif
