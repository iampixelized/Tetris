#ifndef ILAYER_HPP
#define ILAYER_HPP

#include<SFML/Graphics.hpp>

namespace esc
{
	class ILayer
	{
	public:

		virtual void refreshLayer(float, sf::RenderWindow * , bool = true) = 0;
	};
}
#endif