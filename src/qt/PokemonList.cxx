#include "PokemonList.h"

#include "common/Game.h"
#include "common/Group.h"
#include "common/MultipaletteSprite.h"

#include "SpriteUtilities.h"

#include <QImage>
#include <QPixmap>

std::unique_ptr<QPixmap> PokemonList::nullPixmap;

PokemonList::PokemonList(QObject* parent)
	: QAbstractListModel(parent)
	, m_group(nullptr)
{
	if (!nullPixmap) {
		nullPixmap = std::unique_ptr<QPixmap>(new QPixmap(SPRITE_SIZE, SPRITE_SIZE));
		nullPixmap->fill(Qt::transparent);
	}
}

void PokemonList::setGroup(Group* group) {
	beginResetModel();
	m_group = group;
	endResetModel();
}

int PokemonList::rowCount(const QModelIndex&) const {
	if (!m_group) {
		return 0;
	}
	return m_group->length();
}

QVariant PokemonList::data(const QModelIndex& index, int role) const {
	std::unique_ptr<Pokemon> pokemon = m_group->at(index.row());
	switch (role) {
	case Qt::DisplayRole:
		if (!pokemon) {
			return "---";
		}

		return QString::fromUtf8(pokemon->name().c_str());
	case Qt::DecorationRole: {
		if (!pokemon) {
			return *nullPixmap.get();
		}

		const MultipaletteSprite* sprite = pokemon->species()->frontSprite();
		if (!sprite) {
			return *nullPixmap.get();
		}

		QImage image = spriteToQImage(*sprite, pokemon->shiny() ? 1 : 0);
		return QPixmap::fromImage(fitToMargins(image, SPRITE_SIZE, SPRITE_SIZE));
		break;
	}
	default:
		return QVariant();
	}
}
