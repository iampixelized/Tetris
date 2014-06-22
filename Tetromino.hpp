// ??SRS System is used for rotation...

#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include<vector>
using std::vector;

#include "TetrisPlayField.hpp"
#include "Piece.hpp"

/*
	//NOTE: To be continued(...)
	//	- Consider Bottom Wall Kick! Especially for I-Tetromino...
	//	- Work on the internal representation of the grid
	//	- Figure out how a piece can be remove from the playfield.
	//  - Figure out how the grid can shift downwards(updated) after line out
	//  - 
*/

// Create a specific Tetromino Manager for this class.

// In our definition and policies: A Tetromino is composed
// of Pieces, which are the blocks that resembles each type
// of tetrominos(S,Z,J,L,I,O,T). 

// Tetromino is just a container of objects

class Tetromino
{
	typedef unique_ptr<Piece> PiecePtr;
	typedef vector<PiecePtr> BlockPalette;

	enum BlockRotate{ UP, DOWN, LEFT, RIGHT };
	enum RotateTo{ _0, _90, _180, _270 };

	public:

		enum TetrominoType{ S = 1, Z, J, L, I, O, T };
		enum BlockColor{ Cyan, Yellow, Purple, Green, Red, Blue, Orange };
		
		Tetromino(TetrominoType ttype, BlockColor bc, TetrisPlayField & tpf, esc::AssetManager & am);
		virtual ~Tetromino();

		void rotateLeft();
		void rotateRight();

		void update(float);
		void draw(sf::RenderWindow *);

		void hardDrop();
		void softDrop();
		bool isDropped() const;

		void moveRight();
		void moveLeft();

		TetrominoType getType() const;
		static Tetromino * createTetromino(TetrominoType, BlockColor, TetrisPlayField &, esc::AssetManager &);

		void showObjectIDs() const;
		void showObjectPositions() const;

		TetrisPlayField * getPlayField() const;
		void removeBlock(int);
		int getID() const;

		Piece * getPiece(int);

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

		float dropInterval;
		bool _isDropped;
		int face;
		
		BlockConfigurations blockConfigurations;

		TetrisPlayField * playField;

		sf::Vector2f positionOffset;
		sf::Vector2f sizeOffset;
		
		int hWidthOffset;
		int vWidthOffset;
		int moveCount;
		int dropCount;

		bool isLateral;
};	

#endif