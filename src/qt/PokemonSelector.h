#ifndef PTXN_Q_POKEMON_SELECTOR_H
#define PTXN_Q_POKEMON_SELECTOR_H

#include <QWidget>

class Cartridge;
class GroupList;
class PokemonList;

class QListView;
class QTableView;

class PokemonSelector : public QWidget {
Q_OBJECT
public:
	PokemonSelector(QWidget* parent = nullptr);

	void load(Cartridge* cart);

private:
	Cartridge* m_cart;
	GroupList* m_groupList;
	PokemonList* m_pokemonList;

	QListView* m_groupListView;
	QListView* m_pokemonListView;

private slots:
	void selectGroup(const QModelIndex&);
};

#endif
