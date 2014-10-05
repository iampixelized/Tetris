#ifndef IDRAWABLEOBJECT_HPP
#define IDRAWABLEOBJECT_HPP

#include <SFML/Graphics.hpp>

namespace esc
{
	class IDrawableObject 
	{
		public: virtual void draw(sf::RenderWindow*) = 0;
	};
}
#endif