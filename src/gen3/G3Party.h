#ifndef PTXN_G3_PARTY_H
#define PTXN_G3_PARTY_H

#include "common/Group.h"

class Generation3;

class G3Party : public Group {
public:
	G3Party(Generation3* gen);

	virtual std::unique_ptr<Pokemon> at(unsigned i) override;
	virtual unsigned length() const override;
	virtual unsigned capacity() const override;
	virtual std::string name() const override;

	virtual void remove(unsigned i) override;
	virtual bool insert(const Pokemon& pokemon) override;

private:
	Generation3* m_gen;
	uint8_t* m_start;
};

#endif
