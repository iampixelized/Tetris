#include<iostream>
using std::cout;
using std::endl;

#include<algorithm>
using std::all_of;
using std::count;

#include "TetrisPlayField.hpp"

TetrisPlayField::TetrisPlayField(sf::Vector2f pos, float o)
	:
	fieldSize(sf::Vector2f(10,20)),
	position(pos),
	offset(o)
{

	for (size_t i = 0; i <= fieldSize.y; ++i)
	{
		sf::RectangleShape hline;
		hline.setSize(sf::Vector2f(fieldSize.x * offset, 1.0f));
		hline.setPosition(sf::Vector2f(pos.y, i * offset));
		hline.setFillColor(sf::Color::Blue);
		horizontalGrid.push_back(hline);
	}

	for (size_t i = 0; i <= fieldSize.x; ++i)
	{
		sf::RectangleShape vline;
		vline.setSize(sf::Vector2f(1.0f, fieldSize.y * offset));
		vline.setPosition(sf::Vector2f(i * offset, pos.x));
		vline.setFillColor(sf::Color::Blue);
		verticalGrid.push_back(vline);
	}

	for (size_t y = 0; y < fieldSize.y; ++y)
	{
		booleanGrid.push_back(vector<bool>());
		for (size_t i = 0; i < fieldSize.x; ++i)
			booleanGrid[y].push_back(false);
	}
}

TetrisPlayField::~TetrisPlayField()
{

}

void TetrisPlayField::setActive(const sf::Vector2i &pos, bool active)
{
	if ((pos.x >= 0 && pos.x < fieldSize.x) &&
		(pos.y >= 0 && pos.y < fieldSize.y))
		booleanGrid[pos.y][pos.x] = active;

	return;
}

void TetrisPlayField::setActive(int x, int y, bool active)
{
	setActive(sf::Vector2i(x, y), active);
}

bool TetrisPlayField::isActive(const sf::Vector2i &pos) const
{
	if ((pos.x >= 0 && pos.x < fieldSize.x) &&
		(pos.y >= 0 && pos.y < fieldSize.y))
		return booleanGrid[pos.y][pos.x];

	return true;
}

bool TetrisPlayField::isActive(const sf::Vector2f &pos)
{
	sf::Vector2i gridpos = convertToGridPosition(pos);
	return isActive(gridpos);
}

bool TetrisPlayField::isActive(int x, int y) const
{
	return isActive(sf::Vector2i(x, y));
}

bool TetrisPlayField::isWithinBounds(const sf::Vector2i & pos)
{
	if ((pos.x >= 0 && pos.x < fieldSize.x) &&
		(pos.y >= 0 && pos.y < fieldSize.y))
		return true;

	return false;
}

bool TetrisPlayField::isWithinBounds(const sf::Vector2f &pos)
{
	sf::Vector2i gridpos = convertToGridPosition(pos);
	return isWithinBounds(gridpos);
}

int TetrisPlayField::getMaxBounds(int direction , int level)
{
	if (level >= 0 && level < booleanGrid.size())
	{
		if (direction <= 0)
			for (size_t i = 4; i >= booleanGrid.size(); --i)
				if(booleanGrid[level][i])
					return i+1;

		else if (direction > 0)
			for (size_t i = 5; i < booleanGrid.size(); ++i)
				if (booleanGrid[level][i])
					return i;
	}

	return 0;
}

int TetrisPlayField::getScore()
{
	int score = 0;
	int scoreLevel = 0;

	for (size_t y = 0; y < booleanGrid.size(); ++y)
	{
		if (all_of(booleanGrid[y].begin(), booleanGrid[y].end(),
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

// to be deleted
void TetrisPlayField::showBooleanGrid()
{
	for (size_t y = 0; y < booleanGrid.size(); ++y)
	{
		for (size_t i = 0; i < booleanGrid[y].size(); ++i)
		{
			if (booleanGrid[y][i])
				cout << "X";
			else
				cout << ".";
		}

		cout << endl;
	}
}

sf::Vector2i TetrisPlayField::convertToGridPosition(const sf::Vector2f & pixelpos)
{
	sf::Vector2i gpos = sf::Vector2i(pixelpos - position);
	gpos.x /= offset;
	gpos.y /= offset;

	return gpos;
}