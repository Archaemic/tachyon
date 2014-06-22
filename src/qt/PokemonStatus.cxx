#include "PokemonStatus.h"

#include "common/PokemonSpecies.h"

#include "SpriteUtilities.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

PokemonStatus::PokemonStatus(QWidget* parent)
	: QWidget(parent)
	, m_name(new QLabel(this))
	, m_species(new QLabel(this))
	, m_speciesNo(new QLabel(this))
	, m_frontSprite(new QLabel(this))
	, m_backSprite(new QLabel(this))
{
	setPokemon(nullptr);

	QHBoxLayout* hbox;
	QVBoxLayout* vbox = new QVBoxLayout;

	hbox = new QHBoxLayout;
	hbox->addWidget(m_frontSprite);
	hbox->addWidget(m_backSprite);
	vbox->addLayout(hbox);

	hbox = new QHBoxLayout;
	hbox->addWidget(m_name, 1, Qt::AlignLeft);
	hbox->addWidget(m_species, 0, Qt::AlignRight);
	hbox->addWidget(m_speciesNo, 0, Qt::AlignRight);
	vbox->addLayout(hbox);

	vbox->addStretch();

	setLayout(vbox);
}

void PokemonStatus::setPokemon(std::unique_ptr<Pokemon> pokemon) {
	m_activePokemon = std::move(pokemon);

	QPixmap nullPixmap(SPRITE_SIZE, SPRITE_SIZE);
	nullPixmap.fill(Qt::transparent);

	if (m_activePokemon) {
		m_name->setText(QString::fromUtf8(m_activePokemon->name().c_str()));
		m_species->setText(QString::fromUtf8(m_activePokemon->species()->readable()));
		m_speciesNo->setText(tr("#%1").arg(QString::number(m_activePokemon->species()->id()), 3, '0'));

		const MultipaletteSprite* frontSprite = m_activePokemon->species()->frontSprite();
		if (frontSprite) {
			QImage frontSpriteImage = spriteToQImage(*frontSprite, m_activePokemon->shiny() ? 1 : 0);
			m_frontSprite->setPixmap(QPixmap::fromImage(fitToMargins(frontSpriteImage, SPRITE_SIZE, SPRITE_SIZE)));
		} else {
			m_frontSprite->setPixmap(nullPixmap);
		}

		const MultipaletteSprite* backSprite = m_activePokemon->species()->backSprite();
		if (backSprite) {
			QImage backSpriteImage = spriteToQImage(*backSprite, m_activePokemon->shiny() ? 1 : 0);
			m_backSprite->setPixmap(QPixmap::fromImage(fitToMargins(backSpriteImage, SPRITE_SIZE, SPRITE_SIZE)));
		} else {
			m_backSprite->setPixmap(nullPixmap);
		}
	} else {
		m_name->setText(tr("(No selection)"));
		m_species->clear();
		m_speciesNo->clear();

		m_frontSprite->setPixmap(nullPixmap);
		m_backSprite->setPixmap(nullPixmap);
	}
}
