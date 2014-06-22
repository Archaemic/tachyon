#ifndef PTXN_Q_POKEMON_STATUS_H
#define PTXN_Q_POKEMON_STATUS_H

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
	std::unique_ptr<Pokemon> m_activePokemon;

	QLabel* m_name;
	QLabel* m_species;
	QLabel* m_speciesNo;
	QLabel* m_frontSprite;
	QLabel* m_backSprite;
};

#endif
