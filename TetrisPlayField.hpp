#ifndef TETRISPLAYFIELD_HPP
#define TETRISPLAYFIELD_HPP

#include<vector>
using std::vector;

#include<string>
using std::string;

#include<SFML/Graphics.hpp>

#include "PlayField.hpp"

class TetrisPlayField
{

	typedef vector<vector<bool>> BooleanGrid;

	public:

		TetrisPlayField(const sf::Vector2f &, sf::Vector2f = sf::Vector2f(), float offset = 16.0f);
		virtual ~TetrisPlayField();

		void setGridOffset(const sf::Vector2f &);
		float getGridOffset() const;

		void setActive(const sf::Vector2f &, bool);
		void setActive(float, float, bool);
		bool isActive(const sf::Vector2f &) const;
		bool isActive(float , float) const;

		int getScore();

		void setFieldSize(const sf::Vector2f &);
		const sf::Vector2f & getFieldSize() const;

		void setGridOffset(float);
		float getGridOffset();

		void setPosition(const sf::Vector2f &);
		const sf::Vector2f & getPosition() const;

		void drawGrid(sf::RenderWindow *, bool = true);

	private:

		BooleanGrid playField;
		sf::Vector2f fieldSize;
		vector<int> immediateHeight;

		vector<sf::RectangleShape> horizontalGrid;
		vector<sf::RectangleShape> verticalGrid;

		sf::Vector2f position;
		float offset;
};

#endif