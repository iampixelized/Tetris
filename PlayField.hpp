#ifndef PLAYFIELD_HPP
#define PLAYFIELD_HPP

#include<vector>
using std::vector;

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace esc
{
	class PlayField
	{

	typedef vector<vector<bool>> BooleanGrid;

	public:

		explicit PlayField(const sf::Vector2f &);
		virtual ~PlayField();

		void setActive(const sf::Vector2f&, bool);
		bool isActive(const sf::Vector2f &) const;
		bool isActive(float, float) const;

	protected:

		BooleanGrid playField;

	private:

		sf::Vector2f fieldSize;

	};
}

#endif