#include "DRS.hpp"
#include "Tetromino.hpp"

DRS::DRS() : RotationSystem("DTET Rotation System (DRS)")
{
	checkTable.insert(make_pair("Left"  , map<int, sf::Vector2i>()));
	checkTable.insert(make_pair("Right" , map<int, sf::Vector2i>()));

	checkTable["left"].insert(make_pair(1, sf::Vector2i(-1, 0)));
	checkTable["left"].insert(make_pair(2, sf::Vector2i( 1, 0)));
	checkTable["left"].insert(make_pair(3, sf::Vector2i( 0, 1)));
	checkTable["left"].insert(make_pair(4, sf::Vector2i(-1, 1)));
	checkTable["left"].insert(make_pair(5, sf::Vector2i( 1, 1)));
	checkTable["left"].insert(make_pair(6, sf::Vector2i(-2, 0))); // for I Tetromino

	checkTable["right"].insert(make_pair(1, sf::Vector2i( 1, 0)));
	checkTable["right"].insert(make_pair(2, sf::Vector2i(-1, 0)));
	checkTable["right"].insert(make_pair(3, sf::Vector2i( 0, 1)));
	checkTable["right"].insert(make_pair(4, sf::Vector2i( 1, 1)));
	checkTable["right"].insert(make_pair(5, sf::Vector2i(-1, 1)));
	checkTable["right"].insert(make_pair(6, sf::Vector2i( 2, 0))); // for I Tetromino

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
	RotationSystem::reset();

	if (type == Tetromino::TetrominoType::S)
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
	else if (type == Tetromino::TetrominoType::Z)
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
	else if (type == Tetromino::TetrominoType::J)
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
	else if (type == Tetromino::TetrominoType::L)
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
	else if (type == Tetromino::TetrominoType::I)
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
	else if (type == Tetromino::TetrominoType::O)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._90Config  = RotationSystem::bConfig._0Config;
		RotationSystem::bConfig._180Config = RotationSystem::bConfig._0Config;
		RotationSystem::bConfig._270Config = RotationSystem::bConfig._0Config;
	}
	else if (type == Tetromino::TetrominoType::T)
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
	else if (type == Tetromino::TetrominoType::DOT)
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
	if (	   type == Tetromino::TetrominoType::S  
			|| type == Tetromino::TetrominoType::Z
			|| type == Tetromino::TetrominoType::J
			|| type == Tetromino::TetrominoType::L
			|| type == Tetromino::TetrominoType::O
			|| type == Tetromino::TetrominoType::T
		)
		
		return 1;

	else if (type == Tetromino::TetrominoType::I)
		return 2;

	return 0;
}