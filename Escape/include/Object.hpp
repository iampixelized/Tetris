#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<string>
using std::string;

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include "Asset.hpp"
#include "AssetManager.hpp"
#include "ObjectLayer.hpp"

namespace esc
{
	class Object
	{

	public:

		Object(const string &, const sf::Vector2f &, AssetManager &);
		virtual ~Object();

		virtual void update(float);
		virtual void draw(sf::RenderWindow*);

		void moveTo(const sf::Vector2f &);
		void setPosition(const sf::Vector2f &);
		const sf::Vector2f & getPosition() const;
		const string & getObjectName() const;

		void enable(bool);
		bool isEnabled() const;

		virtual void onDeath(){};  // no implementation yet
		virtual void onCreate(){}; // no implementation yet

		virtual void perceiveLayer(ILayer &);
		ILayer * getPerceivedLayer() const;
		bool changeObject(const string &);

		int getObjectID() const;
		virtual bool isGarbageCollectible();

	protected:
		
		Object(){}
		Asset<sf::Texture> * textureHandler;
		Asset<sf::SoundBuffer> * soundBufferHandler;
		AssetManager * assetManager;

	private:

		static int id_generator;
		int id;

		string objectName;
		sf::Vector2f position;

		sf::Sprite sprite;
		sf::Texture texture;

		ILayer *perceivedLayer;
		bool enabled;
	};
}

#endif