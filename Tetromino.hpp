#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <memory>
using std::unique_ptr;

#include "TetrisPlayField.hpp"
#include "Block.hpp"
#include "ObjectLayer.hpp"
#include "TetrominoType.hpp"
#include "RotationSystem.hpp"

class Mechanics;

class Tetromino
{
	public:

		typedef unique_ptr<RotationSystem> RPtr;
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
		static Tetromino * createTetromino(TetrominoType, BlockColor, RPtr, esc::AssetManager &);

		void update(float);
		void draw(sf::RenderWindow *);

		TetrisPlayField * getPlayField() const;
		int getID() const;
		Block * getBlock(int);

		bool checkRotation(int);
		bool checkMovement(int);
		bool checkPosition(const sf::Vector2i &);
		size_t getBlockCount() const;

		void setMimic(Tetromino * mimic);
		Tetromino * getMimic() const;
		bool isGarbageCollectible();

	protected:

		Tetromino
		(
			  TetrominoType
			, BlockColor
			, RPtr
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
		RPtr rotationSystem;
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