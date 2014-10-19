#include<iostream>
using std::cout;
using std::endl;

#include "RotationSystem.hpp"
#include "Tetromino.hpp"

RotationSystem::RotationSystem(const string & rsname , TetrisPlayField & tpf)
	: name(rsname), playField(&tpf), currentFace(0), _isKickEnabled(true)
{

}

RotationSystem::~RotationSystem()
{

}

void RotationSystem::resetConfigurations()
{
	bConfig._0Config.clear();
	bConfig._90Config.clear();
	bConfig._180Config.clear();
	bConfig._270Config.clear();
}

const vector<sf::Vector2i> & RotationSystem::getBlockConfiguration(int face)
{
	switch (face)
	{ 
		case 0: case 360: case -360:
			return bConfig._0Config;

		case 90: case -90:
			return bConfig._90Config;

		case 180: case -180:
			return bConfig._180Config;

		case 270: case -270:
			return bConfig._270Config;

		default:
			return bConfig._0Config;
	}
}

const vector<sf::Vector2i> & RotationSystem::getBlockNextConfiguration(int r)
{
	return getBlockConfiguration(r+90);
}

const vector<sf::Vector2i> & RotationSystem::getBlockPreviousConfiguration(int r)
{
	return getBlockConfiguration(r-90);
}

const RotationSystem::BlockConfigurations & RotationSystem::getBlockConfigurations()
{
	return bConfig;
}

RotationSystem * RotationSystem::getStandard()
{
	return this;
}

const string & RotationSystem::getStandardName() const
{
	return name;
}

int RotationSystem::getSpawningPosition(int type)
{
	return 0;
} 

void RotationSystem::updateCurrentPosition(const sf::Vector2i &npos)
{
	currentPosition = npos;
}

const sf::Vector2i & RotationSystem::getCurrentPosition() const
{
	return currentPosition;
}

void RotationSystem::updateCurrentFace(int face)
{
	currentFace = (face % 90 == 0) ? face : 0;
}

int RotationSystem::getCurrentFace() const
{
	return currentFace;
}

bool RotationSystem::checkProjectedPosition(const sf::Vector2i & ppos, int r)
{
	const vector<sf::Vector2i> & rotations = RotationSystem::getBlockConfiguration(r);
	
	for (size_t i = 0; i < rotations.size(); ++i)
	{
		sf::Vector2i npos = rotations[i] + currentPosition + ppos;

		cout << "\nChecking : " << npos.x << ' ' << npos.y;

		if (RotationSystem::getTetrisPlayField()->isActive(npos))
		{
			cout << " -- Active" << endl;
			return false;
		}
	}


	cout << endl;
	return true;
}

void RotationSystem::updateType(TetrominoType ttype)
{
	type = ttype;
}

TetrisPlayField * RotationSystem::getTetrisPlayField() const
{
	return playField;
}

void RotationSystem::setKickEnable(bool b)
{
	_isKickEnabled = b;
}

bool RotationSystem::isKickEnabled() const
{
	return _isKickEnabled;
}

TetrominoType RotationSystem::getHostType()
{
	return type;
}

void RotationSystem::resetCount()
{
	currentPosition = sf::Vector2i();
	currentFace = 0;
}