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
#include "RotationSystem.hpp"

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
	typedef unique_ptr<esc::Object> ObjectPtr;
	typedef map<int, ObjectPtr> BlockPalette;

	public:

		struct BlockConfigurations
		{
			vector<sf::Vector2i> _0Config;
			vector<sf::Vector2i> _90Config;
			vector<sf::Vector2i> _180Config;
			vector<sf::Vector2i> _270Config;
		};

		enum TetrominoType{ S = 1, Z, J, L, I, O, T, DOT };
		enum BlockColor{ Cyan, Yellow, Purple, Green, Red, Blue, Orange };
		
		Tetromino
		(
			TetrominoType 		 , 
			BlockColor 			 , 
			TetrisPlayField    & ,
			Mechanics		   & ,
			esc::AssetManager  & 
		);
		
		virtual ~Tetromino();

		RotationSystem * getRotationSystem();

		void rotateLeft();
		void rotateRight();
		void setRotation(int);
		int getRotation() const;
		void setGridPosition(const sf::Vector2i &);

		void hardDrop();
		void softDrop();
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
		void removeBlock(int);
		int getID() const;
		esc::Object * getPiece(int);

		bool checkRotation(int);
		bool checkMovement(int);

	protected:

		Tetromino(){};
		void updatePalette(const vector<sf::Vector2i> &);

	private:

		void deploy();

		static int id_generator;
		int id;

		float blockSize;
		int blockRotationCount;

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
};	

#endif