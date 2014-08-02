#ifndef TETRISPLAYFIELD_HPP
#define TETRISPLAYFIELD_HPP

#include<vector>
using std::vector;

#include<queue>
using std::queue;

#include<string>
using std::string;

#include<map>
using std::pair;
using std::make_pair;

#include<SFML/Graphics.hpp>

#include "Object.hpp"

class TetrisPlayField
{
	typedef vector<vector<bool>> BooleanGrid;
	typedef vector<vector<Tetromino::ObjectPtr>> ;

	public:
		
		TetrisPlayField(sf::Vector2f = sf::Vector2f(), float offset = 16.0f);
		virtual ~TetrisPlayField();

		void setActive(const sf::Vector2i &, bool);
		void setActive(int, int, bool);
		bool isActive (const sf::Vector2i &) const;
		bool isActive (const sf::Vector2f &);
		bool isActive (int , int) const;
		bool isWithinBounds(const sf::Vector2f &);
		bool isWithinBounds(const sf::Vector2i &);

		int getScore();
		bool verifyLine(int);

		void setFieldSize(const sf::Vector2f &);
		const sf::Vector2f & getFieldSize() const;

		void setGridOffset(float);
		float getGridOffset();

		void setPosition(const sf::Vector2f &);
		const sf::Vector2f & getPosition() const;

		void drawGrid(sf::RenderWindow *, bool = true);
		
		// to be deleted
		void showBooleanGrid();
		sf::Vector2i convertToGridPosition(const sf::Vector2f &);
	
	private:

		BooleanGrid booleanGrid;
		sf::Vector2f fieldSize;

		vector<sf::RectangleShape> horizontalGrid;
		vector<sf::RectangleShape> verticalGrid;

		sf::Vector2f position;
		float offset;
};

#endif