#include "GroupList.h"

#include "common/Game.h"
#include "common/Group.h"

#include "Cartridge.h"

GroupList::GroupList(QObject* parent)
	: QAbstractListModel(parent)
	, m_cart(nullptr)
{
}

void GroupList::setCartridge(Cartridge* cart) {
	beginResetModel();
	m_cart = cart;
	endResetModel();
}

int GroupList::rowCount(const QModelIndex&) const {
	if (!m_cart) {
		return 0;
	}
	return m_cart->game()->numBoxes() + 1;
}

QVariant GroupList::data(const QModelIndex& index, int role) const {
	Group* group;
	if (index.row()) {
		group = m_cart->game()->box(index.row() - 1);
	} else {
		group = m_cart->game()->party();
	}
	switch (role) {
	case Qt::DisplayRole:
		return QString::fromUtf8(group->name().c_str());
	case Qt::UserRole:
		return QVariant::fromValue((void*) group);
	default:
		return QVariant();
	}
}
