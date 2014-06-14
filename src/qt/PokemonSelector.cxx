#include "PokemonSelector.h"

#include "common/Group.h"

#include "Cartridge.h"
#include "PokemonTable.h"
#include "GroupList.h"

#include <QListView>
#include <QTableView>
#include <QHBoxLayout>

PokemonSelector::PokemonSelector(QWidget* parent)
	: QWidget(parent)
	, m_cart(0)
	, m_table(new PokemonTable(this))
	, m_list(new GroupList(this))
	, m_listView(new QListView)
	, m_tableView(new QTableView)
{
	m_listView->setModel(m_list);
	m_listView->setMinimumWidth(50);
	m_listView->setMaximumWidth(140);
	m_tableView->setModel(m_table);
	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(m_listView);
	hbox->addWidget(m_tableView);
	setLayout(hbox);

	connect(m_listView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(selectGroup(const QModelIndex&)));
}

void PokemonSelector::load(Cartridge* cart) {
	m_cart = cart;
	m_list->setCartridge(cart);
}

void PokemonSelector::selectGroup(const QModelIndex& index) {
	Group* group = static_cast<Group*>(m_list->data(index, Qt::UserRole).value<void*>());
	m_table->setGroup(group);
}
