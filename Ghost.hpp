#ifndef GHOST_HPP
#define GHOST_HPP

#include<SFML/Graphics.hpp>

#include "Object.hpp"
#include "TetrisPlayField.hpp"
#include "AssetManager.hpp"

class Tetromino;

class Ghost : public esc::Object
{
	public:
		
		Ghost(TetrisPlayField &, esc::AssetManager &);
		virtual ~Ghost();

		void setTetromino(Tetromino &);

	private:
		
		void computeLocation();

		Tetromino * tetromino;
};

#endif