#include "TetrominoKicker.hpp"
#include "Tetromino.hpp"
#include "TetrisPlayField.hpp"
#include "RotationSystem.hpp"

void TetrominoKicker::setTetromino(Tetromino * t)
{
	if (tetromino == nullptr) return;

	tetromino      = t;
	rotationSystem = t->getRotationSystem();
}

bool TetrominoKicker::checkKick(int rd)
{
	return rotationSystem->getCorrectPosition(rd) != sf::Vector2i();
}

void TetrominoKicker::kickTetromino(int rd)
{
	if (tetromino == nullptr) return;

	if (rd <= 0) tetromino->rotateLeft();
	else if (rd > 0) tetromino->rotateRight();

	kickMove = 
	tetromino->move()
}