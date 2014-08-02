#ifndef TETRISLAYER_HPP
#define TETRISLAYER_HPP

#include<vector>
using std::vector;

#include<map>
using std::pair;

#include "ObjectLayer.hpp"
#include "Tetromino.hpp"
#include "TetrisPlayField.hpp"
#include "AssetManager.hpp"
#include "RandomGenerator.hpp"

class TetrisLayer : public esc::ObjectLayer<Tetromino>
{

	public:

		TetrisLayer(Mechanics &, TetrisPlayField &, esc::AssetManager &);
		virtual ~TetrisLayer();

		Tetromino * spawnTetromino();
		void setDotPieces(int, const vector<int> &);
		void permutateBag();

	protected:

		virtual void update(float);

	private:
		
		void randomizeBag();
		void checkLineClear();

		TetrisPlayField * tetrisPlayField;
		esc::AssetManager * assetManager;
		Tetromino * currentTetromino;
		Mechanics * mechanics;
		
		vector<pair<Tetromino::TetrominoType, Tetromino::BlockColor>> bag;
		vector<string> possiblePermutations;

		int spawnCount;
		int rcount;

		esc::RandomGenerator random;
};

#endif