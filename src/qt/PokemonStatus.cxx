#include "PokemonStatus.h"

#include "common/Move.h"
#include "common/PokemonSpecies.h"
#include "common/Type.h"

#include "SpriteUtilities.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

PokemonStatus::PokemonStatus(QWidget* parent)
	: QWidget(parent)
	, m_entered(false)
{
	m_ui.setupUi(this);

	setPokemon(nullptr);
}

void PokemonStatus::setPokemon(std::unique_ptr<Pokemon> pokemon) {
	m_activePokemon = std::move(pokemon);

	QPixmap nullPixmap(SPRITE_SIZE, SPRITE_SIZE);
	nullPixmap.fill(Qt::transparent);

	if (m_activePokemon) {
		setWindowTitle(QString::fromUtf8(m_activePokemon->name().c_str()));
		m_ui.name->setText(QString::fromUtf8(m_activePokemon->name().c_str()));
		m_ui.species->setText(QString::fromUtf8(m_activePokemon->species()->readable()));
		m_ui.speciesNo->setText(tr("#%1").arg(QString::number(m_activePokemon->species()->id()), 3, '0'));
		switch (m_activePokemon->gender()) {
		case Pokemon::MALE:
			m_ui.gender->setText(tr("♂"));
			break;
		case Pokemon::FEMALE:
			m_ui.gender->setText(tr("♀"));
			break;
		case Pokemon::GENDERLESS:
			m_ui.gender->clear();
			break;
		}
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

		const MultipaletteSprite* menuSprite = m_activePokemon->species()->menuSprite();
		if (menuSprite) {
			QImage menuSpriteImage = spriteToQImage(*menuSprite, m_activePokemon->shiny() ? 1 : 0);
			m_ui.menuSprite->setPixmap(QPixmap::fromImage(menuSpriteImage));
			m_ui.menuSprite->setMinimumSize(QSize(menuSprite->width(), menuSprite->height()));
		} else {
			m_ui.menuSprite->clear();
			m_ui.menuSprite->setMinimumSize(QSize(16, 16));
		}

		m_ui.ot->setText(tr("%1 (%2/%3)")
			.arg(QString::fromUtf8(m_activePokemon->otName().c_str()))
			.arg(QString::number(m_activePokemon->otId()), 5, '0')
			.arg(QString::number(m_activePokemon->otSecretId()), 5, '0'));


		m_ui.type1->setText(QString::fromUtf8(TypeReadable(m_activePokemon->type1())));
		if (m_activePokemon->type1() != m_activePokemon->type2()) {
			m_ui.type2->setText(QString::fromUtf8(TypeReadable(m_activePokemon->type2())));
		} else {
			m_ui.type2->clear();
		}
		m_ui.nature->setText(QString::fromUtf8(m_activePokemon->natureReadable()));

		m_ui.move1->setText(QString::fromUtf8(MoveReadable(m_activePokemon->move1())));
		m_ui.move2->setText(QString::fromUtf8(MoveReadable(m_activePokemon->move2())));
		m_ui.move3->setText(QString::fromUtf8(MoveReadable(m_activePokemon->move3())));
		m_ui.move4->setText(QString::fromUtf8(MoveReadable(m_activePokemon->move4())));

		m_ui.exp->setMaximum(m_activePokemon->species()->expToLevel(100));

		updateStats();
	} else {
		setWindowTitle(tr("Pokémon"));
		m_ui.name->setText(tr("(No selection)"));
		m_ui.species->clear();
		m_ui.speciesNo->clear();
		m_ui.gender->clear();
		m_ui.shiny->clear();

		m_ui.frontSprite->setPixmap(nullPixmap);
		m_ui.backSprite->setPixmap(nullPixmap);
		m_ui.menuSprite->clear();
		m_ui.menuSprite->setMinimumSize(QSize(16, 16));

		m_ui.level->setText(tr("-"));
		m_ui.hp->setText(tr("-/-"));
		m_ui.attack->setText(tr("-"));
		m_ui.defense->setText(tr("-"));
		m_ui.speed->setText(tr("-"));
		m_ui.specialAttack->setText(tr("-"));
		m_ui.specialDefense->setText(tr("-"));

		m_ui.exp->setValue(0);
		m_ui.expProgress->setValue(0);

		m_ui.type1->setText(tr("-"));
		m_ui.type2->clear();
		m_ui.nature->setText(tr("---"));

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

		m_ui.move1->setText(tr("-"));
		m_ui.move2->setText(tr("-"));
		m_ui.move3->setText(tr("-"));
		m_ui.move4->setText(tr("-"));
	}
}

void PokemonStatus::updateStats() {
	if (!m_activePokemon) {
		return;
	}

	m_entered = true;
	m_ui.hp->setText(QString("%1/%2").arg(m_activePokemon->currentHp()).arg(m_activePokemon->maxHp()));
	m_ui.level->setText(QString::number(m_activePokemon->level()));
	m_ui.attack->setText(QString::number(m_activePokemon->attack()));
	m_ui.defense->setText(QString::number(m_activePokemon->defense()));
	m_ui.speed->setText(QString::number(m_activePokemon->speed()));
	m_ui.specialAttack->setText(QString::number(m_activePokemon->specialAttack()));
	m_ui.specialDefense->setText(QString::number(m_activePokemon->specialDefense()));

	m_ui.exp->setValue(m_activePokemon->xp());
	m_ui.expProgress->setMaximum(m_activePokemon->species()->expToLevel(m_activePokemon->level() + 1) - m_activePokemon->species()->expToLevel(m_activePokemon->level()));
	m_ui.expProgress->setValue(m_activePokemon->xp() - m_activePokemon->species()->expToLevel(m_activePokemon->level()));

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
	m_entered = false;
}

void PokemonStatus::setExp(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setXp(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setIvHp(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setIvHp(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setIvAttack(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setIvAttack(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setIvDefense(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setIvDefense(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setIvSpeed(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setIvSpeed(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setIvSpecialAttack(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setIvSpecialAttack(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setIvSpecialDefense(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setIvSpecialDefense(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setEvHp(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setEvHp(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setEvAttack(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setEvAttack(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setEvDefense(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setEvDefense(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setEvSpeed(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setEvSpeed(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setEvSpecialAttack(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setEvSpecialAttack(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
void PokemonStatus::setEvSpecialDefense(int stat) {
	if (!m_activePokemon || m_entered) {
		return;
	}

	m_activePokemon->setEvSpecialDefense(stat);
	m_activePokemon->recalculateStats();
	updateStats();
}
