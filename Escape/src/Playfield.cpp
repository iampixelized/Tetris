#include<iostream>
using std::cout;
using std::endl;

#include "Playfield.hpp"

namespace esc
{
	PlayField::PlayField(const sf::Vector2f &sz)
		: fieldSize(sz)
	{

	}

	PlayField::~PlayField()
	{

	}

	void PlayField::setActive(const sf::Vector2f &pos, bool active)
	{
		if (!(pos.x < 0 && pos.x >= fieldSize.x) ||
			!(pos.y < 0 && pos.y >= fieldSize.y))
			return;

		playField[pos.y][pos.x] = active;
	}

	bool PlayField::isActive(const sf::Vector2f&pos) const
	{
		if ((pos.x < 0 && pos.x >= fieldSize.x) ||
			(pos.y < 0 && pos.y >= fieldSize.y))
			return playField[pos.y][pos.x];

		return false;
	}

	bool PlayField::isActive(float x, float y) const
	{
		if (!isActive(sf::Vector2f(x,y)))
			return true;
			
		return false;
	}
}