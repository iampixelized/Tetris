#include "Ghost.hpp"

#include "Tetromino.hpp"
#include "TetrisPlayField.hpp"

Ghost::Ghost(TetrisPlayField & tpf, Mechanics & m, esc::AssetManager & am)
	: playField(&tpf), mechanics(&m), assetManager(&am)
{

}

Ghost::~Ghost()
{

}

void Ghost::setTetromino(Tetromino & t)
{
	tetromino = &t;

	mimic.reset
	(
		Tetromino::createTetromino
		(
			  t.getType()
			, Tetromino::BlockColor::Ghost
			, *playField
			, *mechanics
			, *assetManager
		)
	);

	tetromino->setGridPosition(playField->getFieldSize());
}

void Ghost::calculate()
{
	if (mimic.get() == nullptr)
		return;

	sf::Vector2i gpos = tetromino->getGridPosition();
	mimic.get()->setGridPosition(sf::Vector2i(gpos.x, playField->getPeakLevelOnRow(gpos.y)));
}

void Ghost::showGhostTetromino(sf::RenderWindow * w , bool show)
{
	if (!show) return;

	mimic.get()->draw(w);
}