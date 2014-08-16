#ifndef GHOST_HPP
#define GHOST_HPP

#include<SFML/Graphics.hpp>

class Tetromino;

class Ghost 
{
	public:
	
		Ghost();
		virtual ~Ghost();

		void setTetromino(Tetromino &);
		void update(float);
		void draw(sf::RenderWindow *);

	private:
		
		Tetromino * tetromino;
};

#endif