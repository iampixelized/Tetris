#include "SRS.hpp"

SRS::SRS(Tetromino::TetrominoType type)
	: RotationSystem("Super Rotation System (SRS)")
{
	if (type == Tetromino::TetrominoType::S)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 0));

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
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 2));
	}
	else if (type == Tetromino::TetrominoType::J)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 0));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 2));
	}
	else if (type == Tetromino::TetrominoType::L)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 0));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 2));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 2));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
	}
	else if (type == Tetromino::TetrominoType::I)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(3, 1));

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
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 0));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._90Config = RotationSystem::bConfig._0Config;
		RotationSystem::bConfig._180Config = RotationSystem::bConfig._0Config;
		RotationSystem::bConfig._270Config = RotationSystem::bConfig._0Config;
	}
	else if (type == Tetromino::TetrominoType::T)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(1, 0));

		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._90Config.push_back(sf::Vector2i(2, 1));

		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(0, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(2, 1));
		RotationSystem::bConfig._180Config.push_back(sf::Vector2i(1, 2));

		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 0));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 1));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(1, 2));
		RotationSystem::bConfig._270Config.push_back(sf::Vector2i(0, 1));
	}
	else if (type == Tetromino::TetrominoType::DOT)
	{
		RotationSystem::bConfig._0Config.push_back(sf::Vector2i(0, 0));
		RotationSystem::bConfig._90Config = RotationSystem::bConfig._0Config;
		RotationSystem::bConfig._180Config = RotationSystem::bConfig._180Config;
		RotationSystem::bConfig._270Config = RotationSystem::bConfig._270Config;
	}
}

SRS::~SRS()
{

}

SRS * SRS::getStandard()
{
	return this;
}