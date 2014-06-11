#include "common/Type.h"

const static char* typeNames[] = {
	u8"???",
	u8"Bird",
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
	u8"Normal",
	u8"Fighting",
	u8"Flying",
	u8"Poison",
	u8"Ground",
	u8"Rock",
	u8"Bug",
	u8"Ghost",
	u8"Steel",
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	u8"Fire",
	u8"Water",
	u8"Grass",
	u8"Electric",
	u8"Psychic",
	u8"Ice",
	u8"Dragon",
	u8"Dark",
	u8"Fairy"
};

const char* TypeReadable(Type type) {
	const char* readable = nullptr;
	if (type <= DARK) {
		readable = typeNames[type];
	}
	if (!readable) {
		readable = u8"???";
	}
	return readable;
}
