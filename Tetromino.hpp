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
#include "TetrominoType.hpp"

/*
	TO DO:
		1. Reimplement Ghost Pieces
		2. Finish SRS
		3. Test SRS

		Then(A MUST)
		4. Do batch processing on single spritesheet
		5. Review SFML tutorials on Vertex Arrays
*/

class RotationSystem;
class Mechanics;

class Tetromino
{
	public:

		typedef unique_ptr<Block> BlockPtr;

		enum BlockColor{ Cyan, Yellow, Purple, Green, Red, Blue, Orange, Ghost };
		
		virtual ~Tetromino();
		RotationSystem * getRotationSystem();

		void kick(int);
		void rotateLeft();
		void rotateRight();
		void setRotation(int);
		int getRotation() const;
		void setGridPosition(const sf::Vector2i &);
		sf::Vector2i getGridPosition();

		void lock();
		bool isLocked() const;
		
		void deploy(bool);
		bool isDeployed() const;

		void moveRight();
		void moveLeft();
		void move(const sf::Vector2i &);

		TetrominoType getType() const;
		const vector<sf::Vector2i> & getCurrentConfiguration() const;
		static Tetromino * createTetromino(TetrominoType, BlockColor, RotationSystem &, esc::AssetManager &);

		void update(float);
		void draw(sf::RenderWindow *);

		TetrisPlayField * getPlayField() const;
		int getID() const;
		Block * getBlock(int);

		bool checkRotation(int);
		bool checkMovement(int);
		bool checkPosition(const sf::Vector2i &);
		int getBlockCount() const;

		void setMimic(Tetromino * mimic);
		Tetromino * getMimic() const;
		void resetMimic();
		bool isGarbageCollectible();

	protected:

		Tetromino
		(
			  TetrominoType
			, BlockColor
			, RotationSystem &
			, esc::AssetManager &
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

		esc::ObjectLayer<Block> blocks;

		bool _isLocked;
		bool _isDeployed;
		int face;
		
		TetrisPlayField * playField;
		sf::Vector2f positionOffset;
		
		sf::Vector2i moveCount;
		sf::Vector2i kickPos;
		int blockCount;		
};	

#endif