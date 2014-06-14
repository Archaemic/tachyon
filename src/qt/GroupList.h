#ifndef PTXN_Q_GROUP_LIST_H
#define PTXN_Q_GROUP_LIST_H

#include <QAbstractListModel>

#include <memory>
#include <vector>

class Cartridge;

class GroupList : public QAbstractListModel {
Q_OBJECT
public:
	GroupList(QObject* parent = nullptr);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
	void setCartridge(Cartridge*);

private:
	Cartridge* m_cart;
};

#endif
