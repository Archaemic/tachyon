#ifndef PTXN_Q_POKEMON_SELECTOR_H
#define PTXN_Q_POKEMON_SELECTOR_H

#include <QWidget>

class Cartridge;
class GroupList;
class PokemonTable;

class QListView;
class QTableView;

class PokemonSelector : public QWidget {
Q_OBJECT
public:
	PokemonSelector(QWidget* parent = nullptr);

	void load(Cartridge* cart);

private:
	Cartridge* m_cart;
	PokemonTable* m_table;
	GroupList* m_list;

	QListView* m_listView;
	QTableView* m_tableView;

private slots:
	void selectGroup(const QModelIndex&);
};

#endif
