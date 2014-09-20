#include<iostream>
using std::cout;
using std::endl;

#include "Block.hpp"

Block::Block(const string &pname, const sf::Vector2f &pos, TetrisPlayField & tpf, esc::AssetManager &am, int id)
	: 
	  esc::Object(pname, pos, am)
	, blockID(id)
	, _isCleared(false)
	, playField(&tpf)
{

}

Block::~Block()
{

}

void Block::update(float e)
{
	if (_isCleared) return;

	// animation sequence goes here...
	// Use SFML THOR for animation

}

void Block::draw(sf::RenderWindow *window)
{
	if (_isCleared || getGridPosition().y < 2)
		return;

	esc::Object::draw(window);
}

sf::Vector2i Block::getGridPosition()
{
	float offset = playField->getGridOffset();
	sf::Vector2f position = esc::Object::getPosition();
	
	sf::Vector2i gridpos;
	gridpos.x = static_cast<int>( (position.x - playField->getPosition().x) / offset);
	gridpos.y = static_cast<int>( (position.y - playField->getPosition().y) / offset);

	return gridpos;
}

void Block::markCleared()
{
	_isCleared = true;
}

bool Block::isGarbageCollectible()
{
	return false;
}

int Block::getID() const
{
	return blockID;
}