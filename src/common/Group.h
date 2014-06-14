#ifndef PTXN_GROUP_H
#define PTXN_GROUP_H

#include <memory>
#include <string>

class Pokemon;

class Group {
public:
	virtual std::unique_ptr<Pokemon> at(unsigned i) = 0;
	virtual unsigned length() const = 0;
	virtual unsigned capacity() const = 0;
	virtual std::string name() const = 0;

	virtual void remove(unsigned i) = 0;
	virtual bool insert(const Pokemon& pokemon) = 0;
};

#endif
