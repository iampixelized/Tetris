#ifndef TETROMINOKICKER_HPP
#define TETROMINOKICKER_HPP

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<map>
using std::map;
using std::pair;
using std::make_pair;

#include "Tetromino.hpp"
#include "RotationSystem.hpp"
#include "TetrisPlayField.hpp"

class TetrominoKicker 
{
	public:
		
		explicit TetrominoKicker(TetrisPlayField &);
		virtual ~TetrominoKicker();

		void setTetromino(Tetromino*);
		bool checkKick(const string &, int);
		void kickTetromino(int);

	private:
		
		bool checkPosition(const sf::Vector2i &, const vector<sf::Vector2i> &);

		RotationSystem::CheckTable checkTable;

		TetrisPlayField * playField;
		Tetromino * host;

		sf::Vector2i kickPosition;

		bool _isHostSet;
		bool _kickStatus;
};

#endif