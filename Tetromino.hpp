// ??SRS System is used for rotation...

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
#include "Object.hpp"

/*
	//NOTE: To be continued(...)
	//	- Consider Bottom Wall Kick! Especially for I-Tetromino...
	//	- Work on the internal representation of the grid
	//	- Figure out how a piece can be remove from the playfield.
	//  - Figure out how the grid can shift downwards(updated) after line out
	//  - Integrate Piece class to Tetromino, then remove and delete Piece from project.
*/

// Create a specific Tetromino Manager for this class.

// In our definition and policies: A Tetromino is composed
// of Pieces, which are the blocks that resembles each type
// of tetrominos(S,Z,J,L,I,O,T). 

// Tetromino is just a container of objects

class Tetromino
{
	typedef unique_ptr<esc::Object> ObjectPtr;
	typedef map<int, ObjectPtr> BlockPalette;

	enum BlockRotate{ UP, DOWN, LEFT, RIGHT };
	enum RotateTo{ _0, _90, _180, _270 };

	public:

		enum TetrominoType{ S = 1, Z, J, L, I, O, T };
		enum BlockColor{ Cyan, Yellow, Purple, Green, Red, Blue, Orange };
		
		Tetromino(TetrominoType ttype, BlockColor bc, TetrisPlayField & tpf, esc::AssetManager & am);
		virtual ~Tetromino();

		void rotateLeft();
		void rotateRight();
		void setRotation(int);
		int getRotation() const;
		void setGridPosition(const sf::Vector2i &);

		void update(float);
		void draw(sf::RenderWindow *);

		void hardDrop();
		void softDrop();
		bool isDropped() const;

		void moveRight();
		void moveLeft();

		TetrominoType getType() const;
		static Tetromino * createTetromino(TetrominoType, BlockColor, TetrisPlayField &, esc::AssetManager &);

		TetrisPlayField * getPlayField() const;
		void removeBlock(int);
		int getID() const;
		esc::Object * getPiece(int);

		static void setDropInterval(float);
		static float getDropInterval();

	protected:

		Tetromino(){};
		void updatePieces(const vector<sf::Vector2f> &);

	private:

		static int id_generator;
		int id;

		int getRightMostBounds();
		int getLeftMostBounds();

		void leftWallKick();
		void rightWallKick();
		void deploy();
		void rotationCheck();

		struct BlockConfigurations
		{
			vector<sf::Vector2f> _0Config;
			vector<sf::Vector2f> _90Config;
			vector<sf::Vector2f> _180Config;
			vector<sf::Vector2f> _270Config;
		};

		float blockSize;
		int blockRotationCount;

		TetrominoType type;
		BlockColor color;
		RotateTo currentDirection;
		vector<sf::Vector2f> blockPositions;
		BlockPalette palette;

		float dropElapsed;
		static float dropInterval;
		bool _isDropped;
		int face;
		int previousFace;
		
		BlockConfigurations blockConfigurations;

		TetrisPlayField * playField;

		sf::Vector2f positionOffset;
		sf::Vector2f sizeOffset;
		
		int hWidthOffset;
		int vWidthOffset;
		int moveCount;
		int previousMoveCount;
		int moveOffset;
		int dropCount;

		bool isLateral;
};	

#endif