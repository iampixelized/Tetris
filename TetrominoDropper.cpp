#include<iostream>
using std::cout;
using std::endl;

#include "TetrominoDropper.hpp"

TetrominoDropper::TetrominoDropper()
	: 
	dropInterval(0.0f)
	, lockTime(0.0f)
	, lockElapsed(0.0f)
	, dropElapsed(0.0f)
{

}

TetrominoDropper::~TetrominoDropper()
{

}

void TetrominoDropper::setTetromino(Tetromino * t)
{
	if (t == nullptr) return;

	host = t;
	playField = host->getPlayField();
}

void TetrominoDropper::update(float e)
{
	if (host == nullptr) return;
	if (host->getType() == TetrominoType::DOT)
		return;

	host->update(e);

	if (host->isDeployed())
	{
		if (host->isLocked()) return;
		
		lockElapsed += e;
		if (lockElapsed >= lockTime)
		{
			if (host->checkMovement(0))
			{
				host->deploy(true);
				lockElapsed = 0.0f;
			}
			else
			{
				host->lock();
				return;
			}
		}
	}

	dropElapsed += e;
	if (dropElapsed >= dropInterval)
	{
		softDrop();
		dropElapsed = 0.0f;
	}
}

void TetrominoDropper::softDrop(bool deployable)
{	
	if (!host->checkMovement(0))
	{
		host->deploy(deployable);
		return;
	}

	host->move(sf::Vector2i(0,1));
}

void TetrominoDropper::hardDrop(bool deployable)
{
	if (host == nullptr) return;

	for (int i = 0; i < playField->getFieldSize().y-2; ++i)
		softDrop(deployable);

	host->lock();
}

void TetrominoDropper::setDropInterval(float d)
{
	dropInterval = (d < 0.0f)? 0 : d;
}

float TetrominoDropper::getDropInterval() const
{
	return dropInterval;
}

void TetrominoDropper::setLockInterval(float l)
{
	lockTime = (l < 0.0f)? 0.0f : l;
}

float TetrominoDropper::getLockInterval() const
{
	return lockTime;
}


