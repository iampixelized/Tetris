#ifndef BLOCK_HPP
#define BLOCK_HPP

#include<SFML/Graphics.hpp>

#include "AssetManager.hpp"
#include "Object.hpp"
#include "TetrisPlayField.hpp"

class Block : public esc::Object
{
	public:

		Block(const string &, const sf::Vector2f &pos, TetrisPlayField &, esc::AssetManager & , int);
		virtual ~Block();

		virtual void update(float);
		virtual void draw(sf::RenderWindow *);
		sf::Vector2i getGridPosition();

		void markCleared();
		virtual bool isGarbageCollectible();
		int getID() const;

	protected:
		
		Block() : blockID(-1){};

	private:
		
		bool _isCleared;
		int blockID;
		int fieldLevel;
		TetrisPlayField * playField;
};

#endif