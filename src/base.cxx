#include "base.h"

#include <cmath>
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

const static wchar_t* moveNames[] = {
	L"---",
	L"Pound",
	L"Karate Chop",
	L"Double Slap",
	L"Comet Punch",
	L"Mega Punch",
	L"Pay Day",
	L"Fire Punch",
	L"Ice Punch",
	L"Thunder Punch",
	L"Scratch",
	L"Vice Grip",
	L"Guillotine",
	L"Razor Wind",
	L"Swords Dance",
	L"Cut",
	L"Gust",
	L"Wing Attack",
	L"Whirlwind",
	L"Fly",
	L"Bind",
	L"Slam",
	L"Vine Whip",
	L"Stomp",
	L"Double Kick",
	L"Mega Kick",
	L"Jump Kick",
	L"Rolling Kick",
	L"Sand Attack",
	L"Headbutt",
	L"Horn Attack",
	L"Fury Attack",
	L"Horn Drill",
	L"Tackle",
	L"Body Slam",
	L"Wrap",
	L"Take Down",
	L"Thrash",
	L"Double-Edge",
	L"Tail Whip",
	L"Poison Sting",
	L"Twineedle",
	L"Pin Missile",
	L"Leer",
	L"Bite",
	L"Growl",
	L"Roar",
	L"Sing",
	L"Supersonic",
	L"Sonic Boom",
	L"Disable",
	L"Acid",
	L"Ember",
	L"Flamethrower",
	L"Mist",
	L"Water Gun",
	L"Hydro Pump",
	L"Surf",
	L"Ice Beam",
	L"Blizzard",
	L"Psybeam",
	L"Bubble Beam",
	L"Aurora Beam",
	L"Hyper Beam",
	L"Peck",
	L"Drill Peck",
	L"Submission",
	L"Low Kick",
	L"Counter",
	L"Seismic Toss",
	L"Strength",
	L"Absorb",
	L"Mega Drain",
	L"Leech Seed",
	L"Growth",
	L"Razor Leaf",
	L"Solar Beam",
	L"Poison Powder",
	L"Stun Spore",
	L"Sleep Powder",
	L"Petal Dance",
	L"String Shot",
	L"Dragon Rage",
	L"Fire Spin",
	L"Thunder Shock",
	L"Thunderbolt",
	L"Thunder Wave",
	L"Thunder",
	L"Rock Throw",
	L"Earthquake",
	L"Fissure",
	L"Dig",
	L"Toxic",
	L"Confusion",
	L"Psychic",
	L"Hypnosis",
	L"Meditate",
	L"Agility",
	L"Quick Attack",
	L"Rage",
	L"Teleport",
	L"Night Shade",
	L"Mimic",
	L"Screech",
	L"Double Team",
	L"Recover",
	L"Harden",
	L"Minimize",
	L"Smokescreen",
	L"Confuse Ray",
	L"Withdraw",
	L"Defense Curl",
	L"Barrier",
	L"Light Screen",
	L"Haze",
	L"Reflect",
	L"Focus Energy",
	L"Bide",
	L"Metronome",
	L"Mirror Move",
	L"Self-Destruct",
	L"Egg Bomb",
	L"Lick",
	L"Smog",
	L"Sludge",
	L"Bone Club",
	L"Fire Blast",
	L"Waterfall",
	L"Clamp",
	L"Swift",
	L"Skull Bash",
	L"Spike Cannon",
	L"Constrict",
	L"Amnesia",
	L"Kinesis",
	L"Soft-Boiled",
	L"High Jump Kick",
	L"Glare",
	L"Dream Eater",
	L"Poison Gas",
	L"Barrage",
	L"Leech Life",
	L"Lovely Kiss",
	L"Sky Attack",
	L"Transform",
	L"Bubble",
	L"Dizzy Punch",
	L"Spore",
	L"Flash",
	L"Psywave",
	L"Splash",
	L"Acid Armor",
	L"Crabhammer",
	L"Explosion",
	L"Fury Swipes",
	L"Bonemerang",
	L"Rest",
	L"Rock Slide",
	L"Hyper Fang",
	L"Sharpen",
	L"Conversion",
	L"Tri Attack",
	L"Super Fang",
	L"Slash",
	L"Substitute",
	L"Struggle",
	L"Sketch",
	L"Triple Kick",
	L"Thief",
	L"Spider Web",
	L"Mind Reader",
	L"Nightmare",
	L"Flame Wheel",
	L"Snore",
	L"Curse",
	L"Flail",
	L"Conversion 2",
	L"Aeroblast",
	L"Cotton Spore",
	L"Reversal",
	L"Spite",
	L"Powder Snow",
	L"Protect",
	L"Mach Punch",
	L"Scary Face",
	L"Feint Attack",
	L"Sweet Kiss",
	L"Belly Drum",
	L"Sludge Bomb",
	L"Mud-Slap",
	L"Octazooka",
	L"Spikes",
	L"Zap Cannon",
	L"Foresight",
	L"Destiny Bond",
	L"Perish Song",
	L"Icy Wind",
	L"Detect",
	L"Bone Rush",
	L"Lock-On",
	L"Outrage",
	L"Sandstorm",
	L"Giga Drain",
	L"Endure",
	L"Charm",
	L"Rollout",
	L"False Swipe",
	L"Swagger",
	L"Milk Drink",
	L"Spark",
	L"Fury Cutter",
	L"Steel Wing",
	L"Mean Look",
	L"Attract",
	L"Sleep Talk",
	L"Heal Bell",
	L"Return",
	L"Present",
	L"Frustration",
	L"Safeguard",
	L"Pain Split",
	L"Sacred Fire",
	L"Magnitude",
	L"Dynamic Punch",
	L"Megahorn",
	L"Dragon Breath",
	L"Baton Pass",
	L"Encore",
	L"Pursuit",
	L"Rapid Spin",
	L"Sweet Scent",
	L"Iron Tail",
	L"Metal Claw",
	L"Vital Throw",
	L"Morning Sun",
	L"Synthesis",
	L"Moonlight",
	L"Hidden Power",
	L"Cross Chop",
	L"Twister",
	L"Rain Dance",
	L"Sunny Day",
	L"Crunch",
	L"Mirror Coat",
	L"Psych Up",
	L"Extreme Speed",
	L"Ancient Power",
	L"Shadow Ball",
	L"Future Sight",
	L"Rock Smash",
	L"Whirlpool",
	L"Beat Up",
	L"Fake Out",
	L"Uproar",
	L"Stockpile",
	L"Spit Up",
	L"Swallow",
	L"Heat Wave",
	L"Hail",
	L"Torment",
	L"Flatter",
	L"Will-O-Wisp",
	L"Memento",
	L"Facade",
	L"Focus Punch",
	L"Smelling Salts",
	L"Follow Me",
	L"Nature Power",
	L"Charge",
	L"Taunt",
	L"Helping Hand",
	L"Trick",
	L"Role Play",
	L"Wish",
	L"Assist",
	L"Ingrain",
	L"Superpower",
	L"Magic Coat",
	L"Recycle",
	L"Revenge",
	L"Brick Break",
	L"Yawn",
	L"Knock Off",
	L"Endeavor",
	L"Eruption",
	L"Skill Swap",
	L"Imprison",
	L"Refresh",
	L"Grudge",
	L"Snatch",
	L"Secret Power",
	L"Dive",
	L"Arm Thrust",
	L"Camouflage",
	L"Tail Glow",
	L"Luster Purge",
	L"Mist Ball",
	L"Feather Dance",
	L"Teeter Dance",
	L"Blaze Kick",
	L"Mud Sport",
	L"Ice Ball",
	L"Needle Arm",
	L"Slack Off",
	L"Hyper Voice",
	L"Poison Fang",
	L"Crush Claw",
	L"Blast Burn",
	L"Hydro Cannon",
	L"Meteor Mash",
	L"Astonish",
	L"Weather Ball",
	L"Aromatherapy",
	L"Fake Tears",
	L"Air Cutter",
	L"Overheat",
	L"Odor Sleuth",
	L"Rock Tomb",
	L"Silver Wind",
	L"Metal Sound",
	L"Grass Whistle",
	L"Tickle",
	L"Cosmic Power",
	L"Water Spout",
	L"Signal Beam",
	L"Shadow Punch",
	L"Extrasensory",
	L"Sky Uppercut",
	L"Sand Tomb",
	L"Sheer Cold",
	L"Muddy Water",
	L"Bullet Seed",
	L"Aerial Ace",
	L"Icicle Spear",
	L"Iron Defense",
	L"Block",
	L"Howl",
	L"Dragon Claw",
	L"Frenzy Plant",
	L"Bulk Up",
	L"Bounce",
	L"Mud Shot",
	L"Poison Tail",
	L"Covet",
	L"Volt Tackle",
	L"Magical Leaf",
	L"Water Sport",
	L"Calm Mind",
	L"Leaf Blade",
	L"Dragon Dance",
	L"Rock Blast",
	L"Shock Wave",
	L"Water Pulse",
	L"Doom Desire",
	L"Psycho Boost"
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

const wchar_t* MoveReadable(unsigned move) {
	const wchar_t* readable = nullptr;
	if (move < sizeof(moveNames) / sizeof(*moveNames)) {
		readable = moveNames[move];
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

unsigned Pokemon::level() const {
	return m_impl->level();
}

unsigned Pokemon::maxHp() const {
	return m_impl->maxHp();
}

unsigned Pokemon::attack() const {
	return m_impl->attack();
}

unsigned Pokemon::defense() const {
	return m_impl->defense();
}

unsigned Pokemon::speed() const {
	return m_impl->speed();
}

unsigned Pokemon::specialAttack() const {
	return m_impl->specialAttack();
}

unsigned Pokemon::specialDefense() const {
	return m_impl->specialDefense();
}

unsigned Pokemon::ivHp() const {
	return m_impl->ivHp();
}

unsigned Pokemon::ivAttack() const {
	return m_impl->ivAttack();
}

unsigned Pokemon::ivDefense() const {
	return m_impl->ivDefense();
}

unsigned Pokemon::ivSpeed() const {
	return m_impl->ivSpeed();
}

unsigned Pokemon::ivSpecialAttack() const {
	return m_impl->ivSpecialAttack();
}

unsigned Pokemon::ivSpecialDefense() const {
	return m_impl->ivSpecialDefense();
}

unsigned Pokemon::evHp() const {
	return m_impl->evHp();
}

unsigned Pokemon::evAttack() const {
	return m_impl->evAttack();
}

unsigned Pokemon::evDefense() const {
	return m_impl->evDefense();
}

unsigned Pokemon::evSpeed() const {
	return m_impl->evSpeed();
}

unsigned Pokemon::evSpecialAttack() const {
	return m_impl->evSpecialAttack();
}

unsigned Pokemon::evSpecialDefense() const {
	return m_impl->evSpecialDefense();
}

unsigned Pokemon::move1() const {
	return m_impl->move1();
}

unsigned Pokemon::move2() const {
	return m_impl->move2();
}

unsigned Pokemon::move3() const {
	return m_impl->move3();
}

unsigned Pokemon::move4() const {
	return m_impl->move4();
}

unsigned PokemonImpl::level() const {
	switch (species().growthRate()) {
	case PokemonSpecies::LEVEL_FAST:
		for (unsigned i = 2; i <= 100; ++i) {
			unsigned xpNeeded = 4 * i * i * i / 5;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
	case PokemonSpecies::LEVEL_MEDIUM_FAST:
		for (unsigned i = 2; i <= 100; ++i) {
			unsigned xpNeeded = i * i * i;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
	case PokemonSpecies::LEVEL_MEDIUM_SLOW:
		// Complex roots make programmers sad
		for (unsigned i = 2; i <= 100; ++i) {
			unsigned xpNeeded = 6 * i * i * i / 5 - 15 * i * i + 100 * i - 140;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
	case PokemonSpecies::LEVEL_SLOW:
		for (unsigned i = 2; i <= 100; ++i) {
			unsigned xpNeeded = 5 * i * i * i / 4;
			if (xpNeeded > xp()) {
				return i - 1;
			}
		}
	}
	return 100;
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

unsigned PokemonSpecies::baseHp() const {
	return m_impl->baseHp();
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

PokemonSpecies::GrowthRate PokemonSpecies::growthRate() const {
	return m_impl->growthRate();
}

const wchar_t* PokemonSpecies::readable() const {
	return speciesNames[id()];
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
