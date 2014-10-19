#include "DRS.hpp"
#include "Tetromino.hpp"

DRS::DRS(TetrisPlayField & tpf) : RotationSystem("DTET Rotation System (DRS)", tpf)
{
	checkTable.insert(make_pair( -1 , vector<sf::Vector2i>())); // Left
	checkTable.insert(make_pair(  1 , vector<sf::Vector2i>())); // Right

	checkTable[-1].push_back(sf::Vector2i(-1, 0));
	checkTable[-1].push_back(sf::Vector2i( 1, 0));
	checkTable[-1].push_back(sf::Vector2i( 0, 1));
	checkTable[-1].push_back(sf::Vector2i(-1, 1));
	checkTable[-1].push_back(sf::Vector2i( 1, 1));
	checkTable[-1].push_back(sf::Vector2i(-2, 0)); // for I Tetromino
	checkTable[-1].push_back(sf::Vector2i(-3, 0));

	checkTable[ 1].push_back(sf::Vector2i( 1, 0));
	checkTable[ 1].push_back(sf::Vector2i(-1, 0));
	checkTable[ 1].push_back(sf::Vector2i( 0, 1));
	checkTable[ 1].push_back(sf::Vector2i( 1, 1));
	checkTable[ 1].push_back(sf::Vector2i(-1, 1));
	checkTable[ 1].push_back(sf::Vector2i( 2, 0)); // for I Tetromino
	checkTable[ 1].push_back(sf::Vector2i(-2, 0));
}

DRS::~DRS()
{

}

DRS * DRS::getStandard()
{
	return this;
}

void DRS::setConfiguration(int type)
{
	RotationSystem::resetConfigurations();

	if (type == TetrominoType::S)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
	}
	else if (type == TetrominoType::Z)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 2));
	}
	else if (type == TetrominoType::J)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(0, 2));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(2, 0));
	}
	else if (type == TetrominoType::L)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(2, 2));
	}
	else if (type == TetrominoType::I)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(3, 2));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 2));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 3));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(3, 2));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 3));
	}
	else if (type == TetrominoType::O)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._90Config  = RotationSystem::bConfig._0Config;
		RotationSystem::bConfig._180Config = RotationSystem::bConfig._0Config;
		RotationSystem::bConfig._270Config = RotationSystem::bConfig._0Config;
	}
	else if (type == TetrominoType::T)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 2));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(0, 1));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 1));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(2, 1));
	}
	else if (type == TetrominoType::DOT)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 0));
	}
}

int DRS::getSpawningPosition(int type)
{
	//S = 1, Z, J, L, I, O, T, DOT
	return (type != TetrominoType::I)? 1 : 2;
}

sf::Vector2i DRS::getCorrectPosition(int d)
{	
	int dir = (d <= 0)? -1 : 1;
	sf::Vector2i kickPosition;
	int cface = RotationSystem::getCurrentFace() + (90*dir);
 
	for (size_t test = 0; test < checkTable[dir].size(); ++test)
	{
		sf::Vector2i cmove = checkTable[dir][test];
		
		if (RotationSystem::checkProjectedPosition(cmove, cface))
			return cmove;
	}

	return sf::Vector2i();
}

DRS * DRS::createNewInstance()
{
	return new DRS(*RotationSystem::getTetrisPlayField());
}