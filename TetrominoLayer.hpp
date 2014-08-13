#ifndef TETROMINOLAYER_HPP
#define TETROMINOLAYER_HPP

#include<vector>
using std::vector;

#include<map>
using std::pair;

#include "ObjectLayer.hpp"
#include "Tetromino.hpp"
#include "TetrisPlayField.hpp"
#include "AssetManager.hpp"
#include "RandomGenerator.hpp"

class TetrominoLayer : public esc::ObjectLayer<Tetromino>
{
	
	typedef esc::ObjectLayer<Tetromino> TLAYER;

	public:

	TetrominoLayer(Mechanics &, TetrisPlayField &, esc::AssetManager &);
	virtual ~TetrominoLayer();

		Tetromino * spawnTetromino();
		void setDotPieces(int, const vector<int> &);
		void permutateBag();

	private:
		
		void randomizeBag();

		TetrisPlayField * tetrisPlayField;
		esc::AssetManager * assetManager;
		Tetromino * currentTetromino;
		Mechanics * mechanics;
		
		vector<pair<Tetromino::TetrominoType, Tetromino::BlockColor>> bag;
		vector<string> possiblePermutations;

		int spawnCount;

		esc::RandomGenerator random;
};

#endif