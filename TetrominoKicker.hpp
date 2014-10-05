#ifndef TETROMINOKICKER_HPP
#define TETROMINOKICKER_HPP

class Tetromino;
class TetrisPlayField;
class RotationSystem;

class TetrominoKicker 
{
	public:
		
		void setTetromino(Tetromino *);
		bool checkKick(int rd);
		void kickTetromino(int rd);

	private:
		
		TetrisPlayField * playField;
		RotationSystem * rotationSystem;
		Tetromino * tetromino;	
		
		sf::Vector2i kickMove;		
};

#endif