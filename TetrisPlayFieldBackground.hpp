#ifndef TETRISPLAYFIELDBACKGROUND_HPP
#define TETRISPLAYFIELDBACKGROUND_HPP

#include<string>
using std::string;

#include "AssetManager.hpp"

class TetrisPlayField;

class TetrisPlayFieldBackground 
{
	public:
		
		explicit TetrisPlayFieldBackground(TetrisPlayField &);
		virtual ~TetrisPlayFieldBackground();

		void loadPlayFieldBackground(const string &, esc::AssetManager &);
		void draw(sf::RenderWindow*);

	private:
				
		bool _isBackGroundLoaded;
		TetrisPlayField * playField;
};

#endif