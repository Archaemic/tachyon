#include "PokemonSelector.h"

#include "common/Group.h"

#include "Cartridge.h"
#include "PokemonList.h"
#include "GroupList.h"

#include <QListView>
#include <QTableView>
#include <QHBoxLayout>

PokemonSelector::PokemonSelector(QWidget* parent)
	: QWidget(parent)
	, m_cart(0)
	, m_groupList(new GroupList(this))
	, m_pokemonList(new PokemonList(this))
	, m_groupListView(new QListView)
	, m_pokemonListView(new QListView)
{
	m_groupListView->setModel(m_groupList);
	m_groupListView->setMinimumWidth(50);
	m_groupListView->setMaximumWidth(100);
	m_pokemonListView->setModel(m_pokemonList);
	m_pokemonListView->setViewMode(QListView::IconMode);
	m_pokemonListView->setIconSize(QSize(64, 64));
	m_pokemonListView->setGridSize(QSize(96, 96));
	m_pokemonListView->setResizeMode(QListView::Adjust);
	resize(QSize(650, 400));
	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(m_groupListView);
	hbox->addWidget(m_pokemonListView);
	setLayout(hbox);

	connect(m_groupListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(selectGroup(const QModelIndex&)));
}

void PokemonSelector::load(Cartridge* cart) {
	m_cart = cart;
	m_groupList->setCartridge(cart);
}

void PokemonSelector::selectGroup(const QModelIndex& index) {
	Group* group = static_cast<Group*>(m_groupList->data(index, Qt::UserRole).value<void*>());
	m_pokemonList->setGroup(group);
}
