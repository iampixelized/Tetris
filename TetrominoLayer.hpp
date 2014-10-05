#ifndef TETROMINOLAYER_HPP
#define TETROMINOLAYER_HPP

#include<vector>
using std::vector;

#include<map>
using std::pair;

#include "ObjectLayer.hpp"
#include "Tetromino.hpp"
#include "AssetManager.hpp"
#include "RandomGenerator.hpp"
#include "TetrominoType.hpp"

class TetrisPlayField;

class TetrominoLayer : public esc::ObjectLayer<Tetromino>
{
	typedef esc::ObjectLayer<Tetromino> TLAYER;

	public:

		TetrominoLayer(RotationSystem &, esc::AssetManager &);
		virtual ~TetrominoLayer();

		Tetromino * spawnTetromino();
		void setDotPieces(int, const vector<int> &);
		void permutateBag();
		
	private:
		
		void randomizeBag();
		Tetromino::BlockColor getRandomColor();

		RotationSystem * rotationSystem;
		TetrisPlayField * tetrisPlayField;
		esc::AssetManager * assetManager;
		Tetromino * currentTetromino;
				
		vector<TetrominoType> bag;
		vector<string> possiblePermutations;

		int spawnCount;
		int pcount;

		esc::RandomGenerator random;
};

#endif