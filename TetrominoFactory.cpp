#include <algorithm>
using std::next_permutation;
using std::random_shuffle;

#include<utility>
using std::move;

#include "RotationSystem.hpp"
#include "TetrominoFactory.hpp"
#include "RandomGenerator.hpp"

TetrominoFactory::TetrominoFactory(TLAYER & l, Tetromino::RPtr rs, esc::AssetManager &am)
	:
	  rotationSystem(std::move(rs))
	, tetrisPlayField(rotationSystem->getTetrisPlayField())
	, assetManager(&am)
	, spawnCount(0)
	, pcount(0)
	, layer(&l)
{
	tetrisPlayField = rotationSystem->getTetrisPlayField();
	permutateBag();
	randomizeBag();
	random.seed();
}

TetrominoFactory::~TetrominoFactory(){}

Tetromino * TetrominoFactory::spawnTetromino()
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
		  , std::move(Tetromino::RPtr(rotationSystem->createNewInstance()))
		  , *assetManager
		);

	layer->addNewObject(currentTetromino);
	spawnCount++;

	return currentTetromino;
}

Tetromino * TetrominoFactory::spawnTetromino(TetrominoType type, Tetromino::BlockColor color)
{
	currentTetromino = Tetromino::createTetromino(type, color, std::move(Tetromino::RPtr(rotationSystem->createNewInstance())), *assetManager);
	layer->addNewObject(currentTetromino);

	return currentTetromino;
}

void TetrominoFactory::permutateBag()
{
	possiblePermutations.clear();

	string tets = "IJLOSTZ";
	do
	{
		possiblePermutations.push_back(tets);
	}
	while (next_permutation(tets.begin(), tets.end()));

	random_shuffle(possiblePermutations.begin(), possiblePermutations.end());
}

void TetrominoFactory::randomizeBag()
{
	bag.clear();
	spawnCount = 0;

	int rrange = random.randomIntWithinRange(0, possiblePermutations.size());
	string tets = possiblePermutations[rrange];

	TetrominoType ttype;

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

Tetromino::BlockColor TetrominoFactory::getRandomColor()
{
	int crange = random.randomIntWithinRange(0, 6);	
	return static_cast<Tetromino::BlockColor>(crange);
}
