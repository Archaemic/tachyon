#ifndef PTXN_GEN_1_H
#define PTXN_GEN_1_H

#include <wchar.h>
#include <stdint.h>

const wchar_t charMapGen1En[0x100];

enum {
	SIZE_GEN_1 = 0x8000,
	G10E_TRAINER_NAME = 0x2598,
	G10E_PARTY_POKEMON = 0x2F2C,
	G10E_CURRENT_BOX = 0x30C0,
	G10E_BOX_1 = 0x4000
};


enum G1Box {
	G1_BOX_CURRENT,
	G1_BOX_01,
	G1_BOX_02,
	G1_BOX_03,
	G1_BOX_04,
	G1_BOX_05,
	G1_BOX_06,
	G1_BOX_07,
	G1_BOX_08,
	G1_BOX_09,
	G1_BOX_10,
	G1_BOX_11,
	G1_BOX_12
};

struct G1PartyPokemon {
	uint8_t pokemonId;
	uint16_t currentHp;
	uint8_t displayLevel;
	uint8_t status;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
	uint16_t otId;
	uint32_t xp : 24;
	uint16_t evHp;
	uint16_t evAttack;
	uint16_t evDefense;
	uint16_t evSpeed;
	uint16_t evSpecial;
	uint16_t ivs;
	uint8_t ppMove1;
	uint8_t ppMove2;
	uint8_t ppMove3;
	uint8_t ppMove4;
	uint8_t level;
	uint16_t maxHp;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t special;
} __attribute__((packed));

struct G1BoxPokemon {
	uint8_t pokemonId;
	uint16_t currentHp;
	uint8_t displayLevel;
	uint8_t status;
	uint8_t type1;
	uint8_t type2;
	uint8_t catchRate;
	uint8_t move1;
	uint8_t move2;
	uint8_t move3;
	uint8_t move4;
	uint16_t otId;
	uint32_t xp : 24;
	uint16_t evHp;
	uint16_t evAttack;
	uint16_t evDefense;
	uint16_t evSpeed;
	uint16_t evSpecial;
	uint16_t ivs;
	uint8_t ppMove1;
	uint8_t ppMove2;
	uint8_t ppMove3;
	uint8_t ppMove4;
} __attribute__((packed));

int getPartyPokemon(void* saveblock, struct G1PartyPokemon** pokemon , uint8_t** names, uint8_t** otNames);
int getBoxPokemon(void* saveblock, enum G1Box box, struct G1BoxPokemon** pokemon , uint8_t** names, uint8_t** otNames);

#endif
