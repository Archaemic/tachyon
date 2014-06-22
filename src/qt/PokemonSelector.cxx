#include "PokemonSelector.h"

#include "common/Group.h"

#include "Cartridge.h"
#include "PokemonList.h"
#include "PokemonStatus.h"
#include "GroupList.h"

#include <QListView>
#include <QTableView>
#include <QHBoxLayout>

PokemonSelector::PokemonSelector(QWidget* parent)
	: QWidget(parent)
	, m_cart(nullptr)
	, m_activeGroup(nullptr)
	, m_groupList(new GroupList(this))
	, m_pokemonList(new PokemonList(this))
	, m_pokemonStatus(new PokemonStatus(this))
	, m_groupListView(new QListView)
	, m_pokemonListView(new QListView)
{
	m_groupListView->setModel(m_groupList);
	m_groupListView->setMinimumWidth(50);
	m_groupListView->setMaximumWidth(100);
	m_pokemonListView->setModel(m_pokemonList);
	m_pokemonListView->setViewMode(QListView::IconMode);
	m_pokemonListView->setIconSize(QSize(PokemonList::SPRITE_SIZE, PokemonList::SPRITE_SIZE));
	m_pokemonListView->setGridSize(QSize(PokemonList::SPRITE_SIZE, PokemonList::SPRITE_SIZE + 32));
	m_pokemonListView->setResizeMode(QListView::Adjust);
	resize(QSize(650, 400));
	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(m_groupListView);
	hbox->addWidget(m_pokemonListView);
	hbox->addWidget(m_pokemonStatus);
	setLayout(hbox);

	connect(m_groupListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(selectGroup(const QModelIndex&)));
	connect(m_pokemonListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(selectPokemon(const QModelIndex&)));
}

void PokemonSelector::load(Cartridge* cart) {
	m_cart = cart;
	m_groupList->setCartridge(cart);
}

void PokemonSelector::selectGroup(const QModelIndex& index) {
	Group* group = static_cast<Group*>(m_groupList->data(index, Qt::UserRole).value<void*>());
	m_pokemonList->setGroup(group);
	m_activeGroup = group;
}

void PokemonSelector::selectPokemon(const QModelIndex& index) {
	if (m_activeGroup && index.isValid()) {
		m_pokemonStatus->setPokemon(std::move(m_activeGroup->at(index.row())));
	} else {
		m_pokemonStatus->setPokemon(nullptr);
	}
}
