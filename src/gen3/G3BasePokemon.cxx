#include "gen3/G3BasePokemon.h"

G3PokemonGrowth* G3BasePokemonData::growth() {
	switch (personality % 24) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		return &data.f0.g;
	case 6:
	case 7:
	case 12:
	case 13:
	case 18:
	case 19:
		return &data.f1.g;
	case 8:
	case 10:
	case 14:
	case 16:
	case 20:
	case 22:
		return &data.f2.g;
	case 9:
	case 11:
	case 15:
	case 17:
	case 21:
	case 23:
		return &data.f3.g;
	default:
		return nullptr;
	}
}

G3PokemonAttacks* G3BasePokemonData::attacks() {
	switch (personality % 24) {
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		return &data.f0.a;
	case 0:
	case 1:
	case 14:
	case 15:
	case 20:
	case 21:
		return &data.f1.a;
	case 2:
	case 4:
	case 12:
	case 17:
	case 18:
	case 23:
		return &data.f2.a;
	case 3:
	case 5:
	case 13:
	case 16:
	case 19:
	case 22:
		return &data.f3.a;
	default:
		return nullptr;
	}
}

G3PokemonEVs* G3BasePokemonData::evs() {
	switch (personality % 24) {
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		return &data.f0.e;
	case 2:
	case 3:
	case 8:
	case 9:
	case 22:
	case 23:
		return &data.f1.e;
	case 0:
	case 5:
	case 6:
	case 11:
	case 19:
	case 21:
		return &data.f2.e;
	case 1:
	case 4:
	case 7:
	case 10:
	case 18:
	case 20:
		return &data.f3.e;
	default:
		return nullptr;
	}
}

G3PokemonMisc* G3BasePokemonData::misc() {
	switch (personality % 24) {
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		return &data.f0.m;
	case 4:
	case 5:
	case 10:
	case 11:
	case 16:
	case 17:
		return &data.f1.m;
	case 1:
	case 3:
	case 7:
	case 9:
	case 13:
	case 15:
		return &data.f2.m;
	case 0:
	case 2:
	case 6:
	case 8:
	case 12:
	case 14:
		return &data.f3.m;
	default:
		return nullptr;
	}
}
