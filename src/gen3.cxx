#include "gen3-private.h"

#include <sstream>

enum {
	G3_POKEMON_PER_BOX = 30,
	G3_BOXES = 14,

	G30E_PARTY_POKEMON = 0x0234,

	G30E_RUBY_BASE_STATS = 0x1FEC34,
	G30E_SAPPHIRE_BASE_STATS = 0x1FEBC4,

	G31J_BASE_STATS = 0x2F0D70,
	G31E_BASE_STATS = 0x3203E8,

	G32J_FIRE_RED_BASE_STATS = 0x2111A8,
	G32E_FIRE_RED_BASE_STATS = 0x2547A0,

	G32J_LEAF_GREEN_BASE_STATS = 0x211184,
	G32E_LEAF_GREEN_BASE_STATS = 0x25477C,
};

const static Type typeMapping[256] = {
	NORMAL,
	FIGHTING,
	FLYING,
	POISON,
	GROUND,
	ROCK,
	BUG,
	GHOST,
	STEEL,
	QQQ,
	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	PSYCHIC,
	ICE,
	DRAGON,
	DARK
};

const static PokemonSpecies::Id idMapping[] = {
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::BULBASAUR,
	PokemonSpecies::IVYSAUR,
	PokemonSpecies::VENUSAUR,
	PokemonSpecies::CHARMANDER,
	PokemonSpecies::CHARMELEON,
	PokemonSpecies::CHARIZARD,
	PokemonSpecies::SQUIRTLE,
	PokemonSpecies::WARTORTLE,
	PokemonSpecies::BLASTOISE,
	PokemonSpecies::CATERPIE,
	PokemonSpecies::METAPOD,
	PokemonSpecies::BUTTERFREE,
	PokemonSpecies::WEEDLE,
	PokemonSpecies::KAKUNA,
	PokemonSpecies::BEEDRILL,
	PokemonSpecies::PIDGEY,
	PokemonSpecies::PIDGEOTTO,
	PokemonSpecies::PIDGEOT,
	PokemonSpecies::RATTATA,
	PokemonSpecies::RATICATE,
	PokemonSpecies::SPEAROW,
	PokemonSpecies::FEAROW,
	PokemonSpecies::EKANS,
	PokemonSpecies::ARBOK,
	PokemonSpecies::PIKACHU,
	PokemonSpecies::RAICHU,
	PokemonSpecies::SANDSHREW,
	PokemonSpecies::SANDSLASH,
	PokemonSpecies::NIDORAN_F,
	PokemonSpecies::NIDORINA,
	PokemonSpecies::NIDOQUEEN,
	PokemonSpecies::NIDORAN_M,
	PokemonSpecies::NIDORINO,
	PokemonSpecies::NIDOKING,
	PokemonSpecies::CLEFAIRY,
	PokemonSpecies::CLEFABLE,
	PokemonSpecies::VULPIX,
	PokemonSpecies::NINETALES,
	PokemonSpecies::JIGGLYPUFF,
	PokemonSpecies::WIGGLYTUFF,
	PokemonSpecies::ZUBAT,
	PokemonSpecies::GOLBAT,
	PokemonSpecies::ODDISH,
	PokemonSpecies::GLOOM,
	PokemonSpecies::VILEPLUME,
	PokemonSpecies::PARAS,
	PokemonSpecies::PARASECT,
	PokemonSpecies::VENONAT,
	PokemonSpecies::VENOMOTH,
	PokemonSpecies::DIGLETT,
	PokemonSpecies::DUGTRIO,
	PokemonSpecies::MEOWTH,
	PokemonSpecies::PERSIAN,
	PokemonSpecies::PSYDUCK,
	PokemonSpecies::GOLDUCK,
	PokemonSpecies::MANKEY,
	PokemonSpecies::PRIMEAPE,
	PokemonSpecies::GROWLITHE,
	PokemonSpecies::ARCANINE,
	PokemonSpecies::POLIWAG,
	PokemonSpecies::POLIWHIRL,
	PokemonSpecies::POLIWRATH,
	PokemonSpecies::ABRA,
	PokemonSpecies::KADABRA,
	PokemonSpecies::ALAKAZAM,
	PokemonSpecies::MACHOP,
	PokemonSpecies::MACHOKE,
	PokemonSpecies::MACHAMP,
	PokemonSpecies::BELLSPROUT,
	PokemonSpecies::WEEPINBELL,
	PokemonSpecies::VICTREEBEL,
	PokemonSpecies::TENTACOOL,
	PokemonSpecies::TENTACRUEL,
	PokemonSpecies::GEODUDE,
	PokemonSpecies::GRAVELER,
	PokemonSpecies::GOLEM,
	PokemonSpecies::PONYTA,
	PokemonSpecies::RAPIDASH,
	PokemonSpecies::SLOWPOKE,
	PokemonSpecies::SLOWBRO,
	PokemonSpecies::MAGNEMITE,
	PokemonSpecies::MAGNETON,
	PokemonSpecies::FARFETCH_D,
	PokemonSpecies::DODUO,
	PokemonSpecies::DODRIO,
	PokemonSpecies::SEEL,
	PokemonSpecies::DEWGONG,
	PokemonSpecies::GRIMER,
	PokemonSpecies::MUK,
	PokemonSpecies::SHELLDER,
	PokemonSpecies::CLOYSTER,
	PokemonSpecies::GASTLY,
	PokemonSpecies::HAUNTER,
	PokemonSpecies::GENGAR,
	PokemonSpecies::ONIX,
	PokemonSpecies::DROWZEE,
	PokemonSpecies::HYPNO,
	PokemonSpecies::KRABBY,
	PokemonSpecies::KINGLER,
	PokemonSpecies::VOLTORB,
	PokemonSpecies::ELECTRODE,
	PokemonSpecies::EXEGGCUTE,
	PokemonSpecies::EXEGGUTOR,
	PokemonSpecies::CUBONE,
	PokemonSpecies::MAROWAK,
	PokemonSpecies::HITMONLEE,
	PokemonSpecies::HITMONCHAN,
	PokemonSpecies::LICKITUNG,
	PokemonSpecies::KOFFING,
	PokemonSpecies::WEEZING,
	PokemonSpecies::RHYHORN,
	PokemonSpecies::RHYDON,
	PokemonSpecies::CHANSEY,
	PokemonSpecies::TANGELA,
	PokemonSpecies::KANGASKHAN,
	PokemonSpecies::HORSEA,
	PokemonSpecies::SEADRA,
	PokemonSpecies::GOLDEEN,
	PokemonSpecies::SEAKING,
	PokemonSpecies::STARYU,
	PokemonSpecies::STARMIE,
	PokemonSpecies::MR_MIME,
	PokemonSpecies::SCYTHER,
	PokemonSpecies::JYNX,
	PokemonSpecies::ELECTABUZZ,
	PokemonSpecies::MAGMAR,
	PokemonSpecies::PINSIR,
	PokemonSpecies::TAUROS,
	PokemonSpecies::MAGIKARP,
	PokemonSpecies::GYARADOS,
	PokemonSpecies::LAPRAS,
	PokemonSpecies::DITTO,
	PokemonSpecies::EEVEE,
	PokemonSpecies::VAPOREON,
	PokemonSpecies::JOLTEON,
	PokemonSpecies::FLAREON,
	PokemonSpecies::PORYGON,
	PokemonSpecies::OMANYTE,
	PokemonSpecies::OMASTAR,
	PokemonSpecies::KABUTO,
	PokemonSpecies::KABUTOPS,
	PokemonSpecies::AERODACTYL,
	PokemonSpecies::SNORLAX,
	PokemonSpecies::ARTICUNO,
	PokemonSpecies::ZAPDOS,
	PokemonSpecies::MOLTRES,
	PokemonSpecies::DRATINI,
	PokemonSpecies::DRAGONAIR,
	PokemonSpecies::DRAGONITE,
	PokemonSpecies::MEWTWO,
	PokemonSpecies::MEW,
	PokemonSpecies::CHIKORITA,
	PokemonSpecies::BAYLEEF,
	PokemonSpecies::MEGANIUM,
	PokemonSpecies::CYNDAQUIL,
	PokemonSpecies::QUILAVA,
	PokemonSpecies::TYPHLOSION,
	PokemonSpecies::TOTODILE,
	PokemonSpecies::CROCONAW,
	PokemonSpecies::FERALIGATR,
	PokemonSpecies::SENTRET,
	PokemonSpecies::FURRET,
	PokemonSpecies::HOOTHOOT,
	PokemonSpecies::NOCTOWL,
	PokemonSpecies::LEDYBA,
	PokemonSpecies::LEDIAN,
	PokemonSpecies::SPINARAK,
	PokemonSpecies::ARIADOS,
	PokemonSpecies::CROBAT,
	PokemonSpecies::CHINCHOU,
	PokemonSpecies::LANTURN,
	PokemonSpecies::PICHU,
	PokemonSpecies::CLEFFA,
	PokemonSpecies::IGGLYBUFF,
	PokemonSpecies::TOGEPI,
	PokemonSpecies::TOGETIC,
	PokemonSpecies::NATU,
	PokemonSpecies::XATU,
	PokemonSpecies::MAREEP,
	PokemonSpecies::FLAAFFY,
	PokemonSpecies::AMPHAROS,
	PokemonSpecies::BELLOSSOM,
	PokemonSpecies::MARILL,
	PokemonSpecies::AZUMARILL,
	PokemonSpecies::SUDOWOODO,
	PokemonSpecies::POLITOED,
	PokemonSpecies::HOPPIP,
	PokemonSpecies::SKIPLOOM,
	PokemonSpecies::JUMPLUFF,
	PokemonSpecies::AIPOM,
	PokemonSpecies::SUNKERN,
	PokemonSpecies::SUNFLORA,
	PokemonSpecies::YANMA,
	PokemonSpecies::WOOPER,
	PokemonSpecies::QUAGSIRE,
	PokemonSpecies::ESPEON,
	PokemonSpecies::UMBREON,
	PokemonSpecies::MURKROW,
	PokemonSpecies::SLOWKING,
	PokemonSpecies::MISDREAVUS,
	PokemonSpecies::UNOWN,
	PokemonSpecies::WOBBUFFET,
	PokemonSpecies::GIRAFARIG,
	PokemonSpecies::PINECO,
	PokemonSpecies::FORRETRESS,
	PokemonSpecies::DUNSPARCE,
	PokemonSpecies::GLIGAR,
	PokemonSpecies::STEELIX,
	PokemonSpecies::SNUBBULL,
	PokemonSpecies::GRANBULL,
	PokemonSpecies::QWILFISH,
	PokemonSpecies::SCIZOR,
	PokemonSpecies::SHUCKLE,
	PokemonSpecies::HERACROSS,
	PokemonSpecies::SNEASEL,
	PokemonSpecies::TEDDIURSA,
	PokemonSpecies::URSARING,
	PokemonSpecies::SLUGMA,
	PokemonSpecies::MAGCARGO,
	PokemonSpecies::SWINUB,
	PokemonSpecies::PILOSWINE,
	PokemonSpecies::CORSOLA,
	PokemonSpecies::REMORAID,
	PokemonSpecies::OCTILLERY,
	PokemonSpecies::DELIBIRD,
	PokemonSpecies::MANTINE,
	PokemonSpecies::SKARMORY,
	PokemonSpecies::HOUNDOUR,
	PokemonSpecies::HOUNDOOM,
	PokemonSpecies::KINGDRA,
	PokemonSpecies::PHANPY,
	PokemonSpecies::DONPHAN,
	PokemonSpecies::PORYGON,
	PokemonSpecies::STANTLER,
	PokemonSpecies::SMEARGLE,
	PokemonSpecies::TYROGUE,
	PokemonSpecies::HITMONTOP,
	PokemonSpecies::SMOOCHUM,
	PokemonSpecies::ELEKID,
	PokemonSpecies::MAGBY,
	PokemonSpecies::MILTANK,
	PokemonSpecies::BLISSEY,
	PokemonSpecies::RAIKOU,
	PokemonSpecies::ENTEI,
	PokemonSpecies::SUICUNE,
	PokemonSpecies::LARVITAR,
	PokemonSpecies::PUPITAR,
	PokemonSpecies::TYRANITAR,
	PokemonSpecies::LUGIA,
	PokemonSpecies::HO_OH,
	PokemonSpecies::CELEBI,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::MISSINGNO,
	PokemonSpecies::TREECKO,
	PokemonSpecies::GROVYLE,
	PokemonSpecies::SCEPTILE,
	PokemonSpecies::TORCHIC,
	PokemonSpecies::COMBUSKEN,
	PokemonSpecies::BLAZIKEN,
	PokemonSpecies::MUDKIP,
	PokemonSpecies::MARSHTOMP,
	PokemonSpecies::SWAMPERT,
	PokemonSpecies::POOCHYENA,
	PokemonSpecies::MIGHTYENA,
	PokemonSpecies::ZIGZAGOON,
	PokemonSpecies::LINOONE,
	PokemonSpecies::WURMPLE,
	PokemonSpecies::SILCOON,
	PokemonSpecies::BEAUTIFLY,
	PokemonSpecies::CASCOON,
	PokemonSpecies::DUSTOX,
	PokemonSpecies::LOTAD,
	PokemonSpecies::LOMBRE,
	PokemonSpecies::LUDICOLO,
	PokemonSpecies::SEEDOT,
	PokemonSpecies::NUZLEAF,
	PokemonSpecies::SHIFTRY,
	PokemonSpecies::NINCADA,
	PokemonSpecies::NINJASK,
	PokemonSpecies::SHEDINJA,
	PokemonSpecies::TAILLOW,
	PokemonSpecies::SWELLOW,
	PokemonSpecies::SHROOMISH,
	PokemonSpecies::BRELOOM,
	PokemonSpecies::SPINDA,
	PokemonSpecies::WINGULL,
	PokemonSpecies::PELIPPER,
	PokemonSpecies::SURSKIT,
	PokemonSpecies::MASQUERAIN,
	PokemonSpecies::WAILMER,
	PokemonSpecies::WAILORD,
	PokemonSpecies::SKITTY,
	PokemonSpecies::DELCATTY,
	PokemonSpecies::KECLEON,
	PokemonSpecies::BALTOY,
	PokemonSpecies::CLAYDOL,
	PokemonSpecies::NOSEPASS,
	PokemonSpecies::TORKOAL,
	PokemonSpecies::SABLEYE,
	PokemonSpecies::BARBOACH,
	PokemonSpecies::WHISCASH,
	PokemonSpecies::LUVDISC,
	PokemonSpecies::CORPHISH,
	PokemonSpecies::CRAWDAUNT,
	PokemonSpecies::FEEBAS,
	PokemonSpecies::MILOTIC,
	PokemonSpecies::CARVANHA,
	PokemonSpecies::SHARPEDO,
	PokemonSpecies::TRAPINCH,
	PokemonSpecies::VIBRAVA,
	PokemonSpecies::FLYGON,
	PokemonSpecies::MAKUHITA,
	PokemonSpecies::HARIYAMA,
	PokemonSpecies::ELECTRIKE,
	PokemonSpecies::MANECTRIC,
	PokemonSpecies::NUMEL,
	PokemonSpecies::CAMERUPT,
	PokemonSpecies::SPHEAL,
	PokemonSpecies::SEALEO,
	PokemonSpecies::WALREIN,
	PokemonSpecies::CACNEA,
	PokemonSpecies::CACTURNE,
	PokemonSpecies::SNORUNT,
	PokemonSpecies::GLALIE,
	PokemonSpecies::LUNATONE,
	PokemonSpecies::SOLROCK,
	PokemonSpecies::AZURILL,
	PokemonSpecies::SPOINK,
	PokemonSpecies::GRUMPIG,
	PokemonSpecies::PLUSLE,
	PokemonSpecies::MINUN,
	PokemonSpecies::MAWILE,
	PokemonSpecies::MEDITITE,
	PokemonSpecies::MEDICHAM,
	PokemonSpecies::SWABLU,
	PokemonSpecies::ALTARIA,
	PokemonSpecies::WYNAUT,
	PokemonSpecies::DUSKULL,
	PokemonSpecies::DUSCLOPS,
	PokemonSpecies::ROSELIA,
	PokemonSpecies::SLAKOTH,
	PokemonSpecies::VIGOROTH,
	PokemonSpecies::SLAKING,
	PokemonSpecies::GULPIN,
	PokemonSpecies::SWALOT,
	PokemonSpecies::TROPIUS,
	PokemonSpecies::WHISMUR,
	PokemonSpecies::LOUDRED,
	PokemonSpecies::EXPLOUD,
	PokemonSpecies::CLAMPERL,
	PokemonSpecies::HUNTAIL,
	PokemonSpecies::GOREBYSS,
	PokemonSpecies::ABSOL,
	PokemonSpecies::SHUPPET,
	PokemonSpecies::BANETTE,
	PokemonSpecies::SEVIPER,
	PokemonSpecies::ZANGOOSE,
	PokemonSpecies::RELICANTH,
	PokemonSpecies::ARON,
	PokemonSpecies::LAIRON,
	PokemonSpecies::AGGRON,
	PokemonSpecies::CASTFORM,
	PokemonSpecies::VOLBEAT,
	PokemonSpecies::ILLUMISE,
	PokemonSpecies::LILEEP,
	PokemonSpecies::CRADILY,
	PokemonSpecies::ANORITH,
	PokemonSpecies::ARMALDO,
	PokemonSpecies::RALTS,
	PokemonSpecies::KIRLIA,
	PokemonSpecies::GARDEVOIR,
	PokemonSpecies::BAGON,
	PokemonSpecies::SHELGON,
	PokemonSpecies::SALAMENCE,
	PokemonSpecies::BELDUM,
	PokemonSpecies::METANG,
	PokemonSpecies::METAGROSS,
	PokemonSpecies::REGIROCK,
	PokemonSpecies::REGICE,
	PokemonSpecies::REGISTEEL,
	PokemonSpecies::KYOGRE,
	PokemonSpecies::GROUDON,
	PokemonSpecies::RAYQUAZA,
	PokemonSpecies::LATIAS,
	PokemonSpecies::LATIOS,
	PokemonSpecies::JIRACHI,
	PokemonSpecies::DEOXYS,
	PokemonSpecies::CHIMECHO,
	PokemonSpecies::EGG,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN,
	PokemonSpecies::UNOWN
};

const static uint16_t reverseIdMapping[387] = {
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	106,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	138,
	139,
	140,
	141,
	142,
	143,
	144,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
	153,
	154,
	155,
	156,
	157,
	158,
	159,
	160,
	161,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	171,
	172,
	173,
	174,
	175,
	176,
	177,
	178,
	179,
	180,
	181,
	182,
	183,
	184,
	185,
	186,
	187,
	188,
	189,
	190,
	191,
	192,
	193,
	194,
	195,
	196,
	197,
	198,
	199,
	200,
	201,
	202,
	203,
	204,
	205,
	206,
	207,
	208,
	209,
	210,
	211,
	212,
	213,
	214,
	215,
	216,
	217,
	218,
	219,
	220,
	221,
	222,
	223,
	224,
	225,
	226,
	227,
	228,
	229,
	230,
	231,
	232,
	233,
	234,
	235,
	236,
	237,
	238,
	239,
	240,
	241,
	242,
	243,
	244,
	245,
	246,
	247,
	248,
	249,
	250,
	251,
	277,
	278,
	279,
	280,
	281,
	282,
	283,
	284,
	285,
	286,
	287,
	288,
	289,
	290,
	291,
	292,
	293,
	294,
	295,
	296,
	297,
	298,
	299,
	300,
	304,
	305,
	310,
	311,
	392,
	393,
	394,
	311,
	312,
	306,
	307,
	364,
	365,
	366,
	301,
	302,
	303,
	370,
	371,
	372,
	335,
	336,
	350,
	320,
	315,
	316,
	322,
	355,
	382,
	383,
	384,
	356,
	357,
	337,
	338,
	353,
	354,
	386,
	387,
	363,
	367,
	368,
	330,
	331,
	313,
	314,
	322,
	323,
	324,
	351,
	352,
	308,
	332,
	333,
	334,
	344,
	345,
	358,
	359,
	380,
	379,
	348,
	349,
	323,
	324,
	326,
	327,
	318,
	319,
	388,
	389,
	390,
	391,
	328,
	329,
	385,
	317,
	377,
	378,
	361,
	362,
	369,
	411,
	376,
	360,
	346,
	347,
	341,
	342,
	343,
	373,
	374,
	375,
	381,
	325,
	395,
	396,
	397,
	398,
	399,
	400,
	401,
	402,
	403,
	407,
	408,
	404,
	405,
	406,
	409,
	410
};

static const char* charMapEn[0x100] = {
	// 0x0X
	u8" ",	u8"À",	u8"Á",	u8"Â",	u8"Ç",	u8"È",	u8"É",	u8"Ê",
	u8"Ë",	u8"Ì",	u8"こ",	u8"Î",	u8"Ï",	u8"Ò",	u8"Ó",	u8"Ô",

	// 0x1X
	u8"Œ",	u8"Ù",	u8"Ú",	u8"Û",	u8"Ñ",	u8"ß",	u8"à",	u8"á",
	u8"ね",	u8"ç",	u8"è",	u8"é",	u8"ê",	u8"ë",	u8"ì",	u8"ま",

	// 0x2X
	u8"î",	u8"ï",	u8"ò",	u8"ó",	u8"ô",	u8"œ",	u8"ù",	u8"ú",
	u8"û",	u8"ñ",	u8"º",	u8"ª",	u8"�",	u8"&",	u8"+",	u8"あ",

	// 0x3X
	u8"ぃ",	u8"ぅ",	u8"ぇ",	u8"ぉ",	u8"v",	u8"=",	u8"ょ",	u8"が",
	u8"ぎ",	u8"ぐ",	u8"げ",	u8"ご",	u8"ざ",	u8"じ",	u8"ず",	u8"ぜ",

	// 0x4X
	u8"ぞ",	u8"だ",	u8"ぢ",	u8"づ",	u8"で",	u8"ど",	u8"ば",	u8"び",
	u8"ぶ",	u8"べ",	u8"ぼ",	u8"ぱ",	u8"ぴ",	u8"ぷ",	u8"ぺ",	u8"ぽ",

	// 0x5X
	u8"っ",	u8"¿",	u8"¡",	u8"ᴾK",	u8"ᴹN",	u8"ᴾO",	u8"ᴷé",	u8"�",
	u8"�",	u8"�",	u8"Í",	u8"%",	u8"(",	u8")",	u8"セ",	u8"ソ",

	// 0x6X
	u8"タ",	u8"チ",	u8"ツ",	u8"テ",	u8"ト",	u8"ナ",	u8"ニ",	u8"ヌ",
	u8"â",	u8"ノ",	u8"ハ",	u8"ヒ",	u8"フ",	u8"ヘ",	u8"ホ",	u8"í",

	// 0x7X
	u8"ミ",	u8"ム",	u8"メ",	u8"モ",	u8"ヤ",	u8"ユ",	u8"ヨ",	u8"ラ",
	u8"リ",	u8"⬆",	u8"⬇",	u8"⬅",	u8"➡",	u8"ヲ",	u8"ン",	u8"ァ",

	// 0x8X
	u8"ィ",	u8"ゥ",	u8"ェ",	u8"ォ",	u8"ャ",	u8"ュ",	u8"ョ",	u8"ガ",
	u8"ギ",	u8"グ",	u8"ゲ",	u8"ゴ",	u8"ザ",	u8"ジ",	u8"ズ",	u8"ゼ",

	// 0x9X
	u8"ゾ",	u8"ダ",	u8"ヂ",	u8"ヅ",	u8"デ",	u8"ド",	u8"バ",	u8"ビ",
	u8"ブ",	u8"ベ",	u8"ボ",	u8"パ",	u8"ピ",	u8"プ",	u8"ペ",	u8"ポ",

	// 0xAX
	u8"ッ",	u8"0",	u8"1",	u8"2",	u8"3",	u8"4",	u8"5",	u8"6",
	u8"7",	u8"8",	u8"9",	u8"!",	u8"?",	u8".",	u8"-",	u8"・",

	// 0xBX
	u8"…",	u8"“",	u8"”",	u8"‘",	u8"’",	u8"♂",	u8"♀",	u8"$",
	u8",",	u8"×",	u8"/",	u8"A",	u8"B",	u8"C",	u8"D",	u8"E",

	// 0xCX
	u8"F",	u8"G",	u8"H",	u8"I",	u8"J",	u8"K",	u8"L",	u8"M",
	u8"N",	u8"O",	u8"P",	u8"Q",	u8"R",	u8"S",	u8"T",	u8"U",

	// 0xDX
	u8"V",	u8"W",	u8"X",	u8"Y",	u8"Z",	u8"a",	u8"b",	u8"c",
	u8"d",	u8"e",	u8"f",	u8"g",	u8"h",	u8"i",	u8"j",	u8"k",

	// 0xEX
	u8"l",	u8"m",	u8"n",	u8"o",	u8"p",	u8"q",	u8"r",	u8"s",
	u8"t",	u8"u",	u8"v",	u8"w",	u8"x",	u8"y",	u8"z",	u8"▶",

	// 0xFX
	u8":",	u8"Ä",	u8"Ö",	u8"Ü",	u8"ä",	u8"ö",	u8"ü",	u8"⬆",
	u8"⬇",	u8"⬅",	u8"�",	u8"�",	u8"�",	u8"�",	u8"�",	u8""
};

const Generation3::NameMapping Generation3::s_names[] = {
	{ 'JVXA', Game::G30J_RUBY },
	{ 'EVXA', Game::G30E_RUBY },
	{ 'JPXA', Game::G30J_SAPPHIRE },
	{ 'EPXA', Game::G30E_SAPPHIRE },
	{ 'JEPB', Game::G31J_EMERALD },
	{ 'EEPB', Game::G31E_EMERALD },
	{ 'JRPB', Game::G32J_FIRE_RED },
	{ 'ERPB', Game::G32E_FIRE_RED },
	{ 'JGPB', Game::G32J_LEAF_GREEN },
	{ 'EGPB', Game::G32E_LEAF_GREEN },
	{ 0, Game::INVALID }
};

enum {
	G30E_TRAINER_NAME = 0x000
};

Generation3::Generation3(uint8_t* memory, const uint8_t* rom)
	: Game(memory, rom)
	, m_boxes(new G3BasePokemonData[G3_POKEMON_PER_BOX * G3_BOXES])
{
	Section* section = reinterpret_cast<Section*>(memory);
	m_version = section->index;
	if (section[Section::MAX_SECTIONS].index > m_version) {
		section = &section[Section::MAX_SECTIONS];
		m_version = section->index;
	}

	for (unsigned i = 0; i < Section::MAX_SECTIONS; ++i) {
		m_sections[i] = nullptr;
	}

	for (unsigned i = 0; i < Section::MAX_SECTIONS; ++i) {
		unsigned sectionID = section[i].id;
		if (sectionID < Section::MAX_SECTIONS) {
			m_sections[sectionID] = &section[i];
		}
	}

	unsigned remaining = sizeof(G3BasePokemonData) * G3_BOXES * G3_POKEMON_PER_BOX;
	uint8_t* boxData = reinterpret_cast<uint8_t*>(m_boxes.get());
	for (unsigned i = Section::PC_0; i < Section::MAX_SECTIONS; ++i) {
		uint8_t* data = this->section(static_cast<Section::ID>(i))->data;
		unsigned thisBox = std::min<unsigned>(remaining, 3968);
		if (i == Section::PC_0) {
			data += 4;
			thisBox -= 4;
		}
		memcpy(boxData, data, thisBox);
		remaining -= thisBox;
		boxData += thisBox;
	}

	setTrainerName(gameTextToUTF8(&m_sections[0]->data[G30E_TRAINER_NAME], 8));
}

void Generation3::registerLoader() {
	Game::Loader::registerLoader(std::unique_ptr<Loader>(new Loader()));
}

Game* Generation3::Loader::load(uint8_t* memory, const uint8_t* rom) const {
	uint32_t name = *(uint32_t*) &rom[0xAC];
	if (version(s_names, name)) {
		return new Generation3(memory, rom);
	}
	return nullptr;
}

std::string Generation3::gameTextToUTF8(const uint8_t* gameText, size_t len) {
	std::stringstream stream;
	for (size_t i = 0; i < len; ++i) {
		if (gameText[i] == 0xFF) {
			break;
		}
		stream << charMapEn[gameText[i]];
	}
	return stream.str();
}

std::unique_ptr<Group> Generation3::party() {
	return std::unique_ptr<Group>(new G3Party(this));
}

std::unique_ptr<Group> Generation3::box(unsigned box) {
	return std::unique_ptr<Group>(new G3Box(this, &m_boxes[G3_POKEMON_PER_BOX * box]));
}

Game::Version Generation3::version() const {
	uint32_t name = *(uint32_t*) &rom()[0xAC];
	return version(s_names, name);
}

PokemonSpecies* Generation3::species(PokemonSpecies::Id id) {
	PokemonSpecies* species = Game::species(id);
	if (!species && id <= PokemonSpecies::DEOXYS) {
		const G3PokemonBaseStats* stats;
		switch (version()) {
		case Game::G30E_RUBY:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G30E_RUBY_BASE_STATS]);
			break;
		case Game::G30E_SAPPHIRE:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G30E_SAPPHIRE_BASE_STATS]);
			break;
		case Game::G31J_EMERALD:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G31J_BASE_STATS]);
			break;
		case Game::G31E_EMERALD:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G31E_BASE_STATS]);
			break;
		case Game::G32J_FIRE_RED:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32J_FIRE_RED_BASE_STATS]);
			break;
		case Game::G32E_FIRE_RED:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32E_FIRE_RED_BASE_STATS]);
			break;
		case Game::G32J_LEAF_GREEN:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32J_LEAF_GREEN_BASE_STATS]);
			break;
		case Game::G32E_LEAF_GREEN:
			stats = reinterpret_cast<const G3PokemonBaseStats*>(&rom()[G32E_LEAF_GREEN_BASE_STATS]);
			break;
		default:
			return nullptr;
		}
		species = new G3PokemonSpecies(&stats[reverseIdMapping[id] - 1], id);
		putSpecies(id, species);
	}
	return species;
}

Game::Version Generation3::version(const NameMapping* mapping, uint32_t name) {
	while (mapping->name) {
		if (mapping->name == name) {
			break;
		}
		++mapping;
	}
	return mapping->version;
}

Generation3::Section* Generation3::section(Section::ID sectionID) {
	if (sectionID >= Section::MAX_SECTIONS) {
		return nullptr;
	}
	return m_sections[sectionID];
}

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

G3BasePokemon::G3BasePokemon(Generation3* gen, G3BasePokemonData* data)
	: m_gen(gen)
	, m_data(new G3BasePokemonData(*data))
	, m_dirty(false)
{
	decrypt();
	setName(Generation3::gameTextToUTF8(m_data->name, 10));
	setOtName(Generation3::gameTextToUTF8(m_data->otName, 7));
}

PokemonSpecies* G3BasePokemon::species() const {
	unsigned unmappedId = m_data->growth()->species;
	if (unmappedId < sizeof(idMapping) / sizeof(*idMapping)) {
		return m_gen->species(idMapping[unmappedId]);
	}
	return m_gen->species(PokemonSpecies::MISSINGNO);
}

uint16_t G3BasePokemon::otId() const {
	return m_data->otId & 0xFFFF;
}

uint16_t G3BasePokemon::otSecretId() const {
	return m_data->otId >> 16;
}

bool G3BasePokemon::shiny() const {
	return (otId() ^ otSecretId() ^ (m_data->personality >> 16) ^ (m_data->personality & 0xFFFF)) < 8;
}

Pokemon::Nature G3BasePokemon::nature() const {
	return static_cast<Nature>(m_data->personality % 25);
}

unsigned G3BasePokemon::xp() const {
	return m_data->growth()->xp;
}

Type G3BasePokemon::type1() const {
	return species()->type1();
}

Type G3BasePokemon::type2() const {
	return species()->type2();
}

unsigned G3BasePokemon::currentHp() const {
	return maxHp();
}

unsigned G3BasePokemon::maxHp() const {
	return ((ivHp() + species()->baseHp() * 2 + evHp() / 4 + 100) * level()) / 100 + 10;
}

unsigned G3BasePokemon::attack() const {
	switch (nature()) {
	case LONELY:
	case BRAVE:
	case ADAMANT:
	case NAUGHTY:
		return stat(ivAttack(), species()->baseAttack(), evAttack(), 1);
	case BOLD:
	case TIMID:
	case MODEST:
	case CALM:
		return stat(ivAttack(), species()->baseAttack(), evAttack(), -1);
	default:
		return stat(ivAttack(), species()->baseAttack(), evAttack(), 0);
	}
}

unsigned G3BasePokemon::defense() const {
	switch (nature()) {
	case BOLD:
	case RELAXED:
	case IMPISH:
	case LAX:
		return stat(ivDefense(), species()->baseDefense(), evDefense(), 1);
	case LONELY:
	case HASTY:
	case MILD:
	case GENTLE:
		return stat(ivDefense(), species()->baseDefense(), evDefense(), -1);
	default:
		return stat(ivDefense(), species()->baseDefense(), evDefense(), 0);
	}
}

unsigned G3BasePokemon::speed() const {
	switch (nature()) {
	case TIMID:
	case HASTY:
	case JOLLY:
	case NAIVE:
		return stat(ivSpeed(), species()->baseSpeed(), evSpeed(), 1);
	case BRAVE:
	case RELAXED:
	case QUIET:
	case SASSY:
		return stat(ivSpeed(), species()->baseSpeed(), evSpeed(), -1);
	default:
		return stat(ivSpeed(), species()->baseSpeed(), evSpeed(), 0);
	}
}

unsigned G3BasePokemon::specialAttack() const {
	switch (nature()) {
	case MODEST:
	case MILD:
	case QUIET:
	case RASH:
		return stat(ivSpecialAttack(), species()->baseSpecialAttack(), evSpecialAttack(), 1);
	case ADAMANT:
	case IMPISH:
	case JOLLY:
	case CAREFUL:
		return stat(ivSpecialAttack(), species()->baseSpecialAttack(), evSpecialAttack(), -1);
	default:
		return stat(ivSpecialAttack(), species()->baseSpecialAttack(), evSpecialAttack(), 0);
	}
}

unsigned G3BasePokemon::specialDefense() const {
	switch (nature()) {
	case CALM:
	case GENTLE:
	case SASSY:
	case CAREFUL:
		return stat(ivSpecialDefense(), species()->baseSpecialDefense(), evSpecialDefense(), 1);
	case NAUGHTY:
	case LAX:
	case NAIVE:
	case RASH:
		return stat(ivSpecialDefense(), species()->baseSpecialDefense(), evSpecialDefense(), -1);
	default:
		return stat(ivSpecialDefense(), species()->baseSpecialDefense(), evSpecialDefense(), 0);
	}
}

unsigned G3BasePokemon::ivHp() const {
	return m_data->misc()->ivHp;
}

unsigned G3BasePokemon::ivAttack() const {
	return m_data->misc()->ivAttack;
}

unsigned G3BasePokemon::ivDefense() const {
	return m_data->misc()->ivDefense;
}

unsigned G3BasePokemon::ivSpeed() const {
	return m_data->misc()->ivSpeed;
}

unsigned G3BasePokemon::ivSpecialAttack() const {
	return m_data->misc()->ivSpecialAttack;
}

unsigned G3BasePokemon::ivSpecialDefense() const {
	return m_data->misc()->ivSpecialDefense;
}

unsigned G3BasePokemon::evHp() const {
	return m_data->evs()->hp;
}

unsigned G3BasePokemon::evAttack() const {
	return m_data->evs()->attack;
}

unsigned G3BasePokemon::evDefense() const {
	return m_data->evs()->defense;
}

unsigned G3BasePokemon::evSpeed() const {
	return m_data->evs()->speed;
}

unsigned G3BasePokemon::evSpecialAttack() const {
	return m_data->evs()->specialAttack;
}

unsigned G3BasePokemon::evSpecialDefense() const {
	return m_data->evs()->specialDefense;
}

unsigned G3BasePokemon::move1() const {
	return m_data->attacks()->moves[0];
}

unsigned G3BasePokemon::move2() const {
	return m_data->attacks()->moves[1];
}

unsigned G3BasePokemon::move3() const {
	return m_data->attacks()->moves[2];
}

unsigned G3BasePokemon::move4() const {
	return m_data->attacks()->moves[3];
}

void G3BasePokemon::setOtId(uint16_t id) {
	m_data->otId &= ~0xFFFF;
	m_data->otId |= id;
}

void G3BasePokemon::setOtSecretId(uint16_t id) {
	m_data->otId &= ~0xFFFF0000;
	m_data->otId |= id << 16;
}

void G3BasePokemon::setIvHp(unsigned iv) {
	m_data->misc()->ivHp = iv;
}

void G3BasePokemon::setIvAttack(unsigned iv) {
	m_data->misc()->ivAttack = iv;
}

void G3BasePokemon::setIvDefense(unsigned iv) {
	m_data->misc()->ivDefense = iv;
}

void G3BasePokemon::setIvSpeed(unsigned iv) {
	m_data->misc()->ivSpeed = iv;
}

void G3BasePokemon::setIvSpecialAttack(unsigned iv) {
	m_data->misc()->ivSpecialAttack = iv;
}

void G3BasePokemon::setIvSpecialDefense(unsigned iv) {
	m_data->misc()->ivSpecialDefense = iv;
}

unsigned G3BasePokemon::stat(unsigned iv, unsigned base, unsigned ev, int nature) const {
	return (((iv + base * 2 + ev / 4) * level()) / 100 + 5) * (1.f + (nature / 10.f));
}

void G3BasePokemon::decrypt() {
	if (m_dirty) {
		return;
	}
	m_dirty = true;
	uint32_t key = m_data->otId ^ m_data->personality;
	for (int i = 0; i < 3; ++i) {
		m_data->data.f0.raw[i] ^= key;
		m_data->data.f1.raw[i] ^= key;
		m_data->data.f2.raw[i] ^= key;
		m_data->data.f3.raw[i] ^= key;
	}
}

uint8_t G3BasePokemon::genderDeterminer() const {
	return m_data->personality & 0xFF;
}

G3PartyPokemon::G3PartyPokemon(Generation3* gen, uint8_t* data)
	: G3BasePokemon(gen, reinterpret_cast<G3BasePokemonData*>(data))
	, m_data(reinterpret_cast<G3PartyPokemonData*>(data))
{
}

unsigned G3PartyPokemon::level() const {
	return m_data->level;
}

unsigned G3PartyPokemon::currentHp() const {
	return m_data->currentHp;
}

unsigned G3PartyPokemon::maxHp() const {
	return m_data->maxHp;
}

unsigned G3PartyPokemon::attack() const {
	return m_data->attack;
}

unsigned G3PartyPokemon::defense() const {
	return m_data->defense;
}

unsigned G3PartyPokemon::speed() const {
	return m_data->speed;
}

unsigned G3PartyPokemon::specialAttack() const {
	return m_data->specialAttack;
}

unsigned G3PartyPokemon::specialDefense() const {
	return m_data->specialDefense;
}

template <>
PokemonSpecies::Id GenericPokemonSpecies<G3PokemonBaseStats>::id() const {
	return PokemonSpecies::MISSINGNO;
}

G3PokemonSpecies::G3PokemonSpecies(const G3PokemonBaseStats* data, PokemonSpecies::Id id)
	: GenericPokemonSpecies<G3PokemonBaseStats>(data)
	, m_id(id)
{
}

PokemonSpecies::Id G3PokemonSpecies::id() const {
	return m_id;
}

Type G3PokemonSpecies::mapType(unsigned unmapped) const {
	return typeMapping[static_cast<uint8_t>(unmapped)];
}

G3Party::G3Party(Generation3* gen)
	: m_gen(gen)
	, m_start(&gen->section(Generation3::Section::BAG)->data[G30E_PARTY_POKEMON])
{
}

std::unique_ptr<Pokemon> G3Party::at(unsigned i) {
	if (i >= length()) {
		return nullptr;
	}
	uint8_t* pstart = &m_start[4 + sizeof(G3PartyPokemonData) * i];
	return std::unique_ptr<Pokemon>(new G3PartyPokemon(m_gen, pstart));
}

unsigned G3Party::length() const {
	return m_start[0];
}

G3Box::G3Box(Generation3* gen, G3BasePokemonData* start)
	: m_gen(gen)
	, m_start(start)
{
}

std::unique_ptr<Pokemon> G3Box::at(unsigned i) {
	if (i >= length()) {
		return nullptr;
	}
	G3BasePokemonData* data = &m_start[i];
	if (data->checksum == 0) {
		return nullptr;
	}
	return std::unique_ptr<Pokemon>(new G3BasePokemon(m_gen, data));
}

unsigned G3Box::length() const {
	return G3_POKEMON_PER_BOX;
}
