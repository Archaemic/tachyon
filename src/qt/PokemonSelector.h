#ifndef PTXN_Q_POKEMON_SELECTOR_H
#define PTXN_Q_POKEMON_SELECTOR_H

#include <QWidget>

class Cartridge;
class Group;
class GroupList;
class PokemonList;
class PokemonStatus;

class QListView;
class QTableView;

class PokemonSelector : public QWidget {
Q_OBJECT
public:
	PokemonSelector(QWidget* parent = nullptr);

	void load(Cartridge* cart);

private:
	Cartridge* m_cart;
	Group* m_activeGroup;
	GroupList* m_groupList;
	PokemonList* m_pokemonList;
	PokemonStatus* m_pokemonStatus;

	QListView* m_groupListView;
	QListView* m_pokemonListView;

private slots:
	void selectGroup(const QModelIndex&);
	void selectPokemon(const QModelIndex&);
};

#endif
