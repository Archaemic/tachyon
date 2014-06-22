#ifndef PTXN_POKEMON_SPECIES_H
#define PTXN_POKEMON_SPECIES_H

#include <cstdint>

#include "common/MultipaletteSprite.h"
#include "common/Type.h"

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

	enum Forme {
		FORME_NORMAL = 0,

		UNOWN_A = 0,
		UNOWN_B,
		UNOWN_C,
		UNOWN_D,
		UNOWN_E,
		UNOWN_F,
		UNOWN_G,
		UNOWN_H,
		UNOWN_I,
		UNOWN_J,
		UNOWN_K,
		UNOWN_L,
		UNOWN_M,
		UNOWN_N,
		UNOWN_O,
		UNOWN_P,
		UNOWN_Q,
		UNOWN_R,
		UNOWN_S,
		UNOWN_T,
		UNOWN_U,
		UNOWN_V,
		UNOWN_W,
		UNOWN_X,
		UNOWN_Y,
		UNOWN_Z,
		UNOWN_EXCLAIM,
		UNOWN_QUESTION
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
	virtual Forme forme() const = 0;
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

	const MultipaletteSprite* frontSprite() const;
	void setFrontSprite(MultipaletteSprite*);

	const MultipaletteSprite* backSprite() const;
	void setBackSprite(MultipaletteSprite*);

	const MultipaletteSprite* menuSprite() const;
	void setMenuSprite(MultipaletteSprite*);

	const char* readable() const;
	static const char* readable(Id id);

private:
	std::unique_ptr<MultipaletteSprite> m_frontSprite;
	std::unique_ptr<MultipaletteSprite> m_backSprite;
	std::unique_ptr<MultipaletteSprite> m_menuSprite;
};

#endif
