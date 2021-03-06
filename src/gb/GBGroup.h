#ifndef PTXN_GB_GROUP_H
#define PTXN_GB_GROUP_H

#include "common/Group.h"
#include "common/Pokemon.h"
#include "gb/GameBoyGame.h"

template<typename T>
class GBGroup : public Group {
public:
	GBGroup(GameBoyGame* gen);

	virtual std::unique_ptr<Pokemon> at(unsigned i) override;
	virtual unsigned length() const override;

	virtual void remove(unsigned i) override;
	virtual bool insert(const Pokemon& pokemon) override;

protected:
	void setStart(uint8_t* start);
	void setNameLength(unsigned);

	GameBoyGame* m_gen;

private:
	uint8_t* m_start;
	uint8_t m_nameLength;
};

template <typename T>
GBGroup<T>::GBGroup(GameBoyGame* gen)
	: m_gen(gen)
	, m_start(gen->ram())
	, m_nameLength(11)
{
}

template <typename T>
std::unique_ptr<Pokemon> GBGroup<T>::at(unsigned i) {
	if (i >= length()) {
		return nullptr;
	}
	uint8_t* pstart = &m_start[2 + capacity() + sizeof(typename T::DataType) * i];
	uint8_t* nstart = &m_start[2 + (sizeof(typename T::DataType) + 1 + m_nameLength) * capacity() + m_nameLength * i];
	uint8_t* tstart = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + m_nameLength * i];
	return std::unique_ptr<Pokemon>(new T(m_gen, pstart, nstart, tstart));
}

template <typename T>
unsigned GBGroup<T>::length() const {
	if (m_start[0] == 0xFF) {
		return 0;
	}
	return std::min<unsigned>(m_start[0], capacity());
}

template <typename T>
bool GBGroup<T>::insert(const Pokemon& pokemon) {
	unsigned len = length();
	if (len >= capacity()) {
		return false;
	}

	std::unique_ptr<T> convertedPokemon = T::copy(m_gen, pokemon);
	if (!convertedPokemon) {
		return false;
	}

	const typename T::DataType* data = reinterpret_cast<const typename T::DataType*>(convertedPokemon->data(nullptr));

	++m_start[0];
	uint8_t* sstart = &m_start[1 + len];
	uint8_t* pstart = &m_start[2 + capacity() + sizeof(typename T::DataType) * len];
	uint8_t* nstart = &m_start[2 + (sizeof(typename T::DataType) + 1 + m_nameLength) * capacity() + m_nameLength * len];
	uint8_t* tstart = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + m_nameLength * len];
	*sstart = data->species;
	memmove(pstart, data, sizeof(typename T::DataType));
	m_gen->stringToGameText(nstart, m_nameLength, pokemon.name());
	m_gen->stringToGameText(tstart, m_nameLength, pokemon.otName());

	return true;
}

template <typename T>
void GBGroup<T>::remove(unsigned i) {
	unsigned len = length();
	if (i >= len) {
		return;
	}
	--m_start[0];
	uint8_t* sstart = &m_start[1 + i];
	uint8_t* snext = &m_start[1 + i + 1];
	uint8_t* send = &m_start[1 + m_start[0]];
	uint8_t* pstart = &m_start[2 + capacity() + sizeof(typename T::DataType) * i];
	uint8_t* pnext = &m_start[2 + capacity() + sizeof(typename T::DataType) * (i + 1)];
	uint8_t* pend = &m_start[2 + capacity() + sizeof(typename T::DataType) * m_start[0]];
	uint8_t* nstart = &m_start[2 + (sizeof(typename T::DataType) + 1 + m_nameLength) * capacity() + m_nameLength * i];
	uint8_t* nnext = &m_start[2 + (sizeof(typename T::DataType) + 1 + m_nameLength) * capacity() + m_nameLength * (i + 1)];
	uint8_t* nend = &m_start[2 + (sizeof(typename T::DataType) + 1 + m_nameLength) * capacity() + m_nameLength * m_start[0]];
	uint8_t* tstart = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + m_nameLength * i];
	uint8_t* tnext = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + m_nameLength * (i + 1)];
	uint8_t* tend = &m_start[2 + (sizeof(typename T::DataType) + 1) * capacity() + m_nameLength * m_start[0]];
	memmove(sstart, snext, len - i - 1);
	memset(send, 0xFF, capacity() - m_start[0]);
	memmove(pstart, pnext, sizeof(typename T::DataType) * (len - i - 1));
	memset(pend, 0, sizeof(typename T::DataType) * (capacity() - m_start[0]));
	memmove(nstart, nnext, m_nameLength * (len - i - 1));
	memset(nend, 0, m_nameLength * (capacity() - m_start[0]));
	memmove(tstart, tnext, m_nameLength * (len - i - 1));
	memset(tend, 0, m_nameLength * (capacity() - m_start[0]));
}

template <typename T>
void GBGroup<T>::setStart(uint8_t* start) {
	m_start = start;
}

template <typename T>
void GBGroup<T>::setNameLength(unsigned length) {
	m_nameLength = length;
}

#endif
