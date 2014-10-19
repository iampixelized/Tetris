#include<iostream>
using std::cout;
using std::endl;
using std::boolalpha;

#include<utility>
using std::move;

#include "ObjectLayer.hpp"
#include "Tetromino.hpp"

int Tetromino::id_generator = 0;

Tetromino::Tetromino
	(
		TetrominoType ttype
		, BlockColor bc
		, RPtr rs
		, esc::AssetManager	& am
	)
	:
	  blockRotationCount(0)
	, mimic(nullptr)
	, rotationSystem(std::move(rs))
	, type(ttype)
	, color(bc)
	, _isLocked(false)
	, _isDeployed(false)
	, face(0)
	, playField(rotationSystem->getTetrisPlayField())
	, moveCount(sf::Vector2i(3,0))
{
	rotationSystem->setConfiguration(ttype);
	string spriteName;

	switch (color)
	{
		case BlockColor::Blue	: spriteName = "blue_block";	break;
		case BlockColor::Cyan	: spriteName = "cyan_block";	break;
		case BlockColor::Green	: spriteName = "green_block";	break;
		case BlockColor::Orange	: spriteName = "orange_block";	break;
		case BlockColor::Purple	: spriteName = "purple_block";	break;
		case BlockColor::Red	: spriteName = "red_block";		break;
		case BlockColor::Yellow	: spriteName = "yellow_block";	break;
		case BlockColor::Ghost	: spriteName = "ghost_block";	break;
	}

	id = id_generator++;
	moveCount.x = (type == TetrominoType::O) ? 4 : 3;

	blockPositions = rotationSystem->getBlockConfiguration(0);
	blockSize = playField->getGridOffset();
	positionOffset = playField->getPosition();

	int sp = rotationSystem->getSpawningPosition(type);
	int bnum = 0;

	for (sf::Vector2i p : blockPositions)
	{
		sf::Vector2f actualPos;
		actualPos.x = (p.x * blockSize) + positionOffset.x + (blockSize * 3);
		actualPos.y = ((p.y - sp) * blockSize) + positionOffset.y;
		blocks.addNewObject(new Block(spriteName, actualPos, *playField, am , bnum));
		bnum++;
	}

	move(sf::Vector2i(0,2));
	rotationSystem->updateCurrentPosition(moveCount);
	rotationSystem->updateCurrentFace(face);
}

Tetromino::~Tetromino(){}

RotationSystem * Tetromino::getRotationSystem()
{
	return rotationSystem.get();
}

void Tetromino::kick(int rd)
{
	if (rotationSystem->isKickEnabled() && kickPos != sf::Vector2i())
	{
		if (rd <= 0) rotateLeft();
		else rotateRight();

		move(kickPos);
		updateMimic();
		kickPos = sf::Vector2i();
	}
}

void Tetromino::rotateLeft()
{
	if (_isLocked) return;

	blockRotationCount--;

	if (blockRotationCount < 0 || blockRotationCount == 3)
	{
		blockRotationCount = 3;
		blockPositions = rotationSystem->getBlockConfiguration(270);
	}
	else if (blockRotationCount == 2)
	{
		blockPositions = rotationSystem->getBlockConfiguration(180);
	}
	else if (blockRotationCount == 1)
	{
		blockPositions = rotationSystem->getBlockConfiguration(90);
	}
	else if (blockRotationCount == 0)
	{
		blockPositions = rotationSystem->getBlockConfiguration(0);
		blockRotationCount = 4;
	}

	face = blockRotationCount * 90;
	updatePalette(blockPositions);
	updateMimic();
}

void Tetromino::rotateRight()
{
	if (_isLocked) return;

	blockRotationCount++;

	if (blockRotationCount > 4 || blockRotationCount == 1)
	{
		blockRotationCount = 1;
		blockPositions = rotationSystem->getBlockConfiguration(90);
	}
	else if (blockRotationCount == 2)
		blockPositions = rotationSystem->getBlockConfiguration(180);
	else if (blockRotationCount == 3)
		blockPositions = rotationSystem->getBlockConfiguration(270);
	else if (blockRotationCount == 4)
	{
		blockPositions = rotationSystem->getBlockConfiguration(0);
		blockRotationCount = 0;
	}

	face = blockRotationCount * 90;
	updatePalette(blockPositions);
	updateMimic();
}

void Tetromino::setRotation(int f)
{
	if ((f < 0 || face > 360) || checkRotation(1))
		return;

	face = f;
	blockRotationCount = face / 90;
	blockPositions = rotationSystem->getBlockConfiguration(blockRotationCount);
	updatePalette(blockPositions);
}

int Tetromino::getRotation() const
{
	return face;
}

void Tetromino::setGridPosition(const sf::Vector2i &pos)
{
	if (!playField->isWithinBounds(pos))
		return;

	for (size_t i = 0; i < blocks.getSize(); ++i)
	{
		sf::Vector2f newpos;

		newpos.x = positionOffset.x + ((blockPositions[i].x + pos.x) * blockSize);
		newpos.y = positionOffset.y + ((blockPositions[i].y + pos.y) * blockSize);

		if (playField->isActive(newpos))
			return;

		blocks.getObject(0)->setPosition(newpos);
	}
	
	moveCount = pos;
	rotationSystem->updateCurrentPosition(moveCount);
}

sf::Vector2i Tetromino::getGridPosition()
{
	return moveCount;
}

void Tetromino::moveRight()
{
	if (_isLocked) return;

	moveCount.x++;

	for (size_t i = 0; i < blocks.getSize(); ++i)
		blocks.getObject(i)->moveTo(sf::Vector2f(blockSize,0));

	updateMimic();
	rotationSystem->updateCurrentPosition(moveCount);
}

void Tetromino::moveLeft()
{
	if (_isLocked) return;

	moveCount.x--;

	for (size_t i = 0; i < blocks.getSize(); ++i)
		blocks.getObject(i)->moveTo(sf::Vector2f(-blockSize, 0));

	updateMimic();
	rotationSystem->updateCurrentPosition(moveCount);
}

TetrominoType Tetromino::getType() const
{
	return type;
}

const vector<sf::Vector2i> & Tetromino::getCurrentConfiguration() const
{
	return blockPositions;
}

Tetromino * Tetromino::createTetromino
	(
		  TetrominoType ttype
		, Tetromino::BlockColor bc
		, RPtr rs
		, esc::AssetManager & am
	)
{
	return new Tetromino(ttype, bc, std::move(rs), am);
}

void Tetromino::updatePalette(const vector<sf::Vector2i> &pos)
{
	if (type == TetrominoType::O) return;

	for (size_t i = 0; i < blocks.getSize(); ++i)
	{
		sf::Vector2f actualPos;

		actualPos.x = (pos[i].x * blockSize) + positionOffset.x + (moveCount.x * blockSize);
		actualPos.y = (pos[i].y * blockSize) + positionOffset.y + (moveCount.y * blockSize);
		
		blocks.getObject(i)->setPosition(actualPos);
	}

	rotationSystem->updateCurrentFace(face);
}

void Tetromino::updateMimic()
{
	if (mimic == nullptr) return;

	for (size_t i = 0; i < blocks.getSize(); ++i)
	{
		sf::Vector2f pos = blocks.getObject(i)->getPosition();
		mimic->getBlock(i)->setPosition(pos);
	}
}

void Tetromino::update(float e)
{	
	blocks.updateLayer(e);
}

void Tetromino::draw(sf::RenderWindow * window)
{
	blocks.drawLayer(window);
}

void Tetromino::move(const sf::Vector2i &pos)
{
	if (!checkPosition(pos)) return;

	moveCount += pos;

	for (size_t i = 0; i < blocks.getSize(); ++i)
		blocks.getObject(i)->moveTo(sf::Vector2f(pos.x * blockSize, pos.y * blockSize));

	rotationSystem->updateCurrentPosition(moveCount);
}

void Tetromino::lock(){ _isLocked = true; }

bool Tetromino::isLocked() const{ return _isLocked;}

void Tetromino::deploy(bool deployable){ _isDeployed = deployable; }

bool Tetromino::isDeployed() const{ return _isDeployed; }

TetrisPlayField * Tetromino::getPlayField() const {return playField;}

int Tetromino::getID() const{ return id;}

Block * Tetromino::getBlock(int pid){ return blocks.getObject(pid);}

bool Tetromino::checkRotation(int rd)
{
	int direction = (rd <= 0) ? -1 : 1;
	vector<sf::Vector2i> predictedRotatedPositions;
	predictedRotatedPositions = rotationSystem->getBlockConfiguration(face + (90 * direction));

	for (size_t i = 0; i < blocks.getSize(); ++i)
	{
		sf::Vector2f pos;
		pos.x = ((predictedRotatedPositions[i].x + moveCount.x) * blockSize) + positionOffset.x;
		pos.y = ((predictedRotatedPositions[i].y + moveCount.y) * blockSize) + positionOffset.y;

		sf::Vector2i gridpos;
		gridpos.x = static_cast<int>((pos.x - positionOffset.x) / blockSize);
		gridpos.y = static_cast<int>((pos.y - positionOffset.y) / blockSize);

		if (!playField->isWithinBounds(gridpos) || playField->isActive(gridpos))
		{
			kickPos = rotationSystem->getCorrectPosition(direction);
			return false;
		}
	}

	return true;
}


bool Tetromino::checkMovement(int direction)
{
	if (direction <= 0)
	{
		for (size_t i = 0; i < blocks.getSize(); ++i)
		{
			sf::Vector2f pos = blocks.getObject(i)->getPosition();

			if (direction < 0)
				pos.x -= blockSize;
			else if (direction == 0)
				pos.y += blockSize;

			if (!playField->isWithinBounds(pos))
				return false;

			if (playField->isActive(pos))
				return false;
		}
	}
	else if (direction > 0)
	{
		for (size_t i = blocks.getSize(); i > 0; --i)
		{
			sf::Vector2f pos = blocks.getObject(i - 1)->getPosition();
			pos.x += blockSize;

			if (!playField->isWithinBounds(pos))
				return false;

			if (playField->isActive(pos))
				return false;
		}
	}

	return true;
}

bool Tetromino::checkPosition(const sf::Vector2i & ppos)
{
	for (size_t i = 0; i < blocks.getSize(); ++i)
	{
		sf::Vector2i pos = ppos + blocks.getObject(i)->getGridPosition();
		
		if (playField->isActive(pos))
			return false;
	}

	return true;
}

size_t Tetromino::getBlockCount() const{ return blocks.getSize(); }

void Tetromino::setMimic(Tetromino * t){ mimic = t;}

Tetromino * Tetromino::getMimic() const{ return mimic; }

bool Tetromino::isGarbageCollectible(){ return blocks.getSize() == 0; }