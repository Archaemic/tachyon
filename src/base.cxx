#include "base.h"

#include <iostream>

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

const static wchar_t* speciesNames[] = {
	L"MissingNo.",
	L"Bulbasaur",
	L"Ivysaur",
	L"Venusaur",
	L"Charmander",
	L"Charmeleon",
	L"Charizard",
	L"Squirtle",
	L"Wartortle",
	L"Blastoise",
	L"Caterpie",
	L"Metapod",
	L"Butterfree",
	L"Weedle",
	L"Kakuna",
	L"Beedrill",
	L"Pidgey",
	L"Pidgeotto",
	L"Pidgeot",
	L"Rattata",
	L"Raticate",
	L"Spearow",
	L"Fearow",
	L"Ekans",
	L"Arbok",
	L"Pikachu",
	L"Raichu",
	L"Sandshrew",
	L"Sandslash",
	L"Nidoran♀",
	L"Nidorina",
	L"Nidoqueen",
	L"Nidoran♂",
	L"Nidorino",
	L"Nidoking",
	L"Clefairy",
	L"Clefable",
	L"Vulpix",
	L"Ninetales",
	L"Jigglypuff",
	L"Wigglytuff",
	L"Zubat",
	L"Golbat",
	L"Oddish",
	L"Gloom",
	L"Vileplume",
	L"Paras",
	L"Parasect",
	L"Venonat",
	L"Venomoth",
	L"Diglett",
	L"Dugtrio",
	L"Meowth",
	L"Persian",
	L"Psyduck",
	L"Golduck",
	L"Mankey",
	L"Primeape",
	L"Growlithe",
	L"Arcanine",
	L"Poliwag",
	L"Poliwhirl",
	L"Poliwrath",
	L"Abra",
	L"Kadabra",
	L"Alakazam",
	L"Machop",
	L"Machoke",
	L"Machamp",
	L"Bellsprout",
	L"Weepinbell",
	L"Victreebel",
	L"Tentacool",
	L"Tentacruel",
	L"Geodude",
	L"Graveler",
	L"Golem",
	L"Ponyta",
	L"Rapidash",
	L"Slowpoke",
	L"Slowbro",
	L"Magnemite",
	L"Magneton",
	L"Farfetch'd",
	L"Doduo",
	L"Dodrio",
	L"Seel",
	L"Dewgong",
	L"Grimer",
	L"Muk",
	L"Shellder",
	L"Cloyster",
	L"Gastly",
	L"Haunter",
	L"Gengar",
	L"Onix",
	L"Drowzee",
	L"Hypno",
	L"Krabby",
	L"Kingler",
	L"Voltorb",
	L"Electrode",
	L"Exeggcute",
	L"Exeggutor",
	L"Cubone",
	L"Marowak",
	L"Hitmonlee",
	L"Hitmonchan",
	L"Lickitung",
	L"Koffing",
	L"Weezing",
	L"Rhyhorn",
	L"Rhydon",
	L"Chansey",
	L"Tangela",
	L"Kangaskhan",
	L"Horsea",
	L"Seadra",
	L"Goldeen",
	L"Seaking",
	L"Staryu",
	L"Starmie",
	L"Mr. Mime",
	L"Scyther",
	L"Jynx",
	L"Electabuzz",
	L"Magmar",
	L"Pinsir",
	L"Tauros",
	L"Magikarp",
	L"Gyarados",
	L"Lapras",
	L"Ditto",
	L"Eevee",
	L"Vaporeon",
	L"Jolteon",
	L"Flareon",
	L"Porygon",
	L"Omanyte",
	L"Omastar",
	L"Kabuto",
	L"Kabutops",
	L"Aerodactyl",
	L"Snorlax",
	L"Articuno",
	L"Zapdos",
	L"Moltres",
	L"Dratini",
	L"Dragonair",
	L"Dragonite",
	L"Mewtwo",
	L"Mew",
	L"Chikorita",
	L"Bayleef",
	L"Meganium",
	L"Cyndaquil",
	L"Quilava",
	L"Typhlosion",
	L"Totodile",
	L"Croconaw",
	L"Feraligatr",
	L"Sentret",
	L"Furret",
	L"Hoothoot",
	L"Noctowl",
	L"Ledyba",
	L"Ledian",
	L"Spinarak",
	L"Ariados",
	L"Crobat",
	L"Chinchou",
	L"Lanturn",
	L"Pichu",
	L"Cleffa",
	L"Igglybuff",
	L"Togepi",
	L"Togetic",
	L"Natu",
	L"Xatu",
	L"Mareep",
	L"Flaaffy",
	L"Ampharos",
	L"Bellossom",
	L"Marill",
	L"Azumarill",
	L"Sudowoodo",
	L"Politoed",
	L"Hoppip",
	L"Skiploom",
	L"Jumpluff",
	L"Aipom",
	L"Sunkern",
	L"Sunflora",
	L"Yanma",
	L"Wooper",
	L"Quagsire",
	L"Espeon",
	L"Umbreon",
	L"Murkrow",
	L"Slowking",
	L"Misdreavus",
	L"Unown",
	L"Wobbuffet",
	L"Girafarig",
	L"Pineco",
	L"Forretress",
	L"Dunsparce",
	L"Gligar",
	L"Steelix",
	L"Snubbull",
	L"Granbull",
	L"Qwilfish",
	L"Scizor",
	L"Shuckle",
	L"Heracross",
	L"Sneasel",
	L"Teddiursa",
	L"Ursaring",
	L"Slugma",
	L"Magcargo",
	L"Swinub",
	L"Piloswine",
	L"Corsola",
	L"Remoraid",
	L"Octillery",
	L"Delibird",
	L"Mantine",
	L"Skarmory",
	L"Houndour",
	L"Houndoom",
	L"Kingdra",
	L"Phanpy",
	L"Donphan",
	L"Porygon2",
	L"Stantler",
	L"Smeargle",
	L"Tyrogue",
	L"Hitmontop",
	L"Smoochum",
	L"Elekid",
	L"Magby",
	L"Miltank",
	L"Blissey",
	L"Raikou",
	L"Entei",
	L"Suicune",
	L"Larvitar",
	L"Pupitar",
	L"Tyranitar",
	L"Lugia",
	L"Ho-oh",
	L"Celebi",
	L"Treecko",
	L"Grovyle",
	L"Sceptile",
	L"Torchic",
	L"Combusken",
	L"Blaziken",
	L"Mudkip",
	L"Marshtomp",
	L"Swampert",
	L"Poochyena",
	L"Mightyena",
	L"Zigzagoon",
	L"Linoone",
	L"Wurmple",
	L"Silcoon",
	L"Beautifly",
	L"Cascoon",
	L"Dustox",
	L"Lotad",
	L"Lombre",
	L"Ludicolo",
	L"Seedot",
	L"Nuzleaf",
	L"Shiftry",
	L"Taillow",
	L"Swellow",
	L"Wingull",
	L"Pelipper",
	L"Ralts",
	L"Kirlia",
	L"Gardevoir",
	L"Surskit",
	L"Masquerain",
	L"Shroomish",
	L"Breloom",
	L"Slakoth",
	L"Vigoroth",
	L"Slaking",
	L"Nincada",
	L"Ninjask",
	L"Shedinja",
	L"Whismur",
	L"Loudred",
	L"Exploud",
	L"Makuhita",
	L"Hariyama",
	L"Azurill",
	L"Nosepass",
	L"Skitty",
	L"Delcatty",
	L"Sableye",
	L"Mawile",
	L"Aron",
	L"Lairon",
	L"Aggron",
	L"Meditite",
	L"Medicham",
	L"Electrike",
	L"Manectric",
	L"Plusle",
	L"Minun",
	L"Volbeat",
	L"Illumise",
	L"Roselia",
	L"Gulpin",
	L"Swalot",
	L"Carvanha",
	L"Sharpedo",
	L"Wailmer",
	L"Wailord",
	L"Numel",
	L"Camerupt",
	L"Torkoal",
	L"Spoink",
	L"Grumpig",
	L"Spinda",
	L"Trapinch",
	L"Vibrava",
	L"Flygon",
	L"Cacnea",
	L"Cacturne",
	L"Swablu",
	L"Altaria",
	L"Zangoose",
	L"Seviper",
	L"Lunatone",
	L"Solrock",
	L"Barboach",
	L"Whiscash",
	L"Corphish",
	L"Crawdaunt",
	L"Baltoy",
	L"Claydol",
	L"Lileep",
	L"Cradily",
	L"Anorith",
	L"Armaldo",
	L"Feebas",
	L"Milotic",
	L"Castform",
	L"Kecleon",
	L"Shuppet",
	L"Banette",
	L"Duskull",
	L"Dusclops",
	L"Tropius",
	L"Chimecho",
	L"Absol",
	L"Wynaut",
	L"Snorunt",
	L"Glalie",
	L"Spheal",
	L"Sealeo",
	L"Walrein",
	L"Clamperl",
	L"Huntail",
	L"Gorebyss",
	L"Relicanth",
	L"Luvdisc",
	L"Bagon",
	L"Shelgon",
	L"Salamence",
	L"Beldum",
	L"Metang",
	L"Metagross",
	L"Regirock",
	L"Regice",
	L"Registeel",
	L"Latias",
	L"Latios",
	L"Kyogre",
	L"Groudon",
	L"Rayquaza",
	L"Jirachi",
	L"Deoxys"
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

Game::Game(uint8_t* memory, const uint8_t* rom)
	: m_memory(memory)
	, m_rom(rom)
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

PokemonSpecies Pokemon::species() const {
	return m_impl->species();
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

PokemonSpecies::PokemonSpecies(PokemonSpeciesImpl* impl)
	: m_impl(impl)
{
}

PokemonSpecies::PokemonSpecies(const PokemonSpecies& other)
	: m_impl(other.m_impl)
{
	m_impl->ref();
}

PokemonSpecies::~PokemonSpecies() {
	m_impl->deref();
}

PokemonSpecies::Id PokemonSpecies::id() const {
	return m_impl->id();
}

unsigned PokemonSpecies::baseAttack() const {
	return m_impl->baseAttack();
}

unsigned PokemonSpecies::baseDefense() const {
	return m_impl->baseDefense();
}

unsigned PokemonSpecies::baseSpeed() const {
	return m_impl->baseSpeed();
}

unsigned PokemonSpecies::baseSpecialAttack() const {
	return m_impl->baseSpecialAttack();
}

unsigned PokemonSpecies::baseSpecialDefense() const {
	return m_impl->baseSpecialDefense();
}

Type PokemonSpecies::type1() const {
	return m_impl->type1();
}

Type PokemonSpecies::type2() const {
	return m_impl->type2();
}

const wchar_t* PokemonSpecies::readable() const {
	return speciesNames[id()];
}

void Pokemon::enumerate() const {
	std::wcout << "\tName: " << name() << std::endl;
	std::wcout << "\tSpecies: " << species().readable() << " (" << species().id() << ")" << std::endl;
	std::wcout << "\tOT: " << otName() << " (" << otId() << ")" << std::endl;
	std::wcout << "\tExp: " << xp() << std::endl;
	std::wcout << "\tHP: " << currentHp() << std::endl;
	std::wcout << "\tType: " << TypeReadable(type1());
	if (type1() != type2()) {
		std::wcout << "/" << TypeReadable(type2());
	}
	std::wcout << std::endl;
}

RefCounted::RefCounted()
	: m_refs(1)
{
}

void RefCounted::ref() {
	++m_refs;
}

void RefCounted::deref() {
	--m_refs;

	if (m_refs == 0) {
		delete this;
	}
}
