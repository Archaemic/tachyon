#include <QApplication>
#include <QTableView>

#include "common/Group.h"
#include "gen1/Generation1.h"
#include "gen2/Generation2.h"
#include "gen3/Generation3.h"

#include "Cartridge.h"
#include "PokemonTable.h"

int main(int argc, char** argv) {
	Generation1::registerLoader();
	Generation2::registerLoader();
	Generation3::registerLoader();

	QApplication app(argc, argv);
	PokemonTable table;
	QTableView view;
	Cartridge cart("game.bin", "test.sav");
	std::unique_ptr<Group> group = cart.game()->party();
	table.setGroup(group.get());
	view.setModel(&table);
	view.show();
	return app.exec();
}
