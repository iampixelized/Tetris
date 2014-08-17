#include "Ghost.hpp"
#include "Tetromino.hpp"

Ghost::Ghost(TetrisPlayField & t, esc::AssetManager& am)
	: esc::Object("ghost_piece" , sf::Vector2f() , am)
{

}

Ghost::~Ghost()
{

}

void Ghost::setTetromino(Tetromino & t)
{
	tetromino = &t;
}

void Ghost::computeLocation()
{
	sf::Vector2i gpos = tetromino->getGridPosition();



}