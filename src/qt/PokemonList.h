#ifndef PTXN_Q_POKEMON_LIST_H
#define PTXN_Q_POKEMON_LIST_H

#include "common/Pokemon.h"

#include <QAbstractListModel>

class Group;

class PokemonList : public QAbstractListModel {
Q_OBJECT
public:
	PokemonList(QObject* parent = nullptr);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
	void setGroup(Group* group);

private:
	Group* m_group;
};

#endif
