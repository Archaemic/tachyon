#include "GameRegistryView.h"

#include "Cartridge.h"
#include "GameRegistry.h"
#include "PokemonSelector.h"

#include <QFileDialog>
#include <QHBoxLayout>

GameRegistryView::GameRegistryView(QWidget* parent)
	: QWidget(parent)
	, m_listView(new QListView(this))
{
	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(m_listView);
	setLayout(hbox);

	connect(m_listView, SIGNAL(activated(const QModelIndex&)), this, SLOT(openSavegame(const QModelIndex&)));
}

void GameRegistryView::setRegistry(GameRegistry* registry) {
	m_registry = registry;
	m_listView->setModel(registry->listModel());
}

void GameRegistryView::openSavegame(const QModelIndex& index) {
	GameRegistry::Id id = m_listView->model()->data(index, Qt::UserRole).toInt();
	GameRegistry::GameInfo info = m_registry->getInfo(id);

	if (!info.version) {
		return;
	}

	QString sramPath = QFileDialog::getOpenFileName(this, tr("Open Savegame"));
	PokemonSelector* selector = new PokemonSelector;
	selector->setAttribute(Qt::WA_DeleteOnClose);
	Cartridge* cart = new Cartridge(info.rom, sramPath, selector);
	selector->load(cart);
	selector->show();
}
