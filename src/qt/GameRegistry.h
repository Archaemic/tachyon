#ifndef PTXN_Q_GAME_REGISTRY_H
#define PTXN_Q_GAME_REGISTRY_H

#include "common/Game.h"

#include <QAbstractTableModel>

class GameRegistry;
class QFile;

class GameRegistryListModel : public QAbstractTableModel {
Q_OBJECT
public:
	GameRegistryListModel(GameRegistry* parent);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	virtual QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const override;

	using QAbstractItemModel::beginResetModel;
	using QAbstractItemModel::endResetModel;

private:
	GameRegistry* m_parent;
};

class GameRegistry : public QObject {
Q_OBJECT

friend class GameRegistryListModel; // TODO: Remove friend relationship

public:
	struct GameInfo {
		int id;
		Game::Edition version;
		uint8_t* rom;
		QFile* file;
	};

	typedef int Id;

	GameRegistry(QObject* parent = nullptr);
	~GameRegistry();

	Id addRom(const QString& path);
	GameInfo getInfo(Id id);

	GameRegistryListModel* listModel() { return m_listModel; }
	const GameRegistryListModel* listModel() const { return m_listModel; }

	static QString versionReadable(Game::Edition);
	static QString localizationReadable(Game::Edition);

private:
	std::vector<GameInfo> m_info;
	Id m_maxId;
	GameRegistryListModel* m_listModel;
};

#endif
