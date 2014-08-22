#include<iostream>
using std::cout;
using std::endl;

#include<algorithm>
using std::all_of;
using std::count;
using std::find;
using std::min_element;

#include "TetrisPlayField.hpp"
#include "Tetromino.hpp"
#include "Block.hpp"

TetrisPlayField::TetrisPlayField(sf::Vector2f pos, float o)
	:
	  fieldSize(sf::Vector2i(10, 20))
	, blockGrid(fieldSize.y, vector<Block*>(static_cast<int>(fieldSize.x), nullptr))
	, position(pos)
	, offset(o)
	, peakLevels(20, 20)
{

	for (int i = 0; i <= fieldSize.y; ++i)
	{
		sf::RectangleShape hline;
		hline.setSize(sf::Vector2f(fieldSize.x * offset, 1.0f));
		hline.setPosition(sf::Vector2f(pos.y, i * offset));
		hline.setFillColor(sf::Color::Blue);
		horizontalGrid.push_back(hline);
	}

	for (int i = 0; i <= fieldSize.x; ++i)
	{
		sf::RectangleShape vline;
		vline.setSize(sf::Vector2f(1.0f, fieldSize.y * offset));
		vline.setPosition(sf::Vector2f(i * offset, pos.x));
		vline.setFillColor(sf::Color::Blue);
		verticalGrid.push_back(vline);
	}

	cout << "TPF size : " << peakLevels.size() << endl;
}

TetrisPlayField::~TetrisPlayField()
{

}

bool TetrisPlayField::isActive(const sf::Vector2i &pos) const
{
	if ((pos.x >= 0 && pos.x < fieldSize.x) &&
		(pos.y >= 0 && pos.y < fieldSize.y))
		return (blockGrid[pos.y][pos.x] != nullptr)? true : false;

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

const sf::Vector2i & TetrisPlayField::getFieldSize() const
{
	return fieldSize;
}

void TetrisPlayField::setGridOffset(float o)
{
	offset = (o < 6) ? o : 6;

	for (int i = 0; i <= fieldSize.x; ++i)
	{
		verticalGrid[i].setSize(sf::Vector2f(1.0f, fieldSize.y * offset));
		verticalGrid[i].setPosition(sf::Vector2f(i * offset, position.x));
	}

	for (int i = 0; i <= fieldSize.y; ++i)
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

	for (int i = 0; i <= fieldSize.x; ++i)
		verticalGrid[i].setPosition(sf::Vector2f((i * offset) + position.x, position.y));

	for (int i = 0; i <= fieldSize.y; ++i)
		horizontalGrid[i].setPosition(sf::Vector2f(position.x, (i * offset) + position.y));
}

const sf::Vector2f & TetrisPlayField::getPosition() const
{
	return position;
}

void TetrisPlayField::drawGrid(sf::RenderWindow * window, bool show)
{
	if (!show) return;

	for (int x = 0; x <= fieldSize.x; ++x)
		window->draw(verticalGrid[x]);

	for (int y = 0; y <= fieldSize.y; ++y)
		window->draw(horizontalGrid[y]);
}

void TetrisPlayField::showBooleanGrid()
{
	for (size_t y = 0; y < blockGrid.size(); ++y)
	{
		for (size_t i = 0; i < blockGrid[y].size(); ++i)
		{
			if (blockGrid[y][i]) cout << "X";
			else cout << ".";
		}

		cout << endl;
	}
}

sf::Vector2i TetrisPlayField::convertToGridPosition(const sf::Vector2f & pixelpos)
{
	sf::Vector2i gpos = sf::Vector2i(pixelpos - position);
	gpos.x = static_cast<int>(gpos.x / offset);
	gpos.y = static_cast<int>(gpos.y / offset);

	return gpos;
}

int TetrisPlayField::getPeakLevel() const
{
	return *min_element(peakLevels.begin(), peakLevels.end());
}

int TetrisPlayField::getPeakLevelOnRow(int row)
{
	if (row >= 19 || row <= 0)
		return peakLevels[row];

	return -1;
}

void TetrisPlayField::shiftClearedRows()
{
	for (int row : clearedRows)
	{
		for (int i = 0; i < fieldSize.x; ++i)
		{
			blockGrid[row][i]->markCleared();
		}

		for (int y = row; y >= getPeakLevel(); --y)
		{
			if ((y - 1) >= 0) 
			{
				for (int i = 0; i < fieldSize.x; ++i)
				{
					if (blockGrid[y - 1][i] != nullptr)
						blockGrid[y - 1][i]->moveTo(sf::Vector2f(0,offset));
				}
			}
		}
	}

	resetRows();
	//showBooleanGrid();
}

void TetrisPlayField::registerBlocks(Tetromino * t)
{
	cout << "Peak level is : " << getPeakLevel() << endl;

	for (int i = 0; i < t->getBlockCount(); ++i)
	{
		if (Block * block = t->getBlock(i))
		{
			sf::Vector2i gpos = block->getGridPosition();
			blockGrid[gpos.y][gpos.x] = block;
			peakLevels[gpos.x] = (gpos.y < peakLevels[gpos.x]) ? gpos.y : peakLevels[gpos.x];
		}
	}

	//showBooleanGrid();
	searchClearedRows();
}

void TetrisPlayField::resetRows()
{
	for (int i : clearedRows) removeRow(i);
	clearedRows.clear();
}

int TetrisPlayField::getClearedRowsSize() const
{
	return clearedRows.size();
}

void TetrisPlayField::searchClearedRows()
{
	for (int y = 0; y < fieldSize.y; ++y)
	{
		if (all_of(blockGrid[y].begin(), blockGrid[y].end(),
			[](Block * b){return (b != nullptr) ? true : false; }))
		{
			clearedRows.push_back(y);
		}
	}

	std::sort(clearedRows.begin(), clearedRows.end(), [](int a, int b){ return a < b;});
}

void TetrisPlayField::removeRow(int row)
{
	auto iter = blockGrid.begin() + row;

	if (iter == blockGrid.end())
		return;
	
	blockGrid.erase(iter);
	blockGrid.insert(blockGrid.begin(), vector<Block*>(10, nullptr));
}