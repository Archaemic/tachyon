#ifndef PTXN_Q_POKEMON_STATUS_H
#define PTXN_Q_POKEMON_STATUS_H

#include "ui_PokemonStatus.h"

#include "common/Pokemon.h"

#include <QWidget>

#include <memory>

class QLabel;

class PokemonStatus : public QWidget {
Q_OBJECT
public:
	const static int SPRITE_SIZE = 96;

	PokemonStatus(QWidget* parent = nullptr);

	void setPokemon(std::unique_ptr<Pokemon> pokemon);

public slots:
	void resetPokemon();
	void updateStats();
	void setExp(int);
	void setIvHp(int);
	void setIvAttack(int);
	void setIvDefense(int);
	void setIvSpeed(int);
	void setIvSpecialAttack(int);
	void setIvSpecialDefense(int);
	void setEvHp(int);
	void setEvAttack(int);
	void setEvDefense(int);
	void setEvSpeed(int);
	void setEvSpecialAttack(int);
	void setEvSpecialDefense(int);

private slots:
	void buttonPressed(QAbstractButton*);

private:
	Ui::PokemonStatus m_ui;

	std::unique_ptr<Pokemon> m_activePokemon;
	std::unique_ptr<Pokemon> m_pristinePokemon;
	bool m_entered;
};

#endif
