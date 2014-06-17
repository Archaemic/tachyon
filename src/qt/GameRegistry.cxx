#include "GameRegistry.h"

#include <QFile>

GameRegistryListModel::GameRegistryListModel(GameRegistry* parent)
	: QAbstractListModel(parent)
	, m_parent(parent)
{
}

int GameRegistryListModel::rowCount(const QModelIndex&) const {
	return m_parent->m_info.size();
}

QVariant GameRegistryListModel::data(const QModelIndex& index, int role) const {
	if (index.row() >= int(m_parent->m_info.size())) {
		return QVariant();
	}

	switch (role) {
	case Qt::DisplayRole:
		return m_parent->m_info[index.row()].file->fileName();
	case Qt::UserRole:
		return m_parent->m_info[index.row()].id;
	default:
		return QVariant();
	}
}

GameRegistry::GameRegistry(QObject* parent)
	: QObject(parent)
	, m_maxId(0)
	, m_listModel(new GameRegistryListModel(this))
{
}

GameRegistry::~GameRegistry() {
	for (auto& info : m_info) {
		if (info.rom && info.file) {
			info.file->unmap(info.rom);
		}
	}
}

GameRegistry::Id GameRegistry::addRom(const QString& path) {
	GameInfo info;
	info.file = new QFile(path, this);
	if (!info.file->open(QIODevice::ReadOnly)) {
		delete info.file;
		return 0;
	}
	info.rom = info.file->map(0, info.file->size());
	info.version = Game::detect(info.rom);
	if (!info.version) {
		info.file->unmap(info.rom);
		delete info.file;
		return 0;
	}
	++m_maxId;
	info.id = m_maxId;
	m_info.push_back(info);
	return m_maxId;
}

GameRegistry::GameInfo GameRegistry::getInfo(GameRegistry::Id id) {
	for (const auto& info : m_info) {
		if (info.id == id) {
			return info;
		}
	}
	GameInfo info = {};
	return info;
}
