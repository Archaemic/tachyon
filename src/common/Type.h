#ifndef PTXN_TYPE_H
#define PTXN_TYPE_H

enum Type {
	NORMAL = 0x10,
	FIGHTING,
	FLYING,
	POISON,
	GROUND,
	ROCK,
	BUG,
	GHOST,
	STEEL,

	FIRE = 0x20,
	WATER,
	GRASS,
	ELECTRIC,
	PSYCHIC,
	ICE,
	DRAGON,
	DARK,
	FAIRY,

	QQQ = 0,
	BIRD = 1
};

const char* TypeReadable(Type type);

#endif
