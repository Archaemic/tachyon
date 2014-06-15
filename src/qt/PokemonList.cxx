#include "PokemonList.h"

#include "common/Game.h"
#include "common/Group.h"
#include "common/Sprite.h"

#include <QImage>
#include <QPixmap>

PokemonList::PokemonList(QObject* parent)
	: QAbstractListModel(parent)
	, m_group(nullptr)
{
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
			return QVariant();
		}

		const Sprite* sprite = pokemon->species()->frontSprite();
		if (!sprite) {
			return QVariant();
		}

		QImage image(QSize(64, 64), QImage::Format_Indexed8);
		image.setColor(0, qRgba(0, 0, 0, 0));
		for (unsigned p = 1; p < 16; ++p) {
			uint16_t paletteEntry = sprite->palette()[p];
			image.setColor(p, qRgb((paletteEntry & 0x1F) << 3, (paletteEntry >> 2) & 0xF8, (paletteEntry >> 7) & 0xF8));
		}

		for (unsigned y = 0; y < 64; ++y) {
			for (unsigned x = 0; x < 32; ++x) {
				image.setPixel(x * 2 + 1, y, sprite->pixelData()[y * 32 + x] >> 4);
				image.setPixel(x * 2, y, sprite->pixelData()[y * 32 + x] & 0xF);
			}
		}
		return QPixmap::fromImage(image);
		break;
	}
	default:
		return QVariant();
	}
}
