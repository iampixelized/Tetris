#include<iostream>
using std::cout;
using std::endl;

#include "Object.hpp"

namespace esc
{
	int Object::id_generator = 0;

	Object::Object(const string &oname, const sf::Vector2f &pos, AssetManager &am)
		: 
		objectName(oname), 
		position(pos), 
		assetManager(&am),
		perceivedLayer(nullptr)
	{
		id = id_generator++;
		changeObject(oname);
	}

	Object::~Object()
	{

	}

	void Object::update(float e)
	{
		//
	}

	void Object::draw(sf::RenderWindow*window)
	{
		window->draw(sprite);
	}

	void Object::moveTo(const sf::Vector2f &pos)
	{
		sprite.move(pos);
		position = sprite.getPosition();
	}

	void Object::setPosition(const sf::Vector2f & pos)
	{
		position = pos;
		sprite.setPosition(pos);
	}

	const sf::Vector2f & Object::getPosition() const
	{
		return position;
	}

	const string & Object::getObjectName() const
	{
		return objectName;
	}

	void Object::enable(bool b)
	{
		enabled = b;
	}

	bool Object::isEnabled() const
	{
		return enabled;
	}

	void Object::perceiveLayer(ILayer & layer)
	{
		perceivedLayer = &layer;
	}

	ILayer * Object::getPerceivedLayer() const
	{
		return perceivedLayer;
	}

	bool Object::changeObject(const string & oname)
	{
		IAsset * tmpHndlr = assetManager->getAsset("Textures");

		if (tmpHndlr != nullptr)
		{
			textureHandler = dynamic_cast<Asset<sf::Texture>*>(tmpHndlr);
			
			if (textureHandler->isResource(oname))
			{
				texture = *textureHandler->getResource(oname);
				sprite.setTexture(texture);
				sprite.setPosition(position);
				return true;
			}
		}

		return false;
	}

	int Object::getObjectID() const
	{
		return id;
	}
}