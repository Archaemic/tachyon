#ifndef PTXN_Q_POKEMON_TABLE_H
#define PTXN_Q_POKEMON_TABLE_H

#include "common/Pokemon.h"

#include <QAbstractTableModel>

class Group;

class PokemonTable : public QAbstractTableModel {
Q_OBJECT
public:
	enum {
		COLUMN_NAME,
		COLUMN_SPECIES,
		COLUMN_SPECIES_ID,
		COLUMN_LEVEL,
		COLUMN_OT,
		COLUMN_OT_ID,
		COLUMN_SECRET_ID,
		COLUMN_EXP,
		COLUMN_HP,
		COLUMN_MAX_HP,
		COLUMN_TYPE_1,
		COLUMN_TYPE_2,
		COLUMN_ATTACK,
		COLUMN_DEFENSE,
		COLUMN_SPECIAL_ATTACK,
		COLUMN_SPECIAL_DEFENSE,
		COLUMN_SPEED,
		COLUMN_NATURE,
		COLUMN_MOVE_1,
		COLUMN_MOVE_2,
		COLUMN_MOVE_3,
		COLUMN_MOVE_4,
		COLUMN_MAX
	};

	PokemonTable(QObject* parent = nullptr);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
	void setGroup(Group* group);

private:
	Group* m_group;
};

#endif
