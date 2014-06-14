#include <QApplication>

#include "gen1/Generation1.h"
#include "gen2/Generation2.h"
#include "gen3/Generation3.h"

#include "Cartridge.h"
#include "PokemonSelector.h"

int main(int argc, char** argv) {
	Generation1::registerLoader();
	Generation2::registerLoader();
	Generation3::registerLoader();

	QApplication app(argc, argv);
	PokemonSelector selector;

	Cartridge cart("game.bin", "test.sav");
	selector.load(&cart);
	selector.show();

	return app.exec();
}
