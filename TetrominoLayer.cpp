#include <algorithm>
using std::next_permutation;

#include "TetrominoLayer.hpp"
#include "RandomGenerator.hpp"

TetrominoLayer::TetrominoLayer(Mechanics & m, TetrisPlayField & tpf, esc::AssetManager &am)
	:
	  tetrisPlayField(&tpf)
	, assetManager(&am)
	, mechanics(&m)
	, spawnCount(0)
	, pcount(0)
{
	cout << "Tetris playfield was established:" << endl;
	cout << "Field Size : " << tetrisPlayField->getFieldSize().x << " " << tetrisPlayField->getFieldSize().y << endl;
	cout << "Offset     : " << tetrisPlayField->getGridOffset() << endl;
	cout << "Position   : " << tetrisPlayField->getPosition().x << " " << tetrisPlayField->getPosition().y << endl;

	permutateBag();
	randomizeBag();
	random.seed();
}

TetrominoLayer::~TetrominoLayer()
{
}

Tetromino * TetrominoLayer::spawnTetromino()
{
	if ( (unsigned) pcount >= possiblePermutations.size())
	{
		permutateBag();
		pcount = 0;
	}

	if (spawnCount > 6)
	{
		pcount++;
		spawnCount = 0;
		randomizeBag();
	}

	currentTetromino
		= Tetromino::createTetromino
		(  
		    bag[spawnCount]
	      , getRandomColor()
		  , *tetrisPlayField
		  , *mechanics
		  , *assetManager
		);

	TLAYER::addNewObject(currentTetromino);
	spawnCount++;

	return currentTetromino;
}

void TetrominoLayer::setDotPieces(int line, const vector<int> & pieceLine)
{
	for (size_t i = 0; i < pieceLine.size(); ++i)
	{
		if (pieceLine[i] <= 0) continue;

		Tetromino * tetromino = Tetromino::createTetromino
			(
				Tetromino::TetrominoType::DOT,
				getRandomColor(),
				*tetrisPlayField,
				*mechanics,
				*assetManager
			);

		TLAYER::addNewObject(tetromino);
		tetromino->setGridPosition(sf::Vector2i(i, line));
		tetrisPlayField->registerBlocks(tetromino);
	}
}

void TetrominoLayer::permutateBag()
{
	possiblePermutations.clear();

	string tets = "IJLOSTZ";
	do
	{
		possiblePermutations.push_back(tets);
	}
	while (next_permutation(tets.begin(), tets.end()));
}

void TetrominoLayer::randomizeBag()
{
	bag.clear();
	spawnCount = 0;

	int rrange = random.randomIntWithinRange(0, possiblePermutations.size());
	string tets = possiblePermutations[rrange];

	Tetromino::TetrominoType ttype;

	for (char & t : tets)
	{
		if (t == 'I')
			ttype = TetrominoType::I;
		else if (t == 'J')
			ttype = TetrominoType::J;
		else if (t == 'L')
			ttype = TetrominoType::L;
		else if (t == 'O')
			ttype = TetrominoType::O;
		else if (t == 'T')
			ttype = TetrominoType::T;
		else if (t == 'S')
			ttype = TetrominoType::S;
		else if (t == 'Z')
			ttype = TetrominoType::Z;
		
		bag.push_back(ttype);
	}
}

Tetromino::BlockColor TetrominoLayer::getRandomColor()
{
	int crange = random.randomIntWithinRange(0, 6);	
	return static_cast<Tetromino::BlockColor>(crange);
}
