#include "PokemonStatus.h"

#include "common/PokemonSpecies.h"

#include "SpriteUtilities.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

PokemonStatus::PokemonStatus(QWidget* parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	setPokemon(nullptr);
}

void PokemonStatus::setPokemon(std::unique_ptr<Pokemon> pokemon) {
	m_activePokemon = std::move(pokemon);

	QPixmap nullPixmap(SPRITE_SIZE, SPRITE_SIZE);
	nullPixmap.fill(Qt::transparent);

	if (m_activePokemon) {
		m_ui.name->setText(QString::fromUtf8(m_activePokemon->name().c_str()));
		m_ui.species->setText(QString::fromUtf8(m_activePokemon->species()->readable()));
		m_ui.speciesNo->setText(tr("#%1").arg(QString::number(m_activePokemon->species()->id()), 3, '0'));
		if (m_activePokemon->shiny()) {
			m_ui.shiny->setText(tr("⁂"));
		} else {
			m_ui.shiny->clear();
		}

		const MultipaletteSprite* frontSprite = m_activePokemon->species()->frontSprite();
		if (frontSprite) {
			QImage frontSpriteImage = spriteToQImage(*frontSprite, m_activePokemon->shiny() ? 1 : 0);
			m_ui.frontSprite->setPixmap(QPixmap::fromImage(fitToMargins(frontSpriteImage, SPRITE_SIZE, SPRITE_SIZE)));
		} else {
			m_ui.frontSprite->setPixmap(nullPixmap);
		}

		const MultipaletteSprite* backSprite = m_activePokemon->species()->backSprite();
		if (backSprite) {
			QImage backSpriteImage = spriteToQImage(*backSprite, m_activePokemon->shiny() ? 1 : 0);
			m_ui.backSprite->setPixmap(QPixmap::fromImage(fitToMargins(backSpriteImage, SPRITE_SIZE, SPRITE_SIZE)));
		} else {
			m_ui.backSprite->setPixmap(nullPixmap);
		}

		m_ui.hp->setText(QString("%1/%2").arg(m_activePokemon->currentHp()).arg(m_activePokemon->maxHp()));
		m_ui.level->setText(QString::number(m_activePokemon->level()));
		m_ui.attack->setText(QString::number(m_activePokemon->attack()));
		m_ui.defense->setText(QString::number(m_activePokemon->defense()));
		m_ui.speed->setText(QString::number(m_activePokemon->speed()));
		m_ui.specialAttack->setText(QString::number(m_activePokemon->specialAttack()));
		m_ui.specialDefense->setText(QString::number(m_activePokemon->specialDefense()));
		m_ui.ot->setText(tr("%1 (%2/%3)")
			.arg(QString::fromUtf8(m_activePokemon->otName().c_str()))
			.arg(QString::number(m_activePokemon->otId()), 5, '0')
			.arg(QString::number(m_activePokemon->otSecretId()), 5, '0'));

		m_ui.ivHp->setValue(m_activePokemon->ivHp());
		m_ui.ivAttack->setValue(m_activePokemon->ivAttack());
		m_ui.ivDefense->setValue(m_activePokemon->ivDefense());
		m_ui.ivSpeed->setValue(m_activePokemon->ivSpeed());
		m_ui.ivSpecialAttack->setValue(m_activePokemon->ivSpecialAttack());
		m_ui.ivSpecialDefense->setValue(m_activePokemon->ivSpecialDefense());
		m_ui.evHp->setValue(m_activePokemon->evHp());
		m_ui.evAttack->setValue(m_activePokemon->evAttack());
		m_ui.evDefense->setValue(m_activePokemon->evDefense());
		m_ui.evSpeed->setValue(m_activePokemon->evSpeed());
		m_ui.evSpecialAttack->setValue(m_activePokemon->evSpecialAttack());
		m_ui.evSpecialDefense->setValue(m_activePokemon->evSpecialDefense());
	} else {
		m_ui.name->setText(tr("(No selection)"));
		m_ui.species->clear();
		m_ui.speciesNo->clear();
		m_ui.shiny->clear();

		m_ui.frontSprite->setPixmap(nullPixmap);
		m_ui.backSprite->setPixmap(nullPixmap);

		m_ui.level->setText(tr("-"));
		m_ui.hp->setText(tr("-/-"));
		m_ui.attack->setText(tr("-"));
		m_ui.defense->setText(tr("-"));
		m_ui.speed->setText(tr("-"));
		m_ui.specialAttack->setText(tr("-"));
		m_ui.specialDefense->setText(tr("-"));

		m_ui.ivHp->setValue(0);
		m_ui.ivAttack->setValue(0);
		m_ui.ivDefense->setValue(0);
		m_ui.ivSpeed->setValue(0);
		m_ui.ivSpecialAttack->setValue(0);
		m_ui.ivSpecialDefense->setValue(0);
		m_ui.evHp->setValue(0);
		m_ui.evAttack->setValue(0);
		m_ui.evDefense->setValue(0);
		m_ui.evSpeed->setValue(0);
		m_ui.evSpecialAttack->setValue(0);
		m_ui.evSpecialDefense->setValue(0);
	}
}
