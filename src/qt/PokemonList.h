#ifndef PTXN_Q_POKEMON_LIST_H
#define PTXN_Q_POKEMON_LIST_H

#include "common/Pokemon.h"

#include <QAbstractListModel>

#include <memory>

class Group;

class PokemonList : public QAbstractListModel {
Q_OBJECT
public:
	const static int SPRITE_SIZE = 96;

	PokemonList(QObject* parent = nullptr);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
	void setGroup(Group* group);

private:
	static std::unique_ptr<QPixmap> nullPixmap;

	Group* m_group;
};

#endif
