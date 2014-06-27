Tachyon
=======
Tachyon is a tool for manipulating Pokémon within save games of Pokémon games in Generations I - III. It was created with the intent of being able to transfer Pokémon between save games, especially cross-generation, but it has evolved into a general save game viewer and editor. It is still relatively early into development, and not all features are currently implemented.

Tachyon is licensed under the 2-clause BSD license. See the COPYING file for more information. Please note that, to avoid copyright concerns involved with bundling resources, a ROM for the version associated with the save game is required. All of the resources necessary for Tachyon to run are extracted from the ROM. In the future, Tachyon will have the ability to extract all of the resources it needs into a stripped-down data structure that may be possible to distribute under Fair Use.

Also in planning is a hardware tool that will allow Game Boy and Game Boy Advance cartridges to be inserted for dumping the ROM and save games, along with injecting modified save games.

Supported games
---------------

Most games are currently only partially supported. All games are intended to have full support in all of their release localizations. However, not all are supported yet.

### Key

- E: English
- F: French
- G: German
- I: Italian
- J: Japanese
- K: Korean
- S: Spanish

### Game List

- Generation 1 (Full: EFGIJS)
	- Pokémon Red
	- Pokémon Blue
	- Pokémon Green
	- Pokémon Yellow
- Generation 2
	- Pokémon Gold (Full: E, Partial: FGIJS, Missing: K)
	- Pokémon Silver (Partial: EJG, Missing: FIKS)
	- Pokémon Crystal (Partial: E, Missing: FGIJKS)
- Generation 3
	- Pokémon Ruby (Partial: E, Missing: FGIJS)
	- Pokémon Sapphire (Partial: E, Missing: FGIJS)
	- Pokémon Emerald (Missing: EFGIJS)
	- Pokémon FireRed (Partial: E, Missing: FGIJS)
	- Pokémon LeafGreen (Missing: EFGIJS)

Phases
------
The development of Tachyon is separated into "phases". Each phase represents a major, distinct chunk of what Tachyon is intended to do. The phases are as follows:

1. Parse save games for generations I - III
2. Have a GUI for viewing save game Pokémon
3. Freeform Pokémon and box editing and conversion
4. A hardware layer for interacting with physical cartridges
5. A tiny GUI appropriate for using on low-resolution touch screens
6. Save game support for generations IV and V
7. DS homebrew for modifying generation III - V save games

Of note is that phases 4 and 5 are for a hardware component, and phases 6 and 7 are long-term goals if the earlier phases pan out. More phases may be added for further games or projects.

Things to be done
-----------------
Phases 1 - 3 are currently in heavy development, and as a result many things are currently missing or only partially complete. Even this list is incomplete.

### Missing features

- Editing individual Pokémon is currently unsupported
- Pokémon transfers are limited to within the same generation
- Stripped down ROM creation is not currently implemented
- Many regions or versions are currently unsupported
- Friendship is currently unsupported
- Held items are currently unsupported
- Abilities in Generation III are currently unsupported
- Power Points are currently unsupported
- Glitch Pokémon are not currently handled correctly
- Loading of Pokémon, Move and Nature names from the games

### Implementation details
- Change huge enums of offsets and switch statements to structs that contain all of the relevant constants per game (done for Generations I and II)
- Make types a bit more consistent (e.g., unsigned vs. size_t)
- Big-endian platforms are not currently supported, although it's questionable if this matters

Credits and Links
-----------------

The main implementation was done by Archaemic.

- [ptxn](http://ptxn.tumblr.com) is a development blog that can be found on tumblr
- Twitter: [@Archaemic](http://twitter.com/archaemic) 

Many resources were used as reference material:

- [Bulbapedia](http://bulbapedia.bulbagarden.net) contains lots of useful resources and documentation on Generations I - III
- [Data Crystal](http://datacrystal.romhacking.net) has useful offsets into the ROMs for generations I - III
- The [Pokémon Red disassembly](https://github.com/iimarckus/pokered) project provided finer implementation details and offsets for Generation I
- Some [Pokémon reverse engineering tools](https://github.com/kanzure/pokemon-reverse-engineering-tools) proved useful for figuring out how to decompress sprites in Generations I and II
- Technical documentation on the [Game Boy](http://nocash.emubase.de/pandocs.htm) and the [Game Boy Advance](http://nocash.emubase.de/gbatek.htm) provided by Martin Korth were also invaluable
- The people behind [veekun](http://veekun.com) are quite good at pointing the way towards useful resources
