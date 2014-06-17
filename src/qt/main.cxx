#include <QApplication>

#include "gen1/Generation1.h"
#include "gen2/Generation2.h"
#include "gen3/Generation3.h"

#include "Cartridge.h"
#include "GameRegistry.h"
#include "GameRegistryView.h"
#include "PokemonSelector.h"

int main(int argc, char** argv) {
	Generation1::registerLoader();
	Generation2::registerLoader();
	Generation3::registerLoader();

	QApplication app(argc, argv);

	GameRegistry registry;
	registry.addRom("game.bin");

	GameRegistryView registryView;
	registryView.setRegistry(&registry);
	registryView.show();

	return app.exec();
}
