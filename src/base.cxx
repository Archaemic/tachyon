#include "base.h"

const static wchar_t* typeNames[] = {
	L"???",
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	L"Normal",
	L"Fighting",
	L"Flying",
	L"Poison",
	L"Ground",
	L"Rock",
	L"Bug",
	L"Ghost",
	L"Steel",
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	L"Fire",
	L"Water",
	L"Grass",
	L"Electric",
	L"Psychic",
	L"Ice",
	L"Dragon",
	L"Dark",
};

const wchar_t* TypeReadable(Type type) {
	const wchar_t* readable = nullptr;
	if (type <= DARK) {
		readable = typeNames[type];
	}
	if (!readable) {
		readable = L"???";
	}
	return readable;
}

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

Type Pokemon::type1() const {
	return m_impl->type1();
}

Type Pokemon::type2() const {
	return m_impl->type2();
}

void Pokemon::enumerate() const {
	printf("\tName: %ls\n", name());
	printf("\tOT: %ls (%u)\n", otName(), otId());
	printf("\tExp: %u\n", xp());
	printf("\tHP: %u\n", currentHp());
	if (type1() == type2()) {
		printf("\tType: %ls\n", TypeReadable(type1()));
	} else {
		printf("\tType: %ls/%ls\n", TypeReadable(type1()), TypeReadable(type2()));
	}
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
