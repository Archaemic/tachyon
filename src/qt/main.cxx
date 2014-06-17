#include <QApplication>

#include "gen1/Generation1.h"
#include "gen2/Generation2.h"
#include "gen3/Generation3.h"

#include "Cartridge.h"
#include "GameRegistry.h"
#include "GameRegistryView.h"
#include "PokemonSelector.h"

#include <QDir>
#include <QFileDialog>

int main(int argc, char** argv) {
	Generation1::registerLoader();
	Generation2::registerLoader();
	Generation3::registerLoader();

	QApplication app(argc, argv);

	GameRegistry registry;

	QString path = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Register ROM directory"));
	QDir dir(path);
	for (auto file : dir.entryInfoList(QDir::Files)) {
		registry.addRom(file.absoluteFilePath());
	}

	GameRegistryView registryView;
	registryView.setRegistry(&registry);
	registryView.show();

	return app.exec();
}
