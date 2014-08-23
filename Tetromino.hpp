#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include<vector>
using std::vector;

#include <memory>
using std::unique_ptr;
using std::make_unique;

#include<map>
using std::map;
using std::pair;
using std::make_pair;

#include "TetrisPlayField.hpp"
#include "Block.hpp"
#include "ObjectLayer.hpp"

class RotationSystem;

struct Mechanics
{
	float dropInterval = 2.0f;
	float lockTime     = 0.8f;

	Mechanics(RotationSystem & rs) : rotationSystem(&rs){}
	RotationSystem * getRotationSystem() const {return rotationSystem; }
	
	private:
		RotationSystem * rotationSystem;
};

class Tetromino
{
	public:

		typedef unique_ptr<Block> BlockPtr;
		typedef map<int, BlockPtr> BlockPalette;

		enum TetrominoType{ S = 1, Z, J, L, I, O, T, DOT };
		enum BlockColor{ Cyan, Yellow, Purple, Green, Red, Blue, Orange, Ghost };
		
		virtual ~Tetromino();

		RotationSystem * getRotationSystem();

		void rotateLeft();
		void rotateRight();
		void setRotation(int);
		int getRotation() const;
		void setGridPosition(const sf::Vector2i &);
		sf::Vector2i getGridPosition();

		void hardDrop(bool = true);
		void softDrop(bool = true);
		bool isLocked() const;

		void moveRight();
		void moveLeft();
		void move(const sf::Vector2i &);
		int getMoveCount() const;
		int getDropCount() const;

		TetrominoType getType() const;
		const vector<sf::Vector2i> & getCurrentConfiguration() const;
		static Tetromino * createTetromino(TetrominoType, BlockColor, TetrisPlayField &, Mechanics & , esc::AssetManager &);

		void update(float);
		void draw(sf::RenderWindow *);

		TetrisPlayField * getPlayField() const;
		int getID() const;
		Block * getBlock(int);

		bool checkRotation(int);
		bool checkMovement(int);
		int getBlockCount() const;

		void setMimic(Tetromino * mimic);
		Tetromino * getMimic() const;

	protected:

		Tetromino
		(
			  TetrominoType
			, BlockColor
			, TetrisPlayField    &
			, Mechanics		     &
			, esc::AssetManager  &
		);

		Tetromino(){}
		void updatePalette(const vector<sf::Vector2i> &);
		void updateMimic();

	private:
		
		static int id_generator;
		int id;

		float blockSize;
		int blockRotationCount;

		Tetromino * mimic;
		RotationSystem * rotationSystem;
		TetrominoType type;
		BlockColor color;
		vector<sf::Vector2i> blockPositions;

		BlockPalette palette;

		float lockTime;
		float dropInterval;
		float dropElapsed;
		float lockElapsed;

		bool _isLocked;
		bool _isDeployed;
		int face;
		int previousFace;
		
		TetrisPlayField * playField;
		sf::Vector2f positionOffset;
		
		int hWidthOffset;
		int vWidthOffset;
		int moveCount;
		int dropCount;
		int blockCount;
};	

#endif