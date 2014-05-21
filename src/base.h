#ifndef PTXN_BASE_H
#define PTXN_BASE_H

#include <cwchar>
#include <cstdint>
#include <memory>
#include <unordered_map>

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

	QQQ = 0,
	BIRD = 1
};

const wchar_t* TypeReadable(Type type);
const wchar_t* MoveReadable(unsigned move);

class PokemonSpecies {
public:
	enum Id {
		MISSINGNO = 0,
		BULBASAUR,
		IVYSAUR,
		VENUSAUR,
		CHARMANDER,
		CHARMELEON,
		CHARIZARD,
		SQUIRTLE,
		WARTORTLE,
		BLASTOISE,
		CATERPIE,
		METAPOD,
		BUTTERFREE,
		WEEDLE,
		KAKUNA,
		BEEDRILL,
		PIDGEY,
		PIDGEOTTO,
		PIDGEOT,
		RATTATA,
		RATICATE,
		SPEAROW,
		FEAROW,
		EKANS,
		ARBOK,
		PIKACHU,
		RAICHU,
		SANDSHREW,
		SANDSLASH,
		NIDORAN_F,
		NIDORINA,
		NIDOQUEEN,
		NIDORAN_M,
		NIDORINO,
		NIDOKING,
		CLEFAIRY,
		CLEFABLE,
		VULPIX,
		NINETALES,
		JIGGLYPUFF,
		WIGGLYTUFF,
		ZUBAT,
		GOLBAT,
		ODDISH,
		GLOOM,
		VILEPLUME,
		PARAS,
		PARASECT,
		VENONAT,
		VENOMOTH,
		DIGLETT,
		DUGTRIO,
		MEOWTH,
		PERSIAN,
		PSYDUCK,
		GOLDUCK,
		MANKEY,
		PRIMEAPE,
		GROWLITHE,
		ARCANINE,
		POLIWAG,
		POLIWHIRL,
		POLIWRATH,
		ABRA,
		KADABRA,
		ALAKAZAM,
		MACHOP,
		MACHOKE,
		MACHAMP,
		BELLSPROUT,
		WEEPINBELL,
		VICTREEBEL,
		TENTACOOL,
		TENTACRUEL,
		GEODUDE,
		GRAVELER,
		GOLEM,
		PONYTA,
		RAPIDASH,
		SLOWPOKE,
		SLOWBRO,
		MAGNEMITE,
		MAGNETON,
		FARFETCH_D,
		DODUO,
		DODRIO,
		SEEL,
		DEWGONG,
		GRIMER,
		MUK,
		SHELLDER,
		CLOYSTER,
		GASTLY,
		HAUNTER,
		GENGAR,
		ONIX,
		DROWZEE,
		HYPNO,
		KRABBY,
		KINGLER,
		VOLTORB,
		ELECTRODE,
		EXEGGCUTE,
		EXEGGUTOR,
		CUBONE,
		MAROWAK,
		HITMONLEE,
		HITMONCHAN,
		LICKITUNG,
		KOFFING,
		WEEZING,
		RHYHORN,
		RHYDON,
		CHANSEY,
		TANGELA,
		KANGASKHAN,
		HORSEA,
		SEADRA,
		GOLDEEN,
		SEAKING,
		STARYU,
		STARMIE,
		MR_MIME,
		SCYTHER,
		JYNX,
		ELECTABUZZ,
		MAGMAR,
		PINSIR,
		TAUROS,
		MAGIKARP,
		GYARADOS,
		LAPRAS,
		DITTO,
		EEVEE,
		VAPOREON,
		JOLTEON,
		FLAREON,
		PORYGON,
		OMANYTE,
		OMASTAR,
		KABUTO,
		KABUTOPS,
		AERODACTYL,
		SNORLAX,
		ARTICUNO,
		ZAPDOS,
		MOLTRES,
		DRATINI,
		DRAGONAIR,
		DRAGONITE,
		MEWTWO,
		MEW,
		CHIKORITA,
		BAYLEEF,
		MEGANIUM,
		CYNDAQUIL,
		QUILAVA,
		TYPHLOSION,
		TOTODILE,
		CROCONAW,
		FERALIGATR,
		SENTRET,
		FURRET,
		HOOTHOOT,
		NOCTOWL,
		LEDYBA,
		LEDIAN,
		SPINARAK,
		ARIADOS,
		CROBAT,
		CHINCHOU,
		LANTURN,
		PICHU,
		CLEFFA,
		IGGLYBUFF,
		TOGEPI,
		TOGETIC,
		NATU,
		XATU,
		MAREEP,
		FLAAFFY,
		AMPHAROS,
		BELLOSSOM,
		MARILL,
		AZUMARILL,
		SUDOWOODO,
		POLITOED,
		HOPPIP,
		SKIPLOOM,
		JUMPLUFF,
		AIPOM,
		SUNKERN,
		SUNFLORA,
		YANMA,
		WOOPER,
		QUAGSIRE,
		ESPEON,
		UMBREON,
		MURKROW,
		SLOWKING,
		MISDREAVUS,
		UNOWN,
		WOBBUFFET,
		GIRAFARIG,
		PINECO,
		FORRETRESS,
		DUNSPARCE,
		GLIGAR,
		STEELIX,
		SNUBBULL,
		GRANBULL,
		QWILFISH,
		SCIZOR,
		SHUCKLE,
		HERACROSS,
		SNEASEL,
		TEDDIURSA,
		URSARING,
		SLUGMA,
		MAGCARGO,
		SWINUB,
		PILOSWINE,
		CORSOLA,
		REMORAID,
		OCTILLERY,
		DELIBIRD,
		MANTINE,
		SKARMORY,
		HOUNDOUR,
		HOUNDOOM,
		KINGDRA,
		PHANPY,
		DONPHAN,
		PORYGON2,
		STANTLER,
		SMEARGLE,
		TYROGUE,
		HITMONTOP,
		SMOOCHUM,
		ELEKID,
		MAGBY,
		MILTANK,
		BLISSEY,
		RAIKOU,
		ENTEI,
		SUICUNE,
		LARVITAR,
		PUPITAR,
		TYRANITAR,
		LUGIA,
		HO_OH,
		CELEBI,
		TREECKO,
		GROVYLE,
		SCEPTILE,
		TORCHIC,
		COMBUSKEN,
		BLAZIKEN,
		MUDKIP,
		MARSHTOMP,
		SWAMPERT,
		POOCHYENA,
		MIGHTYENA,
		ZIGZAGOON,
		LINOONE,
		WURMPLE,
		SILCOON,
		BEAUTIFLY,
		CASCOON,
		DUSTOX,
		LOTAD,
		LOMBRE,
		LUDICOLO,
		SEEDOT,
		NUZLEAF,
		SHIFTRY,
		TAILLOW,
		SWELLOW,
		WINGULL,
		PELIPPER,
		RALTS,
		KIRLIA,
		GARDEVOIR,
		SURSKIT,
		MASQUERAIN,
		SHROOMISH,
		BRELOOM,
		SLAKOTH,
		VIGOROTH,
		SLAKING,
		NINCADA,
		NINJASK,
		SHEDINJA,
		WHISMUR,
		LOUDRED,
		EXPLOUD,
		MAKUHITA,
		HARIYAMA,
		AZURILL,
		NOSEPASS,
		SKITTY,
		DELCATTY,
		SABLEYE,
		MAWILE,
		ARON,
		LAIRON,
		AGGRON,
		MEDITITE,
		MEDICHAM,
		ELECTRIKE,
		MANECTRIC,
		PLUSLE,
		MINUN,
		VOLBEAT,
		ILLUMISE,
		ROSELIA,
		GULPIN,
		SWALOT,
		CARVANHA,
		SHARPEDO,
		WAILMER,
		WAILORD,
		NUMEL,
		CAMERUPT,
		TORKOAL,
		SPOINK,
		GRUMPIG,
		SPINDA,
		TRAPINCH,
		VIBRAVA,
		FLYGON,
		CACNEA,
		CACTURNE,
		SWABLU,
		ALTARIA,
		ZANGOOSE,
		SEVIPER,
		LUNATONE,
		SOLROCK,
		BARBOACH,
		WHISCASH,
		CORPHISH,
		CRAWDAUNT,
		BALTOY,
		CLAYDOL,
		LILEEP,
		CRADILY,
		ANORITH,
		ARMALDO,
		FEEBAS,
		MILOTIC,
		CASTFORM,
		KECLEON,
		SHUPPET,
		BANETTE,
		DUSKULL,
		DUSCLOPS,
		TROPIUS,
		CHIMECHO,
		ABSOL,
		WYNAUT,
		SNORUNT,
		GLALIE,
		SPHEAL,
		SEALEO,
		WALREIN,
		CLAMPERL,
		HUNTAIL,
		GOREBYSS,
		RELICANTH,
		LUVDISC,
		BAGON,
		SHELGON,
		SALAMENCE,
		BELDUM,
		METANG,
		METAGROSS,
		REGIROCK,
		REGICE,
		REGISTEEL,
		LATIAS,
		LATIOS,
		KYOGRE,
		GROUDON,
		RAYQUAZA,
		JIRACHI,
		DEOXYS
	};

	enum GrowthRate {
		LEVEL_FAST,
		LEVEL_MEDIUM_FAST,
		LEVEL_MEDIUM_SLOW,
		LEVEL_SLOW
	};

	virtual ~PokemonSpecies() {}

	virtual Id id() const = 0;
	virtual unsigned baseHp() const = 0;
	virtual unsigned baseAttack() const = 0;
	virtual unsigned baseDefense() const = 0;
	virtual unsigned baseSpeed() const = 0;
	virtual unsigned baseSpecialAttack() const = 0;
	virtual unsigned baseSpecialDefense() const = 0;
	virtual Type type1() const = 0;
	virtual Type type2() const = 0;
	virtual PokemonSpecies::GrowthRate growthRate() const = 0;

	const wchar_t* readable() const;
	static const wchar_t* readable(Id id);
};

class Pokemon {
public:
	virtual ~Pokemon() {}

	virtual const wchar_t* name() const = 0;
	virtual PokemonSpecies* species() const = 0;
	virtual const wchar_t* otName() const = 0;
	virtual uint16_t otId() const = 0;
	virtual unsigned xp() const = 0;
	virtual unsigned currentHp() const = 0;
	virtual Type type1() const = 0;
	virtual Type type2() const = 0;

	virtual unsigned level() const;
	virtual unsigned maxHp() const = 0;
	virtual unsigned attack() const = 0;
	virtual unsigned defense() const = 0;
	virtual unsigned speed() const = 0;
	virtual unsigned specialAttack() const = 0;
	virtual unsigned specialDefense() const = 0;

	virtual unsigned ivHp() const = 0;
	virtual unsigned ivAttack() const = 0;
	virtual unsigned ivDefense() const = 0;
	virtual unsigned ivSpeed() const = 0;
	virtual unsigned ivSpecialAttack() const = 0;
	virtual unsigned ivSpecialDefense() const = 0;

	virtual unsigned evHp() const = 0;
	virtual unsigned evAttack() const = 0;
	virtual unsigned evDefense() const = 0;
	virtual unsigned evSpeed() const = 0;
	virtual unsigned evSpecialAttack() const = 0;
	virtual unsigned evSpecialDefense() const = 0;

	virtual unsigned move1() const = 0;
	virtual unsigned move2() const = 0;
	virtual unsigned move3() const = 0;
	virtual unsigned move4() const = 0;
};

class Game {
public:
	enum Version {
		INVALID = 0,

		G10J_RED,
		G10J_GREEN,
		G11J_BLUE,
		G12J_YELLOW,

		G10E_RED,
		G10E_BLUE,
		G11E_YELLOW,

		G20J_GOLD,
		G20J_SILVER,
		G21J_CRYSTAL,

		G20E_GOLD,
		G20E_SILVER,
		G21E_CRYSTAL,

		G30J_RUBY,
		G30J_SAPPHIRE,
		G31J_EMERALD,
		G32J_FIRE_RED,
		G32J_LEAF_GREEN,

		G30E_RUBY,
		G30E_SAPPHIRE,
		G31E_EMERALD,
		G32E_FIRE_RED,
		G32E_LEAF_GREEN
	};

	Game(uint8_t* memory, const uint8_t* rom);
	virtual ~Game() {}

	virtual const wchar_t* trainerName() const = 0;

	virtual Pokemon* partyPokemon(int i) = 0;
	virtual unsigned nPartyPokemon() const = 0;
	virtual Pokemon* boxPokemon(int box, int i) = 0;
	virtual unsigned nBoxPokemon(int box) const = 0;

	virtual Version version() const = 0;

	const uint8_t* rom() const { return m_rom; }

	// This function does lazy evaluation and memoizes the result
	// Thus it is not const
	virtual PokemonSpecies* species(PokemonSpecies::Id);

protected:
	void putSpecies(PokemonSpecies::Id, PokemonSpecies*);

	uint8_t* m_memory;
	const uint8_t* m_rom;

private:
	std::unordered_map<int, std::unique_ptr<PokemonSpecies>> m_species;
};

class TMSet {
public:
	virtual ~TMSet() {}
	virtual bool containsTM(int tm) const = 0;
	virtual bool containsHM(int hm) const = 0;
};

#endif
