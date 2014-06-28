#include "GameRegistry.h"

#include <QFile>

GameRegistryListModel::GameRegistryListModel(GameRegistry* parent)
	: QAbstractTableModel(parent)
	, m_parent(parent)
{
}

int GameRegistryListModel::rowCount(const QModelIndex&) const {
	return m_parent->m_info.size();
}

int GameRegistryListModel::columnCount(const QModelIndex&) const {
	return 3;
}

QVariant GameRegistryListModel::data(const QModelIndex& index, int role) const {
	if (index.row() >= int(m_parent->m_info.size())) {
		return QVariant();
	}

	switch (role) {
	case Qt::DisplayRole:
		switch (index.column()) {
		case 0:
			return GameRegistry::versionReadable(m_parent->m_info[index.row()].version);
		case 1:
			return GameRegistry::localizationReadable(m_parent->m_info[index.row()].version);
		case 2:
			return m_parent->m_info[index.row()].file->fileName();
		default:
			return QVariant();
		}
	case Qt::UserRole:
		return m_parent->m_info[index.row()].id;
	default:
		return QVariant();
	}
}

QVariant GameRegistryListModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
		return QAbstractTableModel::headerData(section, orientation, role);
	}

	switch (section) {
	case 0:
		return tr("Game");
	case 1:
		return tr("Localization");
	case 2:
		return tr("File name");
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

QString GameRegistry::versionReadable(Game::Edition version) {
	switch (version & Game::MASK_GAME) {
	case Game::G10_RED:
		return tr("Red");
	case Game::G10_BLUE:
		if ((version & Game::MASK_LOCALIZATION) == Game::JAPANESE) {
			return tr("Green");
		}
		return tr("Blue");
	case Game::G11_BLUE:
		return tr("Blue");
	case Game::G12_YELLOW:
		return tr("Yellow");
	case Game::G20_GOLD:
		return tr("Gold");
	case Game::G20_SILVER:
		return tr("Silver");
	case Game::G21_CRYSTAL:
		return tr("Crystal");
	case Game::G30_RUBY:
		return tr("Ruby");
	case Game::G30_SAPPHIRE:
		return tr("Sapphire");
	case Game::G31_EMERALD:
		return tr("Emerald");
	case Game::G32_FIRE_RED:
		return tr("FireRed");
	case Game::G32_LEAF_GREEN:
		return tr("LeafGreen");
	default:
		return tr("???");
	}
}

QString GameRegistry::localizationReadable(Game::Edition version) {
	switch (version & Game::MASK_LOCALIZATION) {
	case Game::JAPANESE:
		return tr("Japanese");
	case Game::ENGLISH:
		return tr("English");
	case Game::GERMAN:
		return tr("German");
	case Game::FRENCH:
		return tr("French");
	case Game::SPANISH:
		return tr("Spanish");
	case Game::ITALIAN:
		return tr("Italian");
	case Game::KOREAN:
		return tr("Korean");
	default:
		return tr("???");
	}
}
