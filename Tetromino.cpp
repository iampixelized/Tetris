#include<iostream>
using std::cout;
using std::endl;
using std::boolalpha;

#include "ObjectLayer.hpp"
#include "Tetromino.hpp"
#include "RotationSystem.hpp"


// NOTE: Next stop, determine first the immediate height and the blocks at those
// particular heights then do the gradual drop, ghost piece, hard drop, soft drop.

// TO DO:
//		1. Do research on SRS
//		2. For the meantime switch RS to DRS
//		3. Decouple RS from this class
//		4. Implement DRS and its wall kick

int Tetromino::id_generator = 0;

Tetromino::Tetromino
	(
		TetrominoType ttype			, 
		BlockColor bc				, 
		TetrisPlayField &tpf		, 
		Mechanics &tmech			,
		esc::AssetManager & am
	)
	: 
	  blockRotationCount(0)
	, dropElapsed(0.0f)
	, lockElapsed(0.0f)
	, lockTime(tmech.lockTime)
	, dropInterval(tmech.dropInterval)
	, rotationSystem(tmech.getRotationSystem())
	, type(ttype)
	, color(bc)
	, _isLocked(false)
	, _isDeployed(false)
	, face(0)
	, previousFace(face)
	, playField(&tpf)
	, moveCount(3)
	, dropCount(0)
	, blockCount(0)
{
	rotationSystem->setConfiguration(ttype);
	string spriteName;

	switch (color)
	{
		case BlockColor::Blue	:	spriteName = "blue_block";		break;
		case BlockColor::Cyan	:	spriteName = "cyan_block";		break;
		case BlockColor::Green	:	spriteName = "green_block";		break;
		case BlockColor::Orange	:	spriteName = "orange_block";	break;
		case BlockColor::Purple	:	spriteName = "purple_block";	break;
		case BlockColor::Red	:	spriteName = "red_block";		break;
		case BlockColor::Yellow	:	spriteName = "yellow_block";	break;
	}

	id = id_generator++;
	moveCount = (type == TetrominoType::O)? 4 : 3;
	
	blockPositions = rotationSystem->getBlockConfiguration(0);
	playField = &tpf;
	blockSize = playField->getGridOffset();
	positionOffset = playField->getPosition();


	int bnum = 0;
	for (sf::Vector2i p : blockPositions)
	{
		sf::Vector2f actualPos;
		actualPos.x = (p.x * blockSize) + positionOffset.x + (blockSize * 3);
		actualPos.y = ((p.y-((type == TetrominoType::I)? 1: 0)) * blockSize) + positionOffset.y;
		palette[bnum] = BlockPtr(new Block(spriteName, actualPos, tpf, am));
		bnum++;
	}

	blockCount = palette.size();
}

Tetromino::~Tetromino()
{ 

}

RotationSystem * Tetromino::getRotationSystem()
{
	return rotationSystem;
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

	cout << endl;
	cout << "Face      : " << face << endl;
	cout << "Next face : " << face + 90 << endl;
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

	cout << endl;
	cout << "Face      : " << face << endl;
	cout << "Next face : " << face + 90 << endl;
	cout << "Count     : " << blockRotationCount << endl;
}

void Tetromino::setRotation(int f)
{
	if ((f < 0 || face > 360) || checkRotation(1))
		return;

	face = f;
	blockRotationCount = face / 90;

	switch (f)
	{
		case 0   :
		case 360 :
			      blockPositions = rotationSystem->getBlockConfiguration(0); break;
		case 90 : blockPositions = rotationSystem->getBlockConfiguration(90); break;
		case 180: blockPositions = rotationSystem->getBlockConfiguration(180); break;
		case 270: blockPositions = rotationSystem->getBlockConfiguration(270); break;
	}

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

	for (size_t i = 0; i < palette.size(); ++i)
	{
		sf::Vector2f newpos;

		newpos.x = positionOffset.x + ((blockPositions[i].x + pos.x) * blockSize);
		newpos.y = positionOffset.y + ((blockPositions[i].y + pos.y) * blockSize);

		if (playField->isActive(newpos))
			return;

		palette[i]->setPosition(newpos);
	}

	moveCount = pos.x;
	dropCount = pos.y;
}

void Tetromino::moveRight()
{
	if (_isLocked) return;

	moveCount++;
	
	for (size_t i = 0; i < palette.size(); ++i)
		palette[i]->moveTo(sf::Vector2f(blockSize, 0));

	cout << "Moving (RIGHT): " << moveCount << endl;
	return;
}

void Tetromino::moveLeft()
{	
	if (_isLocked) return;

	moveCount--;

	for (size_t i = 0; i < palette.size(); ++i)
		palette[i]->moveTo(sf::Vector2f(-blockSize, 0));

	cout << "Moving (LEFT): " << moveCount << endl;
	return;
}

Tetromino::TetrominoType Tetromino::getType() const
{
	return type;
}

const vector<sf::Vector2i> & Tetromino::getCurrentConfiguration() const
{
	return blockPositions;
}

Tetromino * Tetromino::createTetromino
	(
		Tetromino::TetrominoType ttype, 
		Tetromino::BlockColor bc, 
		TetrisPlayField & tpf, 
		Mechanics & m,
		esc::AssetManager & am
	)
{
	return new Tetromino(ttype, bc, tpf, m, am);
}

void Tetromino::updatePalette(const vector<sf::Vector2i> &pos)
{
	if (type == TetrominoType::O) return;

	for (size_t i = 0; i < pos.size(); ++i)
	{
		sf::Vector2f actualPos;
		
		actualPos.x = (pos[i].x * blockSize) + positionOffset.x + (moveCount * blockSize);
		actualPos.y = (pos[i].y * blockSize) + positionOffset.y + (dropCount * blockSize);

		palette[i]->setPosition(actualPos);
	}
}

void Tetromino::update(float e)
{
	cout << "fdafalsfjlkjsdaf" << endl;
	if (type == TetrominoType::DOT)
		return;
	
	if (_isDeployed)
	{
		if (_isLocked) return;

		lockElapsed += e;
		if (lockElapsed >= lockTime)
		{
			if (checkMovement(0))
			{
				_isDeployed = false;
				lockElapsed = 0.0f;
			}
			else
			{
				_isLocked = true;
				return;
			}
		}
	}

	// update gradual drop here
	dropElapsed += e;
	if (dropElapsed >= dropInterval)
	{
		softDrop();
		dropElapsed = 0.0f;
	}
}

void Tetromino::draw(sf::RenderWindow * window)
{
	for (size_t i = 0; i < palette.size(); ++i)
	{
		palette[i]->draw(window);
	}
}

void Tetromino::hardDrop()
{

	//deploy();
}

void Tetromino::softDrop()
{
	if (!checkMovement(0))
	{
		_isDeployed = true;
		return;
	}

	dropCount++;

	for (size_t i = 0; i < palette.size(); ++i)
		palette[i]->moveTo(sf::Vector2f(0, blockSize));

	cout << "Dropcount : " << dropCount << endl;
}

void Tetromino::move(const sf::Vector2i &pos)
{
	moveCount += pos.x;
	dropCount += pos.y;

	for (size_t i = 0; i < palette.size(); ++i)
	{
		palette[i]->moveTo(sf::Vector2f(pos.x * blockSize, pos.y * blockSize));
	}
}

int Tetromino::getMoveCount() const{return moveCount;}

int Tetromino::getDropCount() const{return dropCount;}

bool Tetromino::isLocked() const
{
	return _isLocked;
}

TetrisPlayField * Tetromino::getPlayField() const
{
	return playField;
}

int Tetromino::getID() const
{
	return id;
}

Block * Tetromino::getBlock(int pid)
{
	if (palette.find(pid) == palette.end())
		return nullptr;

	return palette[pid].get();
}

bool Tetromino::checkRotation(int rd)
{	
	int direction = (rd<=0)? -1 : 1;
	vector<sf::Vector2i> predictedRotatedPositions;
	predictedRotatedPositions = rotationSystem->getBlockConfiguration(face + (90*direction));

	for (size_t i = 0; i < predictedRotatedPositions.size(); ++i)
	{
		sf::Vector2f pos;
		pos.x = ((predictedRotatedPositions[i].x + moveCount) * blockSize) + positionOffset.x;
		pos.y = ((predictedRotatedPositions[i].y + dropCount) * blockSize) + positionOffset.y;

		sf::Vector2i gridpos;
		gridpos.x = (pos.x - positionOffset.x) / blockSize;
		gridpos.y = (pos.y - positionOffset.y) / blockSize;
		
		if (!playField->isWithinBounds(gridpos))
			return false;

		if (playField->isActive(gridpos))
			return false;
	}

	return true;
} 

bool Tetromino::checkMovement(int direction)
{	
	if (direction <= 0)
	{
		for (size_t i = 0; i < palette.size(); ++i)
		{
			sf::Vector2f pos = palette[i]->getPosition();
			
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
		for (size_t i = palette.size(); i > 0; --i)
		{
			sf::Vector2f pos = palette[i-1]->getPosition();
			pos.x += blockSize;

			if (!playField->isWithinBounds(pos))
				return false;

			if (playField->isActive(pos))
				return false;
		}
	}

	return true;
}

int Tetromino::getBlockCount() const
{
	return blockCount;
}

//void Tetromino::registerToField(TetrisPlayField & tpf)
//{
//	
//}