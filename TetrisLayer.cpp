#include <algorithm>
using std::next_permutation;

#include "TetrisLayer.hpp"
#include "RandomGenerator.hpp"

TetrisLayer::TetrisLayer(TetrisPlayField & tpf, esc::AssetManager &am)
	:
	tetrisPlayField(&tpf),
	assetManager(&am),
	spawnCount(0)
{

	cout << "Tetris playfield was established:" << endl;
	cout << "Field Size : " << tetrisPlayField->getFieldSize().x << " " << tetrisPlayField->getFieldSize().y  << endl;
	cout << "Offset     : " << tetrisPlayField->getGridOffset() << endl;
	cout << "Position   : " << tetrisPlayField->getPosition().x << " " << tetrisPlayField->getPosition().y << endl;

	string tets = "IJLOSTZ";
	do
	{
		possiblePermutations.push_back(tets);
	} 
	while (next_permutation(tets.begin(), tets.end()));

	random.seed();
	randomizeBag();
}

TetrisLayer::~TetrisLayer()
{

}

//void TetrisLayer::refreshLayer(float e, sf::RenderWindow *window , bool pause)
//{
//
//}

void TetrisLayer::spawnTetromino()
{
	if (spawnCount > 6)
		randomizeBag();

	Tetromino * tetromino = currentTetromino = Tetromino::createTetromino(Tetromino::TetrominoType::L, bag[spawnCount].second, *tetrisPlayField, *assetManager);
	esc::ObjectLayer<Tetromino>::addNewObject(tetromino);
	spawnCount++;
}

Tetromino * TetrisLayer::getCurrentTetromino()
{
	return currentTetromino;
}

void TetrisLayer::insertPiece(Tetromino::TetrominoType ttype, Tetromino::BlockColor bc, const sf::Vector2i & pos, int face)
{
	Tetromino * tetromino = Tetromino::createTetromino(Tetromino::TetrominoType::L, bag[spawnCount].second, *tetrisPlayField, *assetManager);
	esc::ObjectLayer<Tetromino>::addNewObject(tetromino);
	tetromino->setGridPosition(pos);
	tetromino->setRotation(face);
}

void TetrisLayer::randomizeBag()
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