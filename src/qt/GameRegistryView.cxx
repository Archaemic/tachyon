#include "GameRegistryView.h"

#include "Cartridge.h"
#include "GameRegistry.h"
#include "PokemonSelector.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTreeView>

GameRegistryView::GameRegistryView(QWidget* parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);
	connect(m_ui.treeView, SIGNAL(activated(const QModelIndex&)), this, SLOT(openSavegame(const QModelIndex&)));
	connect(m_ui.loadSave, SIGNAL(clicked()), this, SLOT(openSavegame()));
	connect(m_ui.addFile, SIGNAL(clicked()), this, SLOT(addFile()));
	connect(m_ui.addDirectory, SIGNAL(clicked()), this, SLOT(addDirectory()));
}

void GameRegistryView::setRegistry(GameRegistry* registry) {
	m_registry = registry;
	m_ui.treeView->setModel(registry->listModel());
}

void GameRegistryView::openSavegame() {
	QModelIndexList indices = m_ui.treeView->selectionModel()->selectedRows();
	for (auto selection : indices) {
		openSavegame(selection);
	}
}

void GameRegistryView::openSavegame(const QModelIndex& index) {
	GameRegistry::Id id = m_ui.treeView->model()->data(index, Qt::UserRole).toInt();
	GameRegistry::GameInfo info = m_registry->getInfo(id);

	if (!info.version) {
		return;
	}

	QString sramPath = QFileDialog::getOpenFileName(this, tr("Open Savegame"));
	if (sramPath.isNull()) {
		return;
	}

	PokemonSelector* selector = new PokemonSelector;
	selector->setAttribute(Qt::WA_DeleteOnClose);
	Cartridge* cart = new Cartridge(info.rom, sramPath, selector);
	if (!cart->game()->testChecksum()) {
		QMessageBox* error = new QMessageBox(QMessageBox::Critical, tr("Could not open game"), tr("Could not open game"), QMessageBox::Close, this);
		error->setInformativeText(tr("The save game had an incorrect checksum. You may have tried to open the wrong save game, or it may be corrupted."));
		error->show();
		delete selector;
		return;
	}
	selector->load(cart);
	selector->show();
}

void GameRegistryView::addFile() {
	QStringList paths = QFileDialog::getOpenFileNames(nullptr, QObject::tr("Register ROM files"));
	for (auto file : paths) {
		m_registry->addRom(file);
	}
}

void GameRegistryView::addDirectory() {
	QString path = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Register ROM directory"));
	if (path.isNull()) {
		return;
	}
	QDir dir(path);
	for (auto file : dir.entryInfoList(QDir::Files)) {
		m_registry->addRom(file.absoluteFilePath());
	}
}
