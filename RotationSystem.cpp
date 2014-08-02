#include "RotationSystem.hpp"

RotationSystem::RotationSystem(const string & rsname)
	: name(rsname)
{

}

RotationSystem::~RotationSystem()
{

}

void RotationSystem::reset()
{
	bConfig._0Config.clear();
	bConfig._90Config.clear();
	bConfig._180Config.clear();
	bConfig._270Config.clear();
}

const vector<sf::Vector2i> & RotationSystem::getBlockConfiguration(int r)
{
	if (r == 0 || r == 360)
		return bConfig._0Config;
	else if (r == 90)
		return bConfig._90Config;
	else if (r == 180)
		return bConfig._180Config;
	else if (r == 270)
		return bConfig._270Config;
	else
		return bConfig._0Config;
}

const RotationSystem::BlockConfigurations & RotationSystem::getBlockConfigurations()
{
	return bConfig;
}

const string & RotationSystem::getStandardName() const
{
	return name;
}

sf::Vector2i RotationSystem::getCheckTableTest(const string &tname, int tnum)
{
	if (checkTable.find(tname) == checkTable.end())
		if (checkTable[tname].find(tnum) == checkTable[tname].end())
			return sf::Vector2i();

		return checkTable[tname][tnum];
}

const RotationSystem::CheckTable & RotationSystem::getCheckTable() const
{
	return checkTable;
}

