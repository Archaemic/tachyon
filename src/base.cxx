#include "base.h"

Game::Game(uint8_t* memory)
	: m_memory(memory)
{
}

Pokemon::Pokemon(PokemonImpl* impl)
	: m_impl(impl)
{
}

Pokemon::Pokemon(const Pokemon& other)
	: m_impl(other.m_impl)
{
	m_impl->ref();
}

Pokemon::~Pokemon() {
	m_impl->deref();
}

const wchar_t* Pokemon::name() const {
	return m_impl->name();
}

const wchar_t* Pokemon::otName() const {
	return m_impl->otName();
}

uint16_t Pokemon::otId() const {
	return m_impl->otId();
}

unsigned Pokemon::xp() const {
	return m_impl->xp();
}

unsigned Pokemon::currentHp() const {
	return m_impl->currentHp();
}

void Pokemon::enumerate() const {
	printf("\tName: %ls\n", name());
	printf("\tOT: %ls (%u)\n", otName(), otId());
	printf("\tExp: %u\n", xp());
	printf("\tHP: %u\n", currentHp());
}

PokemonImpl::PokemonImpl()
	: m_refs(1)
{
}

void PokemonImpl::ref() {
	++m_refs;
}

void PokemonImpl::deref() {
	--m_refs;

	if (m_refs == 0) {
		delete this;
	}
}
