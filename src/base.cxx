#include "base.h"

#include <cmath>
#include <iostream>

const static char* typeNames[] = {
	u8"???",
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
	u8"Normal",
	u8"Fighting",
	u8"Flying",
	u8"Poison",
	u8"Ground",
	u8"Rock",
	u8"Bug",
	u8"Ghost",
	u8"Steel",
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	u8"Fire",
	u8"Water",
	u8"Grass",
	u8"Electric",
	u8"Psychic",
	u8"Ice",
	u8"Dragon",
	u8"Dark",
};

const static char* speciesNames[] = {
	u8"MissingNo.",
	u8"Bulbasaur",
	u8"Ivysaur",
	u8"Venusaur",
	u8"Charmander",
	u8"Charmeleon",
	u8"Charizard",
	u8"Squirtle",
	u8"Wartortle",
	u8"Blastoise",
	u8"Caterpie",
	u8"Metapod",
	u8"Butterfree",
	u8"Weedle",
	u8"Kakuna",
	u8"Beedrill",
	u8"Pidgey",
	u8"Pidgeotto",
	u8"Pidgeot",
	u8"Rattata",
	u8"Raticate",
	u8"Spearow",
	u8"Fearow",
	u8"Ekans",
	u8"Arbok",
	u8"Pikachu",
	u8"Raichu",
	u8"Sandshrew",
	u8"Sandslash",
	u8"Nidoran♀",
	u8"Nidorina",
	u8"Nidoqueen",
	u8"Nidoran♂",
	u8"Nidorino",
	u8"Nidoking",
	u8"Clefairy",
	u8"Clefable",
	u8"Vulpix",
	u8"Ninetales",
	u8"Jigglypuff",
	u8"Wigglytuff",
	u8"Zubat",
	u8"Golbat",
	u8"Oddish",
	u8"Gloom",
	u8"Vileplume",
	u8"Paras",
	u8"Parasect",
	u8"Venonat",
	u8"Venomoth",
	u8"Diglett",
	u8"Dugtrio",
	u8"Meowth",
	u8"Persian",
	u8"Psyduck",
	u8"Golduck",
	u8"Mankey",
	u8"Primeape",
	u8"Growlithe",
	u8"Arcanine",
	u8"Poliwag",
	u8"Poliwhirl",
	u8"Poliwrath",
	u8"Abra",
	u8"Kadabra",
	u8"Alakazam",
	u8"Machop",
	u8"Machoke",
	u8"Machamp",
	u8"Bellsprout",
	u8"Weepinbell",
	u8"Victreebel",
	u8"Tentacool",
	u8"Tentacruel",
	u8"Geodude",
	u8"Graveler",
	u8"Golem",
	u8"Ponyta",
	u8"Rapidash",
	u8"Slowpoke",
	u8"Slowbro",
	u8"Magnemite",
	u8"Magneton",
	u8"Farfetch'd",
	u8"Doduo",
	u8"Dodrio",
	u8"Seel",
	u8"Dewgong",
	u8"Grimer",
	u8"Muk",
	u8"Shellder",
	u8"Cloyster",
	u8"Gastly",
	u8"Haunter",
	u8"Gengar",
	u8"Onix",
	u8"Drowzee",
	u8"Hypno",
	u8"Krabby",
	u8"Kingler",
	u8"Voltorb",
	u8"Electrode",
	u8"Exeggcute",
	u8"Exeggutor",
	u8"Cubone",
	u8"Marowak",
	u8"Hitmonlee",
	u8"Hitmonchan",
	u8"Lickitung",
	u8"Koffing",
	u8"Weezing",
	u8"Rhyhorn",
	u8"Rhydon",
	u8"Chansey",
	u8"Tangela",
	u8"Kangaskhan",
	u8"Horsea",
	u8"Seadra",
	u8"Goldeen",
	u8"Seaking",
	u8"Staryu",
	u8"Starmie",
	u8"Mr. Mime",
	u8"Scyther",
	u8"Jynx",
	u8"Electabuzz",
	u8"Magmar",
	u8"Pinsir",
	u8"Tauros",
	u8"Magikarp",
	u8"Gyarados",
	u8"Lapras",
	u8"Ditto",
	u8"Eevee",
	u8"Vaporeon",
	u8"Jolteon",
	u8"Flareon",
	u8"Porygon",
	u8"Omanyte",
	u8"Omastar",
	u8"Kabuto",
	u8"Kabutops",
	u8"Aerodactyl",
	u8"Snorlax",
	u8"Articuno",
	u8"Zapdos",
	u8"Moltres",
	u8"Dratini",
	u8"Dragonair",
	u8"Dragonite",
	u8"Mewtwo",
	u8"Mew",
	u8"Chikorita",
	u8"Bayleef",
	u8"Meganium",
	u8"Cyndaquil",
	u8"Quilava",
	u8"Typhlosion",
	u8"Totodile",
	u8"Croconaw",
	u8"Feraligatr",
	u8"Sentret",
	u8"Furret",
	u8"Hoothoot",
	u8"Noctowl",
	u8"Ledyba",
	u8"Ledian",
	u8"Spinarak",
	u8"Ariados",
	u8"Crobat",
	u8"Chinchou",
	u8"Lanturn",
	u8"Pichu",
	u8"Cleffa",
	u8"Igglybuff",
	u8"Togepi",
	u8"Togetic",
	u8"Natu",
	u8"Xatu",
	u8"Mareep",
	u8"Flaaffy",
	u8"Ampharos",
	u8"Bellossom",
	u8"Marill",
	u8"Azumarill",
	u8"Sudowoodo",
	u8"Politoed",
	u8"Hoppip",
	u8"Skiploom",
	u8"Jumpluff",
	u8"Aipom",
	u8"Sunkern",
	u8"Sunflora",
	u8"Yanma",
	u8"Wooper",
	u8"Quagsire",
	u8"Espeon",
	u8"Umbreon",
	u8"Murkrow",
	u8"Slowking",
	u8"Misdreavus",
	u8"Unown",
	u8"Wobbuffet",
	u8"Girafarig",
	u8"Pineco",
	u8"Forretress",
	u8"Dunsparce",
	u8"Gligar",
	u8"Steelix",
	u8"Snubbull",
	u8"Granbull",
	u8"Qwilfish",
	u8"Scizor",
	u8"Shuckle",
	u8"Heracross",
	u8"Sneasel",
	u8"Teddiursa",
	u8"Ursaring",
	u8"Slugma",
	u8"Magcargo",
	u8"Swinub",
	u8"Piloswine",
	u8"Corsola",
	u8"Remoraid",
	u8"Octillery",
	u8"Delibird",
	u8"Mantine",
	u8"Skarmory",
	u8"Houndour",
	u8"Houndoom",
	u8"Kingdra",
	u8"Phanpy",
	u8"Donphan",
	u8"Porygon2",
	u8"Stantler",
	u8"Smeargle",
	u8"Tyrogue",
	u8"Hitmontop",
	u8"Smoochum",
	u8"Elekid",
	u8"Magby",
	u8"Miltank",
	u8"Blissey",
	u8"Raikou",
	u8"Entei",
	u8"Suicune",
	u8"Larvitar",
	u8"Pupitar",
	u8"Tyranitar",
	u8"Lugia",
	u8"Ho-oh",
	u8"Celebi",
	u8"Treecko",
	u8"Grovyle",
	u8"Sceptile",
	u8"Torchic",
	u8"Combusken",
	u8"Blaziken",
	u8"Mudkip",
	u8"Marshtomp",
	u8"Swampert",
	u8"Poochyena",
	u8"Mightyena",
	u8"Zigzagoon",
	u8"Linoone",
	u8"Wurmple",
	u8"Silcoon",
	u8"Beautifly",
	u8"Cascoon",
	u8"Dustox",
	u8"Lotad",
	u8"Lombre",
	u8"Ludicolo",
	u8"Seedot",
	u8"Nuzleaf",
	u8"Shiftry",
	u8"Taillow",
	u8"Swellow",
	u8"Wingull",
	u8"Pelipper",
	u8"Ralts",
	u8"Kirlia",
	u8"Gardevoir",
	u8"Surskit",
	u8"Masquerain",
	u8"Shroomish",
	u8"Breloom",
	u8"Slakoth",
	u8"Vigoroth",
	u8"Slaking",
	u8"Nincada",
	u8"Ninjask",
	u8"Shedinja",
	u8"Whismur",
	u8"Loudred",
	u8"Exploud",
	u8"Makuhita",
	u8"Hariyama",
	u8"Azurill",
	u8"Nosepass",
	u8"Skitty",
	u8"Delcatty",
	u8"Sableye",
	u8"Mawile",
	u8"Aron",
	u8"Lairon",
	u8"Aggron",
	u8"Meditite",
	u8"Medicham",
	u8"Electrike",
	u8"Manectric",
	u8"Plusle",
	u8"Minun",
	u8"Volbeat",
	u8"Illumise",
	u8"Roselia",
	u8"Gulpin",
	u8"Swalot",
	u8"Carvanha",
	u8"Sharpedo",
	u8"Wailmer",
	u8"Wailord",
	u8"Numel",
	u8"Camerupt",
	u8"Torkoal",
	u8"Spoink",
	u8"Grumpig",
	u8"Spinda",
	u8"Trapinch",
	u8"Vibrava",
	u8"Flygon",
	u8"Cacnea",
	u8"Cacturne",
	u8"Swablu",
	u8"Altaria",
	u8"Zangoose",
	u8"Seviper",
	u8"Lunatone",
	u8"Solrock",
	u8"Barboach",
	u8"Whiscash",
	u8"Corphish",
	u8"Crawdaunt",
	u8"Baltoy",
	u8"Claydol",
	u8"Lileep",
	u8"Cradily",
	u8"Anorith",
	u8"Armaldo",
	u8"Feebas",
	u8"Milotic",
	u8"Castform",
	u8"Kecleon",
	u8"Shuppet",
	u8"Banette",
	u8"Duskull",
	u8"Dusclops",
	u8"Tropius",
	u8"Chimecho",
	u8"Absol",
	u8"Wynaut",
	u8"Snorunt",
	u8"Glalie",
	u8"Spheal",
	u8"Sealeo",
	u8"Walrein",
	u8"Clamperl",
	u8"Huntail",
	u8"Gorebyss",
	u8"Relicanth",
	u8"Luvdisc",
	u8"Bagon",
	u8"Shelgon",
	u8"Salamence",
	u8"Beldum",
	u8"Metang",
	u8"Metagross",
	u8"Regirock",
	u8"Regice",
	u8"Registeel",
	u8"Latias",
	u8"Latios",
	u8"Kyogre",
	u8"Groudon",
	u8"Rayquaza",
	u8"Jirachi",
	u8"Deoxys"
};

const static char* moveNames[] = {
	u8"---",
	u8"Pound",
	u8"Karate Chop",
	u8"Double Slap",
	u8"Comet Punch",
	u8"Mega Punch",
	u8"Pay Day",
	u8"Fire Punch",
	u8"Ice Punch",
	u8"Thunder Punch",
	u8"Scratch",
	u8"Vice Grip",
	u8"Guillotine",
	u8"Razor Wind",
	u8"Swords Dance",
	u8"Cut",
	u8"Gust",
	u8"Wing Attack",
	u8"Whirlwind",
	u8"Fly",
	u8"Bind",
	u8"Slam",
	u8"Vine Whip",
	u8"Stomp",
	u8"Double Kick",
	u8"Mega Kick",
	u8"Jump Kick",
	u8"Rolling Kick",
	u8"Sand Attack",
	u8"Headbutt",
	u8"Horn Attack",
	u8"Fury Attack",
	u8"Horn Drill",
	u8"Tackle",
	u8"Body Slam",
	u8"Wrap",
	u8"Take Down",
	u8"Thrash",
	u8"Double-Edge",
	u8"Tail Whip",
	u8"Poison Sting",
	u8"Twineedle",
	u8"Pin Missile",
	u8"Leer",
	u8"Bite",
	u8"Growl",
	u8"Roar",
	u8"Sing",
	u8"Supersonic",
	u8"Sonic Boom",
	u8"Disable",
	u8"Acid",
	u8"Ember",
	u8"Flamethrower",
	u8"Mist",
	u8"Water Gun",
	u8"Hydro Pump",
	u8"Surf",
	u8"Ice Beam",
	u8"Blizzard",
	u8"Psybeam",
	u8"Bubble Beam",
	u8"Aurora Beam",
	u8"Hyper Beam",
	u8"Peck",
	u8"Drill Peck",
	u8"Submission",
	u8"Low Kick",
	u8"Counter",
	u8"Seismic Toss",
	u8"Strength",
	u8"Absorb",
	u8"Mega Drain",
	u8"Leech Seed",
	u8"Growth",
	u8"Razor Leaf",
	u8"Solar Beam",
	u8"Poison Powder",
	u8"Stun Spore",
	u8"Sleep Powder",
	u8"Petal Dance",
	u8"String Shot",
	u8"Dragon Rage",
	u8"Fire Spin",
	u8"Thunder Shock",
	u8"Thunderbolt",
	u8"Thunder Wave",
	u8"Thunder",
	u8"Rock Throw",
	u8"Earthquake",
	u8"Fissure",
	u8"Dig",
	u8"Toxic",
	u8"Confusion",
	u8"Psychic",
	u8"Hypnosis",
	u8"Meditate",
	u8"Agility",
	u8"Quick Attack",
	u8"Rage",
	u8"Teleport",
	u8"Night Shade",
	u8"Mimic",
	u8"Screech",
	u8"Double Team",
	u8"Recover",
	u8"Harden",
	u8"Minimize",
	u8"Smokescreen",
	u8"Confuse Ray",
	u8"Withdraw",
	u8"Defense Curl",
	u8"Barrier",
	u8"Light Screen",
	u8"Haze",
	u8"Reflect",
	u8"Focus Energy",
	u8"Bide",
	u8"Metronome",
	u8"Mirror Move",
	u8"Self-Destruct",
	u8"Egg Bomb",
	u8"Lick",
	u8"Smog",
	u8"Sludge",
	u8"Bone Club",
	u8"Fire Blast",
	u8"Waterfall",
	u8"Clamp",
	u8"Swift",
	u8"Skull Bash",
	u8"Spike Cannon",
	u8"Constrict",
	u8"Amnesia",
	u8"Kinesis",
	u8"Soft-Boiled",
	u8"High Jump Kick",
	u8"Glare",
	u8"Dream Eater",
	u8"Poison Gas",
	u8"Barrage",
	u8"Leech Life",
	u8"Lovely Kiss",
	u8"Sky Attack",
	u8"Transform",
	u8"Bubble",
	u8"Dizzy Punch",
	u8"Spore",
	u8"Flash",
	u8"Psywave",
	u8"Splash",
	u8"Acid Armor",
	u8"Crabhammer",
	u8"Explosion",
	u8"Fury Swipes",
	u8"Bonemerang",
	u8"Rest",
	u8"Rock Slide",
	u8"Hyper Fang",
	u8"Sharpen",
	u8"Conversion",
	u8"Tri Attack",
	u8"Super Fang",
	u8"Slash",
	u8"Substitute",
	u8"Struggle",
	u8"Sketch",
	u8"Triple Kick",
	u8"Thief",
	u8"Spider Web",
	u8"Mind Reader",
	u8"Nightmare",
	u8"Flame Wheel",
	u8"Snore",
	u8"Curse",
	u8"Flail",
	u8"Conversion 2",
	u8"Aeroblast",
	u8"Cotton Spore",
	u8"Reversal",
	u8"Spite",
	u8"Powder Snow",
	u8"Protect",
	u8"Mach Punch",
	u8"Scary Face",
	u8"Feint Attack",
	u8"Sweet Kiss",
	u8"Belly Drum",
	u8"Sludge Bomb",
	u8"Mud-Slap",
	u8"Octazooka",
	u8"Spikes",
	u8"Zap Cannon",
	u8"Foresight",
	u8"Destiny Bond",
	u8"Perish Song",
	u8"Icy Wind",
	u8"Detect",
	u8"Bone Rush",
	u8"Lock-On",
	u8"Outrage",
	u8"Sandstorm",
	u8"Giga Drain",
	u8"Endure",
	u8"Charm",
	u8"Rollout",
	u8"False Swipe",
	u8"Swagger",
	u8"Milk Drink",
	u8"Spark",
	u8"Fury Cutter",
	u8"Steel Wing",
	u8"Mean Look",
	u8"Attract",
	u8"Sleep Talk",
	u8"Heal Bell",
	u8"Return",
	u8"Present",
	u8"Frustration",
	u8"Safeguard",
	u8"Pain Split",
	u8"Sacred Fire",
	u8"Magnitude",
	u8"Dynamic Punch",
	u8"Megahorn",
	u8"Dragon Breath",
	u8"Baton Pass",
	u8"Encore",
	u8"Pursuit",
	u8"Rapid Spin",
	u8"Sweet Scent",
	u8"Iron Tail",
	u8"Metal Claw",
	u8"Vital Throw",
	u8"Morning Sun",
	u8"Synthesis",
	u8"Moonlight",
	u8"Hidden Power",
	u8"Cross Chop",
	u8"Twister",
	u8"Rain Dance",
	u8"Sunny Day",
	u8"Crunch",
	u8"Mirror Coat",
	u8"Psych Up",
	u8"Extreme Speed",
	u8"Ancient Power",
	u8"Shadow Ball",
	u8"Future Sight",
	u8"Rock Smash",
	u8"Whirlpool",
	u8"Beat Up",
	u8"Fake Out",
	u8"Uproar",
	u8"Stockpile",
	u8"Spit Up",
	u8"Swallow",
	u8"Heat Wave",
	u8"Hail",
	u8"Torment",
	u8"Flatter",
	u8"Will-O-Wisp",
	u8"Memento",
	u8"Facade",
	u8"Focus Punch",
	u8"Smelling Salts",
	u8"Follow Me",
	u8"Nature Power",
	u8"Charge",
	u8"Taunt",
	u8"Helping Hand",
	u8"Trick",
	u8"Role Play",
	u8"Wish",
	u8"Assist",
	u8"Ingrain",
	u8"Superpower",
	u8"Magic Coat",
	u8"Recycle",
	u8"Revenge",
	u8"Brick Break",
	u8"Yawn",
	u8"Knock Off",
	u8"Endeavor",
	u8"Eruption",
	u8"Skill Swap",
	u8"Imprison",
	u8"Refresh",
	u8"Grudge",
	u8"Snatch",
	u8"Secret Power",
	u8"Dive",
	u8"Arm Thrust",
	u8"Camouflage",
	u8"Tail Glow",
	u8"Luster Purge",
	u8"Mist Ball",
	u8"Feather Dance",
	u8"Teeter Dance",
	u8"Blaze Kick",
	u8"Mud Sport",
	u8"Ice Ball",
	u8"Needle Arm",
	u8"Slack Off",
	u8"Hyper Voice",
	u8"Poison Fang",
	u8"Crush Claw",
	u8"Blast Burn",
	u8"Hydro Cannon",
	u8"Meteor Mash",
	u8"Astonish",
	u8"Weather Ball",
	u8"Aromatherapy",
	u8"Fake Tears",
	u8"Air Cutter",
	u8"Overheat",
	u8"Odor Sleuth",
	u8"Rock Tomb",
	u8"Silver Wind",
	u8"Metal Sound",
	u8"Grass Whistle",
	u8"Tickle",
	u8"Cosmic Power",
	u8"Water Spout",
	u8"Signal Beam",
	u8"Shadow Punch",
	u8"Extrasensory",
	u8"Sky Uppercut",
	u8"Sand Tomb",
	u8"Sheer Cold",
	u8"Muddy Water",
	u8"Bullet Seed",
	u8"Aerial Ace",
	u8"Icicle Spear",
	u8"Iron Defense",
	u8"Block",
	u8"Howl",
	u8"Dragon Claw",
	u8"Frenzy Plant",
	u8"Bulk Up",
	u8"Bounce",
	u8"Mud Shot",
	u8"Poison Tail",
	u8"Covet",
	u8"Volt Tackle",
	u8"Magical Leaf",
	u8"Water Sport",
	u8"Calm Mind",
	u8"Leaf Blade",
	u8"Dragon Dance",
	u8"Rock Blast",
	u8"Shock Wave",
	u8"Water Pulse",
	u8"Doom Desire",
	u8"Psycho Boost"
};

const char* TypeReadable(Type type) {
	const char* readable = nullptr;
	if (type <= DARK) {
		readable = typeNames[type];
	}
	if (!readable) {
		readable = u8"???";
	}
	return readable;
}

const char* MoveReadable(unsigned move) {
	const char* readable = nullptr;
	if (move < sizeof(moveNames) / sizeof(*moveNames)) {
		readable = moveNames[move];
	}
	if (!readable) {
		readable = u8"???";
	}
	return readable;
}

Game::Game(uint8_t* memory, const uint8_t* rom)
	: m_memory(memory)
	, m_rom(rom)
{
}

const std::string& Game::trainerName() const {
	return m_trainerName;
}

void Game::setTrainerName(const std::string& name) {
	m_trainerName = name;
}

PokemonSpecies* Game::species(PokemonSpecies::Id id) {
	return m_species[id].get();
}

void Game::putSpecies(PokemonSpecies::Id id, PokemonSpecies* species) {
	m_species[id] = std::unique_ptr<PokemonSpecies>(species);
}

unsigned Pokemon::level() const {
	switch (species()->growthRate()) {
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

const std::string& Pokemon::name() const {
	return m_name;
}

void Pokemon::setName(const std::string& name) {
	m_name = name;
}

const std::string& Pokemon::otName() const {
	return m_otName;
}

void Pokemon::setOtName(const std::string& otName) {
	m_otName = otName;
}


const char* PokemonSpecies::readable() const {
	return speciesNames[id()];
}
