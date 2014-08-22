#ifndef GHOST_HPP
#define GHOST_HPP

#include<memory>
using std::unique_ptr;

#include<SFML/Graphics.hpp>

#include "AssetManager.hpp"

class TetrisPlayField;
class Tetromino;
struct Mechanics;

class Ghost 
{
	public:

		Ghost(TetrisPlayField & , Mechanics & , esc::AssetManager &);
		virtual ~Ghost();

		void setTetromino(Tetromino &);
		void calculate();
		void showGhostTetromino(sf::RenderWindow * , bool = true );

	private:
		
		Tetromino * tetromino;
		unique_ptr<Tetromino> mimic;
		TetrisPlayField * playField;
		Mechanics * mechanics;	
		esc::AssetManager * assetManager;	
};

#endif