#include "PokemonTable.h"

#include "common/Game.h"
#include "common/Group.h"
#include "common/Move.h"

#include <vector>

PokemonTable::PokemonTable(QObject* parent)
	: QAbstractTableModel(parent)
	, m_group(nullptr)
{
}

void PokemonTable::setGroup(Group* group) {
	m_group = group;
}

int PokemonTable::rowCount(const QModelIndex&) const {
	return m_group->length();
}

int PokemonTable::columnCount(const QModelIndex&) const {
	return COLUMN_MAX;
}

QVariant PokemonTable::data(const QModelIndex& index, int role) const {
	if (role != Qt::DisplayRole) {
		return QVariant();
	}
	std::unique_ptr<Pokemon> pokemon = m_group->at(index.row());
	switch (index.column()) {
	case COLUMN_NAME:
		return QString::fromUtf8(pokemon->name().c_str());
	case COLUMN_SPECIES:
		return QString::fromUtf8(pokemon->species()->readable());
	case COLUMN_SPECIES_ID:
		return pokemon->species()->id();
	case COLUMN_LEVEL:
		return pokemon->level();
	case COLUMN_OT:
		return QString::fromUtf8(pokemon->otName().c_str());
	case COLUMN_OT_ID:
		return pokemon->otId();
	case COLUMN_SECRET_ID:
		return pokemon->otSecretId();
	case COLUMN_EXP:
		return pokemon->xp();
	case COLUMN_HP:
		return pokemon->currentHp();
	case COLUMN_MAX_HP:
		return pokemon->maxHp();
	case COLUMN_TYPE_1:
		return QString::fromUtf8(TypeReadable(pokemon->type1()));
	case COLUMN_TYPE_2:
		if (pokemon->type1() != pokemon->type2()) {
			return QString::fromUtf8(TypeReadable(pokemon->type2()));
		} else {
			return "";
		}
	case COLUMN_ATTACK:
		return pokemon->attack();
	case COLUMN_DEFENSE:
		return pokemon->defense();
	case COLUMN_SPECIAL_ATTACK:
		return pokemon->specialAttack();
	case COLUMN_SPECIAL_DEFENSE:
		return pokemon->specialDefense();
	case COLUMN_SPEED:
		return pokemon->speed();
	case COLUMN_NATURE:
		return QString::fromUtf8(pokemon->natureReadable());
	case COLUMN_MOVE_1:
		return QString::fromUtf8(MoveReadable(pokemon->move1()));
	case COLUMN_MOVE_2:
		return QString::fromUtf8(MoveReadable(pokemon->move2()));
	case COLUMN_MOVE_3:
		return QString::fromUtf8(MoveReadable(pokemon->move3()));
	case COLUMN_MOVE_4:
		return QString::fromUtf8(MoveReadable(pokemon->move4()));
	default:
		return 0;
	}
}

QVariant PokemonTable::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole || orientation == Qt::Vertical) {
		return QAbstractTableModel::headerData(section, orientation, role);
	}
	switch (section) {
	case COLUMN_NAME:
		return tr("Name");
	case COLUMN_SPECIES:
		return tr("Species");
	case COLUMN_SPECIES_ID:
		return tr("ID");
	case COLUMN_LEVEL:
		return tr("Level");
	case COLUMN_OT:
		return tr("Original Trainer");
	case COLUMN_OT_ID:
		return tr("OT ID");
	case COLUMN_SECRET_ID:
		return tr("Secret ID");
	case COLUMN_EXP:
		return tr("Experience");
	case COLUMN_HP:
		return tr("HP");
	case COLUMN_MAX_HP:
		return tr("Max HP");
	case COLUMN_TYPE_1:
		return tr("Type 1");
	case COLUMN_TYPE_2:
		return tr("Type 2");
	case COLUMN_ATTACK:
		return tr("Attack");
	case COLUMN_DEFENSE:
		return tr("Defense");
	case COLUMN_SPECIAL_ATTACK:
		return tr("Special Attack");
	case COLUMN_SPECIAL_DEFENSE:
		return tr("Special Defense");
	case COLUMN_SPEED:
		return tr("Speed");
	case COLUMN_NATURE:
		return tr("Nature");
	case COLUMN_MOVE_1:
		return tr("Move 1");
	case COLUMN_MOVE_2:
		return tr("Move 2");
	case COLUMN_MOVE_3:
		return tr("Move 3");
	case COLUMN_MOVE_4:
		return tr("Move 4");
	default:
		return 0;
	}
}
