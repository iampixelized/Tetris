#include "SRS.hpp"
#include "Tetromino.hpp"

SRS::SRS(TetrisPlayField & tpf) : RotationSystem("Super Rotation System (SRS)", tpf)
{
	checkTable.insert(make_pair(-1, map<int , vector<sf::Vector2i>>()));
	checkTable.insert(make_pair( 1, map<int , vector<sf::Vector2i>>()));
	checkTableI.insert(make_pair(-1, map<int, vector<sf::Vector2i>>()));
	checkTableI.insert(make_pair(1, map<int, vector<sf::Vector2i>>()));

	checkTable[-1].insert(make_pair(90  , vector<sf::Vector2i>())); // 0->L 
	checkTable[-1].insert(make_pair(180 , vector<sf::Vector2i>())); // L->2
	checkTable[-1].insert(make_pair(270 , vector<sf::Vector2i>())); // 2->L
	checkTable[-1].insert(make_pair(0   , vector<sf::Vector2i>())); // L->0

	checkTable[ 1].insert(make_pair(90  , vector<sf::Vector2i>())); // 0->R
	checkTable[ 1].insert(make_pair(180 , vector<sf::Vector2i>())); // R->2
	checkTable[ 1].insert(make_pair(270 , vector<sf::Vector2i>())); // 2->R
	checkTable[ 1].insert(make_pair(0   , vector<sf::Vector2i>())); // R->0

	// Recheck...

	checkTable[-1][90 ] = {sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(1,1), sf::Vector2i(0,-2), sf::Vector2i(1,-2)};
	checkTable[-1][180] = {sf::Vector2i(0,0), sf::Vector2i(-1,0), sf::Vector2i(-1,-1), sf::Vector2i(0,2), sf::Vector2i(-1,2)};
	checkTable[-1][270] = {sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(1,1), sf::Vector2i(0,-2), sf::Vector2i(1,-2)};
	checkTable[-1][0  ] = {sf::Vector2i(0,0), sf::Vector2i(-1,0), sf::Vector2i(-1,-1), sf::Vector2i(0,2), sf::Vector2i(-1,2)};

	checkTable[ 1][90 ] = {sf::Vector2i(0,0), sf::Vector2i(-1,0), sf::Vector2i(-1,1), sf::Vector2i(0,-2), sf::Vector2i(-1,-2)};
	checkTable[ 1][180] = {sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(1,-1), sf::Vector2i(0,2), sf::Vector2i(1,2)};
	checkTable[ 1][270] = {sf::Vector2i(0,0), sf::Vector2i(-1,0), sf::Vector2i(-1,1), sf::Vector2i(0,-2), sf::Vector2i(-1,-2)};
	checkTable[ 1][0  ] = {sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(1,-1), sf::Vector2i(0,2), sf::Vector2i(1,2)};

	checkTableI[-1][90 ] = {sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 2), sf::Vector2i(2, -1) };
	checkTableI[-1][180] = {sf::Vector2i(0, 0), sf::Vector2i(-2, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, -1), sf::Vector2i(-1, -2) };
	checkTableI[-1][270] = {sf::Vector2i(0, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 1), sf::Vector2i(-1, -2) };
	checkTableI[-1][0  ] = {sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, 0), sf::Vector2i(-1, 2), sf::Vector2i(2, -1) };

	checkTableI[ 1][90 ] = {sf::Vector2i(0, 0), sf::Vector2i(-2, 0), sf::Vector2i(1,0), sf::Vector2i(-2, -1), sf::Vector2i(1, 2) };
	checkTableI[ 1][180] = {sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(2,0), sf::Vector2i(-1, 2), sf::Vector2i(2, -1) };
	checkTableI[ 1][270] = {sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, 1), sf::Vector2i(1, -2), sf::Vector2i(-2, 1) };
	checkTableI[ 1][0  ] = {sf::Vector2i(0, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 1), sf::Vector2i(-1, -2) };
}

SRS::~SRS()
{

}

SRS * SRS::getStandard()
{
	return this;
}

void SRS::setConfiguration(int type)
{
	RotationSystem::reset();

}

int SRS::getSpawningPosition(int type)
{
	return 0;
}

sf::Vector2i SRS::getCorrectPosition(int dir)
{
	return sf::Vector2i();
}