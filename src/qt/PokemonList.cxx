#include "PokemonList.h"

#include "common/Game.h"
#include "common/Group.h"
#include "common/MultipaletteSprite.h"

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

		QImage image(QSize(sprite->width(), sprite->height()), QImage::Format_Indexed8);
		image.setColor(0, qRgba(0, 0, 0, 0));
		const uint16_t* palette;
		if (pokemon->shiny()) {
			palette = sprite->paletteById(1);
		} else {
			palette = sprite->paletteById(0);
		}
		for (unsigned p = 1; p < 16; ++p) {
			uint16_t paletteEntry = palette[p];
			image.setColor(p, qRgb((paletteEntry & 0x1F) << 3, (paletteEntry >> 2) & 0xF8, (paletteEntry >> 7) & 0xF8));
		}

		switch (sprite->format()) {
		case Sprite::GBA_4:
			for (unsigned y = 0; y < sprite->height(); ++y) {
				for (unsigned x = 0; x < sprite->width() / 2; ++x) {
					image.setPixel(x * 2 + 1, y, sprite->pixelData()[y * sprite->width() / 2 + x] >> 4);
					image.setPixel(x * 2, y, sprite->pixelData()[y * sprite->width() / 2 + x] & 0xF);
				}
			}
			break;
		case Sprite::GB_2:
			for (unsigned y = 0; y < sprite->height(); ++y) {
				const uint16_t* row = reinterpret_cast<const uint16_t*>(&sprite->pixelData()[y * sprite->width() / 4]);
				for (unsigned x = 0; x < sprite->width() / 8; ++x) {
					uint16_t block = row[x];
					image.setPixel(x * 8, y, block >> 14);
					image.setPixel(x * 8 + 1, y, (block >> 12) & 0x3);
					image.setPixel(x * 8 + 2, y, (block >> 10) & 0x3);
					image.setPixel(x * 8 + 3, y, (block >> 8) & 0x3);
					image.setPixel(x * 8 + 4, y, (block >> 6) & 0x3);
					image.setPixel(x * 8 + 5, y, (block >> 4) & 0x3);
					image.setPixel(x * 8 + 6, y, (block >> 2) & 0x3);
					image.setPixel(x * 8 + 7, y, block & 0x3);
				}
			}
			break;
		}
		return QPixmap::fromImage(image.copy((int(sprite->width()) - SPRITE_SIZE) / 2, (int(sprite->height()) - SPRITE_SIZE) / 2, SPRITE_SIZE, SPRITE_SIZE));
		break;
	}
	default:
		return QVariant();
	}
}
