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

class Tetromino;
class Block;

class TetrisPlayField
{
	typedef vector<vector<Block*>> BlockGrid;

	public:
		
		TetrisPlayField(sf::Vector2f = sf::Vector2f(), float offset = 16.0f);
		virtual ~TetrisPlayField();

		bool isActive (const sf::Vector2i &) const;
		bool isActive (const sf::Vector2f &);
		bool isActive (int , int) const;

		bool isWithinBounds(const sf::Vector2f &);
		bool isWithinBounds(const sf::Vector2i &);
		
		void setFieldSize(const sf::Vector2f &);
		const sf::Vector2f & getFieldSize() const;

		void setGridOffset(float);
		float getGridOffset();

		void setPosition(const sf::Vector2f &);
		const sf::Vector2f & getPosition() const;

		void drawGrid(sf::RenderWindow *, bool = true);
		
		// to be deleted
		void showGridLines();
		sf::Vector2i convertToGridPosition(const sf::Vector2f &);
		int getPeak() const;

		void shiftClearedRows();
		void registerBlocks(Tetromino *);
		void resetRows();
		int getClearedRowsSize() const;

	private:

		void searchClearedRows();
		void removeRow(int);

		sf::Vector2f fieldSize;
		BlockGrid blockGrid;

		vector<sf::RectangleShape> horizontalGrid;
		vector<sf::RectangleShape> verticalGrid;

		sf::Vector2f position;
		float offset;
		int peakLevel;

		vector<int> clearedRows;
};

#endif