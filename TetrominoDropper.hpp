#ifndef TETROMINODROPPER_HPP
#define TETROMINODROPPER_HPP

#include "IUpdatableObject.hpp"
#include "TetrisPlayField.hpp"
#include "Tetromino.hpp"


class TetrominoDropper : public esc::IUpdatableObject
{
	public:
		
		TetrominoDropper();
		virtual ~TetrominoDropper();

		void setTetromino(Tetromino * t);
		virtual void update(float);

		void softDrop(bool = true);
		void hardDrop(bool = true);

		void setDropInterval(float);
		float getDropInterval() const;

		void setLockInterval(float);
		float getLockInterval() const;

	private:
		
		float dropInterval;
		float lockTime;
		float lockElapsed;
		float dropElapsed;

		Tetromino * host;
		TetrisPlayField * playField;
};

#endif