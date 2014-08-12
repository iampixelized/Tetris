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
{
	cout << "Tetris playfield was established:" << endl;
	cout << "Field Size : " << tetrisPlayField->getFieldSize().x << " " << tetrisPlayField->getFieldSize().y << endl;
	cout << "Offset     : " << tetrisPlayField->getGridOffset() << endl;
	cout << "Position   : " << tetrisPlayField->getPosition().x << " " << tetrisPlayField->getPosition().y << endl;

	permutateBag();
	random.seed();
	randomizeBag();
}

TetrominoLayer::~TetrominoLayer()
{

}

Tetromino * TetrominoLayer::spawnTetromino()
{
	if (spawnCount > 6)
	{
		spawnCount = 0;
		randomizeBag();
	}

	currentTetromino
		= Tetromino::createTetromino
		(  
			 bag[spawnCount].first
		  ,  bag[spawnCount].second
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
				bag[spawnCount].second,
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

	Tetromino::BlockColor color[] =
	{
		Tetromino::BlockColor::Blue,
		Tetromino::BlockColor::Cyan,
		Tetromino::BlockColor::Green,
		Tetromino::BlockColor::Orange,
		Tetromino::BlockColor::Purple,
		Tetromino::BlockColor::Red,
		Tetromino::BlockColor::Yellow
	};

	int rrange = random.randomIntWithinRange(0,possiblePermutations.size());
	int crange = random.randomIntWithinRange(0, 6);

	string tets = possiblePermutations[rrange];
	Tetromino::BlockColor rcolor = color[crange];

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
		
		bag.push_back(pair<Tetromino::TetrominoType, Tetromino::BlockColor>(ttype,rcolor));
	}
}
