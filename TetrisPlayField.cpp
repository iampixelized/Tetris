#include<iostream>
using std::cout;
using std::endl;

#include<algorithm>
using std::all_of;

#include "TetrisPlayField.hpp"

TetrisPlayField::TetrisPlayField(const sf::Vector2f &size, sf::Vector2f pos, float o)
	: fieldSize(size), position(pos), offset(o)
{

	// for drafting only
	for (size_t i = 0; i <= size.y; ++i)
	{
		sf::RectangleShape hline;
		hline.setSize(sf::Vector2f(size.x * offset, 1.0f));
		hline.setPosition(sf::Vector2f(pos.y, i * offset));
		hline.setFillColor(sf::Color::Blue);
		horizontalGrid.push_back(hline);
	}

	for (size_t i = 0; i <= size.x; ++i)
	{
		sf::RectangleShape vline;
		vline.setSize(sf::Vector2f(1.0f, size.y * offset));
		vline.setPosition(sf::Vector2f(i * offset, pos.x));
		vline.setFillColor(sf::Color::Blue);
		verticalGrid.push_back(vline);
	}
	//

	cout << "Playfield size : " << size.x << " x " << size.y << endl;
	cout << "Playfield pos  : " << pos.x << " x " << pos.y << endl;
}

TetrisPlayField::~TetrisPlayField()
{

}

int TetrisPlayField::getScore()
{
	int score = 0;
	int scoreLevel = 0;

	for (size_t y = 0; y < playField.size(); ++y)
	{
		if (all_of(playField[y].begin(), playField[y].end(),
			[](bool b){return b; }))
		{
			scoreLevel++;
			score += 100;
		}
	}

	if (scoreLevel >= 4)
		return 1000;
	else
		return score;
}

void TetrisPlayField::setFieldSize(const sf::Vector2f &fs)
{
	fieldSize = fs;
}

const sf::Vector2f & TetrisPlayField::getFieldSize() const
{
	return fieldSize;
}

void TetrisPlayField::setGridOffset(float o)
{
	offset = (o < 6) ? o : 6;

	for (size_t i = 0; i <= fieldSize.x; ++i)
	{
		verticalGrid[i].setSize(sf::Vector2f(1.0f, fieldSize.y * offset));
		verticalGrid[i].setPosition(sf::Vector2f(i * offset, position.x));
	}

	for (size_t i = 0; i <= fieldSize.y; ++i)
	{
		horizontalGrid[i].setSize(sf::Vector2f(fieldSize.x * offset, 1.0f));
		horizontalGrid[i].setPosition(sf::Vector2f(position.y, i * offset));
	}
}

float TetrisPlayField::getGridOffset()
{
	return offset;
}

void TetrisPlayField::setActive(const sf::Vector2f &pos, bool active)
{
	if (!(pos.x < 0 && pos.x >= fieldSize.x) ||
		!(pos.y < 0 && pos.y >= fieldSize.y))
		return;

	playField[pos.y][pos.x] = active;
}

void TetrisPlayField::setActive(float x, float y, bool active)
{
	setActive(sf::Vector2f(x, y), active);
}

bool TetrisPlayField::isActive(const sf::Vector2f &pos) const
{
	if (!(pos.x < 0 && pos.x >= fieldSize.x) ||
		!(pos.y < 0 && pos.y >= fieldSize.y))
		return playField[pos.y][pos.x];

	return false;
}

bool TetrisPlayField::isActive(float x, float y) const
{
	return isActive(sf::Vector2f(x, y));
}


void TetrisPlayField::setPosition(const sf::Vector2f &pos)
{
	position = pos;

	for (size_t i = 0; i <= fieldSize.x; ++i)
		verticalGrid[i].setPosition(sf::Vector2f((i * offset) + position.x, position.y));

	for (size_t i = 0; i <= fieldSize.y; ++i)
		horizontalGrid[i].setPosition(sf::Vector2f(position.x, (i * offset) + position.y));
}

const sf::Vector2f & TetrisPlayField::getPosition() const
{
	return position;
}

void TetrisPlayField::drawGrid(sf::RenderWindow * window, bool show)
{
	if (!show) return;

	for (size_t x = 0; x <= fieldSize.x; ++x)
		window->draw(verticalGrid[x]);

	for (size_t y = 0; y <= fieldSize.y; ++y)
		window->draw(horizontalGrid[y]);
}
