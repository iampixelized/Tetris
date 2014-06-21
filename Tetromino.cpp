#include<iostream>
using std::cout;
using std::endl;
using std::boolalpha;

#include "Tetromino.hpp"

// NOTE: Next stop, determine first the immediate height and the blocks at those
// particular heights then do the gradual drop, ghost piece, hard drop, soft drop.

Tetromino::Tetromino(TetrominoType ttype, BlockColor bc, TetrisPlayField tpf, esc::AssetManager & am)
	: 
	blockRotationCount(0),
	type(ttype),
	color(bc),
	currentDirection(RotateTo::_0),
	_isDropped(false),
	face(0),
	playField(&tpf),
	moveCount(3),
	dropCount(0),
	isLateral(false)
{
	if (type == TetrominoType::S)
	{
		blockConfigurations._0Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 1));

		blockConfigurations._90Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(2, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(2, 2));

		blockConfigurations._180Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 1));

		blockConfigurations._270Config.push_back(sf::Vector2f(0, 0));
		blockConfigurations._270Config.push_back(sf::Vector2f(0, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 2));
	}
	else if (type == TetrominoType::Z)
	{
		blockConfigurations._0Config.push_back(sf::Vector2f(0, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 2));

		blockConfigurations._90Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(2, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(2, 0));

		blockConfigurations._180Config.push_back(sf::Vector2f(0, 1));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 2));

		blockConfigurations._270Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._270Config.push_back(sf::Vector2f(0, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 0));
	}
	else if (type == TetrominoType::J)
	{
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(0, 1));

		blockConfigurations._90Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 0));

		blockConfigurations._180Config.push_back(sf::Vector2f(0, 1));
		blockConfigurations._180Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 2));

		blockConfigurations._270Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._270Config.push_back(sf::Vector2f(2, 0));
	}
	else if (type == TetrominoType::L)
	{
		blockConfigurations._0Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(0, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 1));

		blockConfigurations._90Config.push_back(sf::Vector2f(0, 0));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 2));

		blockConfigurations._180Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 1));

		blockConfigurations._270Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._270Config.push_back(sf::Vector2f(2, 2));
	}
	else if (type == TetrominoType::I)
	{
		blockConfigurations._0Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(3, 2));

		blockConfigurations._90Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 3));

		blockConfigurations._180Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(3, 2));

		blockConfigurations._270Config.push_back(sf::Vector2f(2, 0));
		blockConfigurations._270Config.push_back(sf::Vector2f(2, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._270Config.push_back(sf::Vector2f(2, 3));
	}
	else if (type == TetrominoType::O)
	{
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 3));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 3));

		blockConfigurations._90Config = blockConfigurations._0Config;
		blockConfigurations._180Config = blockConfigurations._0Config;
		blockConfigurations._270Config = blockConfigurations._0Config;
	}
	else if (type == TetrominoType::T)
	{
		blockConfigurations._0Config.push_back(sf::Vector2f(0, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(2, 1));
		blockConfigurations._0Config.push_back(sf::Vector2f(1, 2));

		blockConfigurations._90Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._90Config.push_back(sf::Vector2f(0, 1));

		blockConfigurations._180Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 1));

		blockConfigurations._270Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._270Config.push_back(sf::Vector2f(2, 1));
	}

	if (type == TetrominoType::I)
	{
		hWidthOffset = 4;
		vWidthOffset = 1;
	}
	else if (type == TetrominoType::O)
		hWidthOffset = vWidthOffset = 2;
	else
	{
		hWidthOffset = 3;
		vWidthOffset = 2;
	}

	moveCount = (type == TetrominoType::O)? 4 : 3;
	blockPositions = blockConfigurations._0Config;
	playField = &tpf;
	blockSize = playField->getGridOffset();
	positionOffset = playField->getPosition();
	sizeOffset = playField->getFieldSize();

	string spriteName;

	switch (color)
	{
		case BlockColor::Blue:		spriteName = "blue_block";		break;
		case BlockColor::Cyan:		spriteName = "cyan_block";		break;
		case BlockColor::Green:		spriteName = "green_block";		break;
		case BlockColor::Orange:	spriteName = "orange_block";	break;
		case BlockColor::Purple:	spriteName = "purple_block";	break;
		case BlockColor::Red:		spriteName = "red_block";		break;
		case BlockColor::Yellow:	spriteName = "yellow_block";	break;
	}

	int pnum = 1;
	for (sf::Vector2f p : blockPositions)
	{
		sf::Vector2f actualPos;
		actualPos.x = (p.x * blockSize) + positionOffset.x + (blockSize * 3);
		actualPos.y = (p.y * blockSize) + positionOffset.y;

		palette.push_back(PiecePtr(new Piece(spriteName, actualPos, am, pnum)));
		palette[0]->perceivePlayField(tpf);
		pnum++;
	}
}

Tetromino::~Tetromino()
{ 

}

void Tetromino::rotateLeft()
{
	if (_isDropped) return;

	blockRotationCount--;
	isLateral = ((blockRotationCount % 2 != 0)) ? true : false;

	if (blockRotationCount < 0 || blockRotationCount == 3)
	{
		blockRotationCount = 3;
		blockPositions = blockConfigurations._270Config;
	}
	else if (blockRotationCount == 2)
		blockPositions = blockConfigurations._180Config;
	else if (blockRotationCount == 1)
		blockPositions = blockConfigurations._90Config;
	else if (blockRotationCount == 0)
	{
		blockPositions = blockConfigurations._0Config;
		blockRotationCount = 4;
	}

	face = blockRotationCount * 90;
	cout << "Face : " << face << endl;

	updatePieces(blockPositions);
	leftWallKick();
	rightWallKick();
}

void Tetromino::rotateRight()
{
	if (_isDropped) return;
	blockRotationCount++;
	isLateral = ((blockRotationCount % 2) != 0) ? true : false;

	if (blockRotationCount > 4 || blockRotationCount == 1)
	{
		blockRotationCount = 1;
		blockPositions = blockConfigurations._90Config;
	}
	else if (blockRotationCount == 2)
		blockPositions = blockConfigurations._180Config;
	else if (blockRotationCount == 3)
		blockPositions = blockConfigurations._270Config;
	else if (blockRotationCount == 4)
	{
		blockPositions = blockConfigurations._0Config;
		blockRotationCount = 0;
	}

	face = blockRotationCount * 90;
	cout << "Face : " << face << endl;

	updatePieces(blockPositions);
	leftWallKick();
	rightWallKick();
}

void Tetromino::moveRight()
{
	if (moveCount >= getRightMostBounds() || _isDropped)
		return;

	for (size_t i = 0; i < palette.size(); ++i)
	{
		sf::Vector2f curpos = palette[i].get()->getPosition();
		curpos.x += blockSize;

		palette[i].get()->setPosition(curpos);
	}

	moveCount++;
	cout << moveCount << endl;
}

void Tetromino::moveLeft()
{	
	if (moveCount <= getLeftMostBounds() || _isDropped)
		return;

	for (size_t i = 0; i < palette.size(); ++i)
	{
		sf::Vector2f curpos = palette[i].get()->getPosition();
		curpos.x -= blockSize;

		palette[i].get()->setPosition(curpos);
	}

	moveCount--;
	cout << moveCount << endl;
}

Tetromino::TetrominoType Tetromino::getType() const
{
	return type;
}

Tetromino * Tetromino::createTetromino
	(
		Tetromino::TetrominoType ttype, 
		Tetromino::BlockColor bc, 
		TetrisPlayField & tpf, 
		esc::AssetManager & am
	)
{
	return new Tetromino(ttype, bc, tpf, am);
}

void Tetromino::showObjectIDs() const
{
	for (size_t i = 0; i < palette.size(); ++i)
		cout << "Object " << i << " : " << palette[i].get()->getObjectID() << endl;
}

void Tetromino::showObjectPositions() const
{
	for (size_t i = 0; i < palette.size(); ++i)
		cout << "Object id: " << palette[i].get()->getObjectID() << " : "
			 << palette[i].get()->getPosition().x 
			 << " , " 
			 << palette[i].get()->getPosition().y 
			 << endl;
}

void Tetromino::updatePieces(const vector<sf::Vector2f> &pos)
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
	for (size_t i = 0; i < palette.size(); ++i)
		palette[i]->update(e);
}

void Tetromino::draw(sf::RenderWindow * window)
{
	for (size_t i = 0; i < palette.size(); ++i)
		palette[i].get()->draw(window);
}

void Tetromino::hardDrop()
{
	dropCount = (sizeOffset.y - 2) - 1;
	_isDropped = true;
}

void Tetromino::softDrop()
{
	if (dropCount >= (sizeOffset.y - 2) - 1)
	{
		_isDropped = true;
		return;
	}

	dropCount++;

	for (size_t i = 0; i < palette.size(); ++i)
		palette[i].get()->moveTo(sf::Vector2f(0.0f, blockSize));
}

bool Tetromino::isDropped() const
{
	return _isDropped;
}

TetrisPlayField * Tetromino::getPlayField() const
{
	return playField;
}

void Tetromino::removeBlock(int piece)
{

}

// Try logic, whenever rotation starts from the left or from the right.
int Tetromino::getRightMostBounds()
{
	int wo = (isLateral) ? vWidthOffset : hWidthOffset;
	
	if (type == TetrominoType::T ||
	    type == TetrominoType::L ||
	    type == TetrominoType::J)
	{
		return (face == 270) ? (sizeOffset.x - wo) - 1 : sizeOffset.x - wo;
	}
	else if (type == TetrominoType::S ||
			 type == TetrominoType::Z)
	{
		return (face == 90) ? (sizeOffset.x - wo) - 1 : sizeOffset.x - wo;
	}
	else if (type == TetrominoType::I)
	{
		if (face == 270)
			return (sizeOffset.x - wo) - 2;
		else if (face == 90)
			return (sizeOffset.x - wo) - 1;
	}

	return sizeOffset.x - wo;
}

int Tetromino::getLeftMostBounds()
{
	int wo = (isLateral) ? vWidthOffset : hWidthOffset;

	if (type == TetrominoType::T ||
		type == TetrominoType::L ||
		type == TetrominoType::J)
	{
		if (face == 270 )
			return -1;
	}
	else if (type == TetrominoType::S ||
			 type == TetrominoType::Z)
	{
		return (face == 90) ? -1 : 0;
	}
	else if (type == TetrominoType::I)
	{
		if (face == 270)
			return -2;
		else if (face == 90)
			return -1;
	}

	return 0;
}

void Tetromino::leftWallKick()
{
	if (moveCount >= getLeftMostBounds()) return;
	sf::Vector2f kickpos;

	switch (type)
	{
		case TetrominoType::L:
		case TetrominoType::J:
		case TetrominoType::T:
		case TetrominoType::S:
		case TetrominoType::Z:
		{
			kickpos.x = blockSize;
			moveCount++;
		}
		break;

		case TetrominoType::I:
		{
			if (face == 180)
			{
				kickpos.x = blockSize;
				moveCount++;
			}
			else if (face == 0)
			{
				kickpos.x = blockSize * 2;
				moveCount += 2;
			}
		}
		break;
	}

	for (size_t i = 0; i < palette.size(); ++i)
	{
		sf::Vector2f actualPos;
		actualPos.x = palette[i].get()->getPosition().x + kickpos.x;
		actualPos.y = palette[i].get()->getPosition().y + kickpos.y;

		palette[i].get()->setPosition(actualPos);
	}

	cout << "Wall kick detected! face: " << face << " move count : " << moveCount << " (LEFT): +" << kickpos.x << endl;
}

void Tetromino::rightWallKick()
{
	if (moveCount <= getRightMostBounds()) return;

	sf::Vector2f kickpos;
	
	switch (type)
	{
		case TetrominoType::L:
		case TetrominoType::J:
		case TetrominoType::T:
		case TetrominoType::S:
		case TetrominoType::Z:
		{
			kickpos.x = -blockSize;
			moveCount--;
		}
		break;

		case TetrominoType::I:
		{
			if (face == 0)
			{
				kickpos.x -= blockSize;
				moveCount--;
			}
			else if (face == 180)
			{
				kickpos.x = -blockSize * 2;
				moveCount-=2;
			}
		}
		break;
	}

	for (size_t i = 0; i < palette.size(); ++i)
	{
		sf::Vector2f actualPos;
		actualPos.x = palette[i].get()->getPosition().x + kickpos.x;
		actualPos.y = palette[i].get()->getPosition().y + kickpos.y;

		palette[i].get()->setPosition(actualPos);
	}

	cout << "Wall kick detected! face: " << face << " move count : " << moveCount << " (RIGHT): +" << kickpos.x << endl;
}
