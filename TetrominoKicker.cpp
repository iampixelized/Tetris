#include "TetrominoKicker.hpp"

TetrominoKicker::TetrominoKicker(TetrisPlayField &tpf)
	: playField(&tpf), _isHostSet(false), _kickStatus(false)
{

}

TetrominoKicker::~TetrominoKicker()
{

}

void TetrominoKicker::setTetromino(Tetromino * tetromino)
{
	if (tetromino == nullptr)
		return;

	host = tetromino;
	_isHostSet = true;
	checkTable = tetromino->getRotationSystem()->getCheckTable();
}

bool TetrominoKicker::checkKick(const string &state, int rd)
{
	if (checkTable.find(state) == checkTable.end() && !_isHostSet)
		return false;

	int direction = (rd <= 0)? -1 : 1;
	int face = host->getRotation();
	vector<sf::Vector2i> assumedRotatedPositions;

	switch (face + (90*direction)) 
	{
	    case 0: case 360: case -360:
			assumedRotatedPositions = host->getRotationSystem()->getBlockConfiguration(0)   ; break;
		
		case 90 : case -90:
			assumedRotatedPositions = host->getRotationSystem()->getBlockConfiguration(90)  ; break;
		
		case 180: case -180:
			assumedRotatedPositions = host->getRotationSystem()->getBlockConfiguration(180) ; break;
		
		case 270: case -270: 
			assumedRotatedPositions = host->getRotationSystem()->getBlockConfiguration(270) ; break;
		
		default : 
			assumedRotatedPositions = host->getRotationSystem()->getBlockConfiguration(0)   ; break;
	}

	for (size_t test = 1; test <= checkTable[state].size(); ++test)
	{
		sf::Vector2i cmove = checkTable[state][test];
		cout << "Check move position : " << cmove.x << ' ' << cmove.y << endl;

		if (checkPosition(cmove, assumedRotatedPositions))
		{
			kickPosition = cmove;
			_kickStatus  = true;
			break;
		}
	}

	return _kickStatus;
}

void TetrominoKicker::kickTetromino(int rd)
{
	if (!_kickStatus && !_isHostSet) return;
	host->move(kickPosition);

	kickPosition = sf::Vector2i();
	_kickStatus = false;
}

bool TetrominoKicker::checkPosition(const sf::Vector2i &pos, const vector<sf::Vector2i> &rotations)
{
	int moveCount = host->getMoveCount();
	int dropCount = host->getDropCount();

	for (size_t i = 0; i < 4; ++i)
	{
		sf::Vector2i npos = rotations[i] + sf::Vector2i(moveCount, dropCount) + pos;
		
		if (playField->isActive(npos))
			return false;
	}

	return true;
}