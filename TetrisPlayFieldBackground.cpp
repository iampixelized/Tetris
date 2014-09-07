#include "TetrisPlayField.hpp"


#include "TetrisPlayFieldBackground.hpp"

TetrisPlayFieldBackground::TetrisPlayFieldBackground(TetrisPlayField & tpf)
	: playField(&tpf) , _isBackGroundLoaded(false)
{

}

TetrisPlayFieldBackground::~TetrisPlayFieldBackground()
{

}

void TetrisPlayFieldBackground::loadPlayFieldBackground(const string &bgName, esc::AssetManager &am)
{
	
}

void TetrisPlayFieldBackground::draw(sf::RenderWindow * window)
{

}


