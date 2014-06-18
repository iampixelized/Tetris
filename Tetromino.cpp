#include<iostream>
using std::cout;
using std::endl;
using std::boolalpha;

#include "Tetromino.hpp"


Tetromino::Tetromino(TetrominoType ttype, BlockColor bc, TetrisPlayField tpf, esc::AssetManager & am)
	: 
		blockRotationCount(0),
		type(ttype),
		color(bc),
		currentDirection(RotateTo::_0),
		_isDeployed(false),
		face(0),
		playField(&tpf),
		moveCount(3),
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

		blockConfigurations._90Config.push_back(sf::Vector2f(2, 0));
		blockConfigurations._90Config.push_back(sf::Vector2f(2, 1));
		blockConfigurations._90Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._90Config.push_back(sf::Vector2f(2, 3));

		blockConfigurations._180Config.push_back(sf::Vector2f(0, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(2, 2));
		blockConfigurations._180Config.push_back(sf::Vector2f(3, 2));

		blockConfigurations._270Config.push_back(sf::Vector2f(1, 0));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 1));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 2));
		blockConfigurations._270Config.push_back(sf::Vector2f(1, 3));
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

	if (color == BlockColor::Blue)
		spriteName = "blue_block";
	else if (color == BlockColor::Cyan)
		spriteName = "cyan_block";
	else if (color == BlockColor::Green)
		spriteName = "green_block";
	else if (color == BlockColor::Orange)
		spriteName = "orange_block";
	else if (color == BlockColor::Purple)
		spriteName = "purple_block";
	else if (color == BlockColor::Red)
		spriteName = "red_block";
	else if (color == BlockColor::Yellow)
		spriteName = "yellow_block";

	for (sf::Vector2f p : blockPositions)
	{
		sf::Vector2f actualPos;
		actualPos.x = (p.x * blockSize) + positionOffset.x + (blockSize * 3);
		actualPos.y = (p.y * blockSize) + positionOffset.y;

		palette.push_back(PiecePtr(new Piece(spriteName, actualPos, am)));
	}
}

Tetromino::~Tetromino()
{ 

}

void Tetromino::rotateLeft()
{
	blockRotationCount--;
	isLateral = ((blockRotationCount % 2 != 0)) ? true : false;

	if (blockRotationCount == 3)
		blockPositions = blockConfigurations._270Config;
	else if (blockRotationCount == 2)
		blockPositions = blockConfigurations._180Config;
	else if (blockRotationCount == 1)
		blockPositions = blockConfigurations._90Config;
	else if (blockRotationCount == 0)
	{
		blockPositions = blockConfigurations._0Config;
		blockRotationCount = 4;
	}
	else if (blockRotationCount < 0)
	{
		blockRotationCount = 3;
		blockPositions = blockConfigurations._270Config;
	}

	face = blockRotationCount * 90;
	cout << "Face : " << face << endl;
	updatePieces(blockPositions);
}

void Tetromino::rotateRight()
{
	blockRotationCount++;
	isLateral = ((blockRotationCount % 2) != 0) ? true : false;

	if (blockRotationCount == 1)
		blockPositions = blockConfigurations._90Config;
	else if (blockRotationCount == 2)
		blockPositions = blockConfigurations._180Config;
	else if (blockRotationCount == 3)
		blockPositions = blockConfigurations._270Config;
	else if (blockRotationCount == 4)
	{
		blockPositions = blockConfigurations._0Config;
		blockRotationCount = 0;
	}
	else if (blockRotationCount > 4)
	{
		blockRotationCount = 1;
		blockPositions = blockConfigurations._90Config;
	}

	face = blockRotationCount * 90;
	cout << "Face : " << face << endl;
	updatePieces(blockPositions);
}

void Tetromino::deploy()
{

}

bool Tetromino::isDeployed() const
{
	return _isDeployed;
}

void Tetromino::moveRight()
{
	if (moveCount >= getRightMostBounds())
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

// Fix the move offsetting for left and right movement!
// SRS causes problem with our computation
void Tetromino::moveLeft()
{
	
	int wo = (isLateral) ? vWidthOffset : hWidthOffset;
	int bounds = (face == 90 || face == 180 || face == 0)? 0 : -1;

	if (moveCount <= bounds)
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

Tetromino * Tetromino::createTetromino(Tetromino::TetrominoType ttype, Tetromino::BlockColor bc, TetrisPlayField & tpf, esc::AssetManager & am)
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
	for (size_t i = 0; i < pos.size(); ++i)
	{
		sf::Vector2f actualPos;
		
		actualPos.x = (pos[i].x * blockSize) + positionOffset.x  + (moveCount * blockSize);
		actualPos.y = (pos[i].y * blockSize) + positionOffset.y;

		palette[i].get()->setPosition(actualPos);
	}
}

void Tetromino::update(float e)
{

}

void Tetromino::draw(sf::RenderWindow * window)
{
	for (size_t i = 0; i < palette.size(); ++i)
	{
		palette[i].get()->draw(window);
	}
}

TetrisPlayField * Tetromino::getPlayField() const
{
	return playField;
}

int Tetromino::getRightMostBounds()
{
	int wo = (isLateral) ? vWidthOffset : hWidthOffset;

	if (type == TetrominoType::O)
	{
		return sizeOffset.x - wo;
	}
	else if (type == TetrominoType::T ||
			 type == TetrominoType::L ||
			 type == TetrominoType::J)
	{
		return (face == 270) ? (sizeOffset.x - wo) - 1 : sizeOffset.x - wo;
	}
	else if (type == TetrominoType::S ||
			 type == TetrominoType::Z)
	{

	}
	else if (type == TetrominoType::I)
	{

	}
}

int Tetromino::getLeftMostBounds()
{
	//int wo = (isLateral) ? vWidthOffset : hWidthOffset;

	//if (type == TetrominoType::O)
	//{

	//}
	//else if (type == TetrominoType::T ||
	//		 type == TetrominoType::L ||
	//		 type == TetrominoType::J)
	//{

	//}
	//else if (type == TetrominoType::S ||
	//		 type == TetrominoType::Z)
	//{

	//}
	//else if (type == TetrominoType::I)
	//{

	//}

	return 0;
}