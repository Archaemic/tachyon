#ifndef PTXN_BASE_H
#define PTXN_BASE_H

#include <cwchar>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

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
const char* MoveReadable(unsigned move);

class PokemonSpecies {
public:
	enum Id {
		EGG = -1,
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
		DEOXYS,
		TURTWIG,
		GROTLE,
		TORTERRA,
		CHIMCHAR,
		MONFERNO,
		INFERNAPE,
		PIPLUP,
		PRINPLUP,
		EMPOLEON,
		STARLY,
		STARAVIA,
		STARAPTOR,
		BIDOOF,
		BIBAREL,
		KRICKETOT,
		KRICKETUNE,
		SHINX,
		LUXIO,
		LUXRAY,
		BUDEW,
		ROSERADE,
		CRANIDOS,
		RAMPARDOS,
		SHIELDON,
		BASTIODON,
		BURMY,
		WORMADAM,
		MOTHIM,
		COMBEE,
		VESPIQUEN,
		PACHIRISU,
		BUIZEL,
		FLOATZEL,
		CHERUBI,
		CHERRIM,
		SHELLOS,
		GASTRODON,
		AMBIPOM,
		DRIFLOON,
		DRIFBLIM,
		BUNEARY,
		LOPUNNY,
		MISMAGIUS,
		HONCHKROW,
		GLAMEOW,
		PURUGLY,
		CHINGLING,
		STUNKY,
		SKUNTANK,
		BRONZOR,
		BRONZONG,
		BONSLY,
		MIME_JR,
		HAPPINY,
		CHATOT,
		SPIRITOMB,
		GIBLE,
		GABITE,
		GARCHOMP,
		MUNCHLAX,
		RIOLU,
		LUCARIO,
		HIPPOPOTAS,
		HIPPOWDON,
		SKORUPI,
		DRAPION,
		CROAGUNK,
		TOXICROAK,
		CARNIVINE,
		FINNEON,
		LUMINEON,
		MANTYKE,
		SNOVER,
		ABOMASNOW,
		WEAVILE,
		MAGNEZONE,
		LICKILICKY,
		RHYPERIOR,
		TANGROWTH,
		ELECTIVIRE,
		MAGMORTAR,
		TOGEKISS,
		YANMEGA,
		LEAFEON,
		GLACEON,
		GLISCOR,
		MAMOSWINE,
		PORYGON_Z,
		GALLADE,
		PROBOPASS,
		DUSKNOIR,
		FROSLASS,
		ROTOM,
		UXIE,
		MESPRIT,
		AZELF,
		DIALGA,
		PALKIA,
		HEATRAN,
		REGIGIGAS,
		GIRATINA,
		CRESSELIA,
		PHIONE,
		MANAPHY,
		DARKRAI,
		SHAYMIN,
		ARCEUS,
		VICTINI,
		SNIVY,
		SERVINE,
		SERPERIOR,
		TEPIG,
		PIGNITE,
		EMBOAR,
		OSHAWOTT,
		DEWOTT,
		SAMUROTT,
		PATRAT,
		WATCHOG,
		LILLIPUP,
		HERDIER,
		STOUTLAND,
		PURRLOIN,
		LIEPARD,
		PANSAGE,
		SIMISAGE,
		PANSEAR,
		SIMISEAR,
		PANPOUR,
		SIMIPOUR,
		MUNNA,
		MUSHARNA,
		PIDOVE,
		TRANQUILL,
		UNFEZANT,
		BLITZLE,
		ZEBSTRIKA,
		ROGGENROLA,
		BOLDORE,
		GIGALITH,
		WOOBAT,
		SWOOBAT,
		DRILBUR,
		EXCADRILL,
		AUDINO,
		TIMBURR,
		GURDURR,
		CONKELDURR,
		TYMPOLE,
		PALPITOAD,
		SEISMITOAD,
		THROH,
		SAWK,
		SEWADDLE,
		SWADLOON,
		LEAVANNY,
		VENIPEDE,
		WHIRLIPEDE,
		SCOLIPEDE,
		COTTONEE,
		WHIMSICOTT,
		PETILIL,
		LILLIGANT,
		BASCULIN,
		SANDILE,
		KROKOROK,
		KROOKODILE,
		DARUMAKA,
		DARMANITAN,
		MARACTUS,
		DWEBBLE,
		CRUSTLE,
		SCRAGGY,
		SCRAFTY,
		SIGILYPH,
		YAMASK,
		COFAGRIGUS,
		TIRTOUGA,
		CARRACOSTA,
		ARCHEN,
		ARCHEOPS,
		TRUBBISH,
		GARBODOR,
		ZORUA,
		ZOROARK,
		MINCCINO,
		CINCCINO,
		GOTHITA,
		GOTHORITA,
		GOTHITELLE,
		SOLOSIS,
		DUOSION,
		REUNICLUS,
		DUCKLETT,
		SWANNA,
		VANILLITE,
		VANILLISH,
		VANILLUXE,
		DEERLING,
		SAWSBUCK,
		EMOLGA,
		KARRABLAST,
		ESCAVALIER,
		FOONGUS,
		AMOONGUSS,
		FRILLISH,
		JELLICENT,
		ALOMOMOLA,
		JOLTIK,
		GALVANTULA,
		FERROSEED,
		FERROTHORN,
		KLINK,
		KLANG,
		KLINKLANG,
		TYNAMO,
		EELEKTRIK,
		EELEKTROSS,
		ELGYEM,
		BEHEEYEM,
		LITWICK,
		LAMPENT,
		CHANDELURE,
		AXEW,
		FRAXURE,
		HAXORUS,
		CUBCHOO,
		BEARTIC,
		CRYOGONAL,
		SHELMET,
		ACCELGOR,
		STUNFISK,
		MIENFOO,
		MIENSHAO,
		DRUDDIGON,
		GOLETT,
		GOLURK,
		PAWNIARD,
		BISHARP,
		BOUFFALANT,
		RUFFLET,
		BRAVIARY,
		VULLABY,
		MANDIBUZZ,
		HEATMOR,
		DURANT,
		DEINO,
		ZWEILOUS,
		HYDREIGON,
		LARVESTA,
		VOLCARONA,
		COBALION,
		TERRAKION,
		VIRIZION,
		TORNADUS,
		THUNDURUS,
		RESHIRAM,
		ZEKROM,
		LANDORUS,
		KYUREM,
		KELDEO,
		MELOETTA,
		GENESECT,
		CHESPIN,
		QUILLADIN,
		CHESNAUGHT,
		FENNEKIN,
		BRAIXEN,
		DELPHOX,
		FROAKIE,
		FROGADIER,
		GRENINJA,
		BUNNELBY,
		DIGGERSBY,
		FLETCHLING,
		FLETCHINDER,
		TALONFLAME,
		SCATTERBUG,
		SPEWPA,
		VIVILLON,
		LITLEO,
		PYROAR,
		FLABEBE,
		FLOETTE,
		FLORGES,
		SKIDDO,
		GOGOAT,
		PANCHAM,
		PANGORO,
		FURFROU,
		ESPURR,
		MEOWSTIC,
		HONEDGE,
		DOUBLADE,
		AEGISLASH,
		SPRITZEE,
		AROMATISSE,
		SWIRLIX,
		SLURPUFF,
		INKAY,
		MALAMAR,
		BINACLE,
		BARBARACLE,
		SKRELP,
		DRAGALGE,
		CLAUNCHER,
		CLAWITZER,
		HELIOPTILE,
		HELIOLISK,
		TYRUNT,
		TYRANTRUM,
		AMAURA,
		AURORUS,
		SYLVEON,
		HAWLUCHA,
		DEDENNE,
		CARBINK,
		GOOMY,
		SLIGGOO,
		GOODRA,
		KLEFKI,
		PHANTUMP,
		TREVENANT,
		PUMPKABOO,
		GOURGEIST,
		BERGMITE,
		AVALUGG,
		NOIBAT,
		NOIVERN,
		XERNEAS,
		YVELTAL,
		ZYGARDE,
		DIANCIE,
	};

	enum GrowthRate {
		LEVEL_FAST,
		LEVEL_MEDIUM_FAST,
		LEVEL_MEDIUM_SLOW,
		LEVEL_SLOW,
		LEVEL_ERRATIC,
		LEVEL_FLUCTUATING
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
	virtual uint8_t genderRatio() const = 0;
	virtual PokemonSpecies::GrowthRate growthRate() const = 0;

	const char* readable() const;
	static const char* readable(Id id);
};

class Pokemon {
public:
	enum Gender {
		GENDERLESS = 0,
		MALE,
		FEMALE
	};

	enum Nature {
		NO_NATURE = -1,
		HARDY = 0,
		LONELY,
		BRAVE,
		ADAMANT,
		NAUGHTY,
		BOLD,
		DOCILE,
		RELAXED,
		IMPISH,
		LAX,
		TIMID,
		HASTY,
		SERIOUS,
		JOLLY,
		NAIVE,
		MODEST,
		MILD,
		QUIET,
		BASHFUL,
		RASH,
		CALM,
		GENTLE,
		SASSY,
		CAREFUL,
		QUIRKY,
		NATURE_MAX
	};

	virtual ~Pokemon() {}

	const std::string& name() const;
	virtual PokemonSpecies* species() const = 0;
	const std::string& otName() const;
	virtual uint16_t otId() const = 0;
	virtual uint16_t otSecretId() const = 0;
	virtual Gender gender() const;
	virtual bool shiny() const = 0;
	virtual Nature nature() const = 0;
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

	static const char* natureReadable(Nature nature);
	const char* natureReadable() const;

	void setName(const std::string& name);
	void setOtName(const std::string& otName);
	virtual void setOtId(uint16_t) = 0;
	virtual void setOtSecretId(uint16_t) = 0;

	virtual void setIvHp(unsigned) = 0;
	virtual void setIvAttack(unsigned) = 0;
	virtual void setIvDefense(unsigned) = 0;
	virtual void setIvSpeed(unsigned) = 0;
	virtual void setIvSpecialAttack(unsigned) = 0;
	virtual void setIvSpecialDefense(unsigned) = 0;

protected:
	virtual uint8_t genderDeterminer() const = 0;

private:
	std::string m_name;
	std::string m_otName;
};

class Group {
public:
	virtual std::unique_ptr<Pokemon> at(unsigned i) = 0;
	virtual unsigned length() const = 0;
	virtual unsigned capacity() const = 0;
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

	class Loader {
	public:
		virtual Game* load(uint8_t* memory, const uint8_t* rom) const = 0;
		static void registerLoader(std::unique_ptr<Loader> loader);
	};

	static std::unique_ptr<Game> load(uint8_t* memory, const uint8_t* rom);
	virtual ~Game() {}

	const std::string& trainerName() const;

	virtual std::unique_ptr<Group> party() = 0;
	virtual std::unique_ptr<Group> box(unsigned box) = 0;

	virtual Version version() const = 0;

	const uint8_t* rom() const { return m_rom; }
	uint8_t* ram() { return m_memory; }
	virtual void finalize() = 0;

	// This function does lazy evaluation and memoizes the result
	// Thus it is not const. PokemonSpecies objects are own by the Game
	virtual PokemonSpecies* species(PokemonSpecies::Id);

protected:
	Game(uint8_t* memory, const uint8_t* rom);

	void setTrainerName(const std::string& name);
	void putSpecies(PokemonSpecies::Id, PokemonSpecies*);

	std::string m_trainerName;

	uint8_t* m_memory;
	const uint8_t* m_rom;

private:
	static std::vector<std::unique_ptr<Loader>> s_loaders;
	std::unordered_map<int, std::unique_ptr<PokemonSpecies>> m_species;
};

template <typename T>
class GenericPokemonSpecies : public PokemonSpecies {
public:
	GenericPokemonSpecies(const T*);

	virtual Id id() const override;
	virtual unsigned baseHp() const override;
	virtual unsigned baseAttack() const override;
	virtual unsigned baseDefense() const override;
	virtual unsigned baseSpeed() const override;
	virtual unsigned baseSpecialAttack() const override;
	virtual unsigned baseSpecialDefense() const override;
	virtual Type type1() const override;
	virtual Type type2() const override;
	virtual uint8_t genderRatio() const override;
	virtual PokemonSpecies::GrowthRate growthRate() const override;

protected:
	virtual Type mapType(unsigned) const = 0;

private:
	const T* m_data;
};

template <typename T>
GenericPokemonSpecies<T>::GenericPokemonSpecies(const T* data)
	: m_data(data)
{
}

template <typename T>
PokemonSpecies::Id GenericPokemonSpecies<T>::id() const {
	return (PokemonSpecies::Id) m_data->species;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseHp() const {
	return m_data->hp;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseAttack() const {
	return m_data->attack;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseDefense() const {
	return m_data->defense;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseSpeed() const {
	return m_data->speed;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseSpecialAttack() const {
	return m_data->specialAttack;
}

template <typename T>
unsigned GenericPokemonSpecies<T>::baseSpecialDefense() const {
	return m_data->specialDefense;
}

template <typename T>
PokemonSpecies::GrowthRate GenericPokemonSpecies<T>::growthRate() const {
	switch (m_data->growthRate) {
	case 0:
		return PokemonSpecies::LEVEL_MEDIUM_FAST;
	case 1:
		return PokemonSpecies::LEVEL_ERRATIC;
	case 2:
		return PokemonSpecies::LEVEL_FLUCTUATING;
	case 3:
		return PokemonSpecies::LEVEL_MEDIUM_SLOW;
	case 4:
		return PokemonSpecies::LEVEL_FAST;
	case 5:
		return PokemonSpecies::LEVEL_SLOW;
	default:
		return PokemonSpecies::LEVEL_MEDIUM_FAST;
	}
}

template <typename T>
Type GenericPokemonSpecies<T>::type1() const {
	return mapType(m_data->type1);
}

template <typename T>
Type GenericPokemonSpecies<T>::type2() const {
	return mapType(m_data->type2);
}

template <typename T>
uint8_t GenericPokemonSpecies<T>::genderRatio() const {
	return m_data->genderRatio;
}

#endif
