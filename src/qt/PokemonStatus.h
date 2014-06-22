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

private:
	Ui::PokemonStatus m_ui;

	std::unique_ptr<Pokemon> m_activePokemon;
};

#endif
