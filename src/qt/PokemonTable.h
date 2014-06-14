#ifndef PTXN_Q_POKEMON_TABLE_H
#define PTXN_Q_POKEMON_TABLE_H

#include "common/Group.h"

#include <QAbstractItemModel>

#include <memory>
#include <vector>

class Cartridge;

class PokemonTable : public QAbstractItemModel {
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

	void load(Cartridge* cart);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	virtual QModelIndex parent(const QModelIndex& index) const override;

public slots:
	void unload();

private:
	Cartridge* m_cart;
	std::vector<std::unique_ptr<Group>> m_groups;

	void update();
};

#endif
