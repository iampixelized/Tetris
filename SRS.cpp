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

	checkTable[-1][0  ] = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, -2), sf::Vector2i(1, -2) };
	checkTable[-1][180] = { sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(-1, -1), sf::Vector2i(0, 2), sf::Vector2i(-1, 2) };
	checkTable[-1][270] = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, -2), sf::Vector2i(1, -2) };
	checkTable[-1][90 ] = { sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(-1, -1), sf::Vector2i(0, 2), sf::Vector2i(-1, 2) };

	checkTable[ 1][0  ] = { sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, -2), sf::Vector2i(-1, -2) };
	checkTable[ 1][180] = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, -1), sf::Vector2i(0, 2), sf::Vector2i(1, 2) };
	checkTable[ 1][270] = { sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, -2), sf::Vector2i(-1, -2) };
	checkTable[ 1][90 ] = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, -1), sf::Vector2i(0, 2), sf::Vector2i(1, 2) };

	checkTableI[-1][0  ] = { sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 2), sf::Vector2i(2, -1) };
	checkTableI[-1][180] = { sf::Vector2i(0, 0), sf::Vector2i(-2, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, -1), sf::Vector2i(1, 2) };
	checkTableI[-1][270] = { sf::Vector2i(0, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 1), sf::Vector2i(-1, -2) };
	checkTableI[-1][90 ] = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, 0), sf::Vector2i(1, -2), sf::Vector2i(-2, 1) };

	checkTableI[ 1][0  ] = { sf::Vector2i(0, 0), sf::Vector2i(-2, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, -1), sf::Vector2i(1, 2) };
	checkTableI[ 1][180] = { sf::Vector2i(0, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 2), sf::Vector2i(2, -1) };
	checkTableI[ 1][270] = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(-2, 0), sf::Vector2i(1, -2), sf::Vector2i(-2, 1) };
	checkTableI[ 1][90 ] = { sf::Vector2i(0, 0), sf::Vector2i(2, 0), sf::Vector2i(-1, 0), sf::Vector2i(2, 1), sf::Vector2i(-1, -2) };
}

SRS::~SRS(){}

SRS * SRS::getStandard(){ return this; }

// Replace RS with the correct parameter type
void SRS::setConfiguration(int type)
{
	RotationSystem::resetConfigurations();
	hostType = static_cast<TetrominoType>(type);

	switch (type) 
	{
		case TetrominoType::I:
			
			RotationSystem::bConfig._0Config   = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(3, 1) };
			RotationSystem::bConfig._90Config  = { sf::Vector2i(2, 0), sf::Vector2i(2, 1), sf::Vector2i(2, 2), sf::Vector2i(2, 3) };
			RotationSystem::bConfig._180Config = { sf::Vector2i(0, 2), sf::Vector2i(1, 2), sf::Vector2i(2, 2), sf::Vector2i(3, 2) };
			RotationSystem::bConfig._270Config = { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2), sf::Vector2i(1, 3) };
			break;

		case TetrominoType::J:
			
			RotationSystem::bConfig._0Config   = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
			RotationSystem::bConfig._90Config  = { sf::Vector2i(2, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };
			RotationSystem::bConfig._180Config = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(2, 2) };
			RotationSystem::bConfig._270Config = { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2), sf::Vector2i(0, 2) };
			break;

		case TetrominoType::L:
			
			RotationSystem::bConfig._0Config   = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(2, 0) };
			RotationSystem::bConfig._90Config  = { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2), sf::Vector2i(2, 2) };
			RotationSystem::bConfig._180Config = { sf::Vector2i(0, 2), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
			RotationSystem::bConfig._270Config = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };
			break;

		case TetrominoType::O:
			
			RotationSystem::bConfig._0Config   = 
			RotationSystem::bConfig._90Config  =
			RotationSystem::bConfig._180Config = 
			RotationSystem::bConfig._270Config = { sf::Vector2i(1, 0), sf::Vector2i(2, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
			break;

		case TetrominoType::S:

			RotationSystem::bConfig._0Config   = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 0), sf::Vector2i(2, 0) };
			RotationSystem::bConfig._90Config  = { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(2, 2) };
			RotationSystem::bConfig._180Config = { sf::Vector2i(0, 2), sf::Vector2i(1, 2), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
			RotationSystem::bConfig._270Config = { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, 1), sf::Vector2i(0, 2) };
			break;

		case TetrominoType::T:
			
			RotationSystem::bConfig._0Config   = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(1, 0) };
			RotationSystem::bConfig._90Config  = { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2), sf::Vector2i(2, 1) };
			RotationSystem::bConfig._180Config = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(1, 2) };
			RotationSystem::bConfig._270Config = { sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2), sf::Vector2i(0, 1) };
			break;

		case TetrominoType::Z:
			
			RotationSystem::bConfig._0Config   = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
			RotationSystem::bConfig._90Config  = { sf::Vector2i(2, 0), sf::Vector2i(2, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };
			RotationSystem::bConfig._180Config = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 2), sf::Vector2i(2, 2) };
			RotationSystem::bConfig._270Config = { sf::Vector2i(0, 2), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 0) };
			break;
	}

}

int SRS::getSpawningPosition(int type)
{
	// Check if there is required offset...
	if (type != TetrominoType::I)
		return 0;

	return 1;
}

sf::Vector2i SRS::getCorrectPosition(int d)
{
	int dir = (d <= 0)? -1 : 1;
	sf::Vector2i kickPosition;
	int cface = RotationSystem::getCurrentFace() + 90;
	
	cface = (cface >= 360)? 0 : cface;
	cface = (cface < 0)? 270 : cface;

	vector<sf::Vector2i> & testList = (hostType != TetrominoType::I) ? checkTable[dir][cface] : checkTableI[dir][cface];
		
	for (size_t i = 0; i < testList.size(); ++i)
	{
		sf::Vector2i cmove = testList[i];
		cmove.y *= -1;

		if (RotationSystem::checkProjectedPosition(cmove, cface))
		{
			cout << "Moving : " << cmove.x << ' ' << cmove.y << endl;
			return cmove;
		}
	}

	return sf::Vector2i();
}

SRS * SRS::createNewInstance()
{
	return new SRS(*RotationSystem::getTetrisPlayField());
}