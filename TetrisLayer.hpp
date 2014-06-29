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

		TetrisLayer(TetrisPlayField &, esc::AssetManager &);
		virtual ~TetrisLayer();

		//virtual void refreshLayer(float, sf::RenderWindow * , bool = true);
		//virtual void pauseLayer(bool = true);

		void spawnTetromino();
		Tetromino * getCurrentTetromino();

		void insertPiece(Tetromino::TetrominoType, Tetromino::BlockColor, const sf::Vector2i &, int = 0);


	private:

		void randomizeBag();

		TetrisPlayField * tetrisPlayField;
		esc::AssetManager * assetManager;
		Tetromino * currentTetromino;
		
		vector<pair<Tetromino::TetrominoType, Tetromino::BlockColor>> bag;
		vector<string> possiblePermutations;

		int spawnCount;
		esc::RandomGenerator random;
};

#endif