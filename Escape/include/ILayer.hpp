#ifndef ILAYER_HPP
#define ILAYER_HPP

#include<SFML/Graphics.hpp>

namespace esc
{
	class ILayer
	{
	public:
		
		ILayer();
		virtual ~ILayer();

		void setParentLayer(ILayer &);
		void setChildLayer(ILayer &);

		virtual void refreshLayer(float , sf::RenderWindow * , bool = false) = 0;

		ILayer * getParentLayer() const;
		ILayer * getChildLayer() const;

	private:

		ILayer * parent;
		ILayer * child;
	
	};

	inline ILayer::ILayer() : parent(nullptr), child(nullptr){}
	inline ILayer::~ILayer(){}

	inline void ILayer::setParentLayer(ILayer &l){parent = &l;}
	inline void ILayer::setChildLayer(ILayer &l){ child = &l; }

	inline ILayer * ILayer::getParentLayer() const{return parent;}
	inline ILayer * ILayer::getChildLayer() const{return child;}
}

#endif