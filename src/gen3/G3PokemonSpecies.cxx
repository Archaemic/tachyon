#include "gen3/G3PokemonSpecies.h"

#include "gen3/Generation3.h"

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

const PokemonSpecies::Id G3PokemonSpecies::idMapping[] = {
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

enum {
	G30E_RUBY_FRONT_SPRITE_MAPPING = 0x1E8354,
	G30E_SAPPHIRE_FRONT_SPRITE_MAPPING = 0x1E82E4,
	G32E_FIRE_RED_FRONT_SPRITE_MAPPING = 0x2350AC,

	G30E_RUBY_PALETTE_MAPPING = 0x1EA5B4,
	G30E_SAPPHIRE_PALETTE_MAPPING = 0x1EA544,
	G32E_FIRE_RED_PALETTE_MAPPING = 0x23730C,

	G30E_RUBY_SHINY_PALETTE_MAPPING = 0x1EB374,
	G30E_SAPPHIRE_SHINY_PALETTE_MAPPING = 0x1EB304,
	G32E_FIRE_RED_SHINY_PALETTE_MAPPING = 0x2380CC,
};

template <>
PokemonSpecies::Id GenericPokemonSpecies<G3PokemonBaseStats>::id() const {
	return PokemonSpecies::MISSINGNO;
}

G3PokemonSpecies::G3PokemonSpecies(const Generation3* gen, const G3PokemonBaseStats* data, PokemonSpecies::Id id, PokemonSpecies::Forme forme)
	: GenericPokemonSpecies<G3PokemonBaseStats>(data)
	, m_gen(gen)
	, m_id(id)
	, m_forme(forme)
{
	loadSprites();
}

void G3PokemonSpecies::loadSprites() {
	if (id() > PokemonSpecies::DEOXYS) {
		return;
	}

	unsigned gameId;
	if (id() != PokemonSpecies::UNOWN || !m_forme) {
		gameId = Generation3::reverseIdMapping[id()];
	} else {
		gameId = G3PokemonSpecies::UNOWN_BASE + m_forme - 1;
	}
	struct Mapping {
		uint32_t pointer;
		uint16_t unknown;
		uint16_t id;
	};

	const Mapping* spriteMapping;
	const Mapping* paletteMapping;
	const Mapping* shinyPaletteMapping;

	switch (m_gen->version()) {
	case Game::G30E_RUBY:
		spriteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G30E_RUBY_FRONT_SPRITE_MAPPING]);
		paletteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G30E_RUBY_PALETTE_MAPPING]);
		shinyPaletteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G30E_RUBY_SHINY_PALETTE_MAPPING]);
		break;
	case Game::G30E_SAPPHIRE:
		spriteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G30E_SAPPHIRE_FRONT_SPRITE_MAPPING]);
		paletteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G30E_SAPPHIRE_PALETTE_MAPPING]);
		shinyPaletteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G30E_SAPPHIRE_SHINY_PALETTE_MAPPING]);
		break;
	case Game::G32E_FIRE_RED:
		spriteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G32E_FIRE_RED_FRONT_SPRITE_MAPPING]);
		paletteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G32E_FIRE_RED_PALETTE_MAPPING]);
		shinyPaletteMapping = reinterpret_cast<const Mapping*>(&m_gen->rom()[G32E_FIRE_RED_SHINY_PALETTE_MAPPING]);
		break;
	default:
		return;
	}
	spriteMapping += gameId;
	paletteMapping += gameId;
	shinyPaletteMapping += gameId;

	uint8_t* rawSpriteData = new uint8_t[64 * 32];
	uint8_t* spriteData = new uint8_t[64 * 32];
	uint16_t* paletteData = new uint16_t[16];
	uint16_t* shinyPaletteData = new uint16_t[16];

	const uint8_t* spritePointer = &m_gen->rom()[spriteMapping->pointer & (Generation3::SIZE_ROM - 1)];
	const uint8_t* palettePointer = &m_gen->rom()[paletteMapping->pointer & (Generation3::SIZE_ROM - 1)];
	const uint8_t* shinyPalettePointer = &m_gen->rom()[shinyPaletteMapping->pointer & (Generation3::SIZE_ROM - 1)];

	Generation3::lz77Decompress(spritePointer, rawSpriteData, 64 * 32);
	Generation3::lz77Decompress(palettePointer, reinterpret_cast<uint8_t*>(paletteData), 32);
	Generation3::lz77Decompress(shinyPalettePointer, reinterpret_cast<uint8_t*>(shinyPaletteData), 32);

	for (unsigned tile = 0; tile < 64; ++tile) {
		for (unsigned y = 0; y < 8; ++y) {
			reinterpret_cast<uint32_t*>(spriteData)[y * 8 + (tile & 7) + (tile >> 3) * 64] = reinterpret_cast<uint32_t*>(rawSpriteData)[y + tile * 8];
		}
	}

	delete [] rawSpriteData;

	MultipaletteSprite* sprite = new MultipaletteSprite(64, 64, spriteData, paletteData, Sprite::GBA_4);
	sprite->addPalette(shinyPaletteData);
	m_frontSprite = std::unique_ptr<MultipaletteSprite>(sprite);
}

PokemonSpecies::Id G3PokemonSpecies::id() const {
	return m_id;
}

PokemonSpecies::Forme G3PokemonSpecies::forme() const {
	return m_forme;
}

const MultipaletteSprite* G3PokemonSpecies::frontSprite() const {
	return m_frontSprite.get();
}

Type G3PokemonSpecies::mapType(unsigned unmapped) const {
	return typeMapping[static_cast<uint8_t>(unmapped)];
}
