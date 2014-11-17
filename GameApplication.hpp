#ifndef GAMEAPPLICATION_HPP
#define GAMEAPPLICATION_HPP

#include<string>
using std::string;

#include<memory>
using std::unique_ptr;

#include<SFML/Graphics.hpp>
#include<SFML/Audio/SoundBuffer.hpp>
#include<SFML/Audio/Music.hpp>
#include<SFML/System/Clock.hpp>

#include "AssetManager.hpp"
#include "TetrisPlayField.hpp"
#include "SoundDirector.hpp"

class GameApplication
{
	typedef esc::Asset<sf::Texture> TextureAsset;
	typedef esc::Asset<sf::SoundBuffer> SoundAsset;

	public:

		enum GameState
		{
			INITIATING = 1,
			STARTING,
			GAMEOVER,
			EXITING
		};

		GameApplication();
		virtual ~GameApplication();

		int run();
		void setScreenSize(unsigned int , unsigned int);

		static sf::Texture		* loadTextureFromFile(const string & path);
		static sf::SoundBuffer	* loadSoundFromFile  (const string & path);
	
	private:

		
		GameState gameLoop();
		bool loadGameAssets();

		GameState gameState;
		unsigned int screen_width;
		unsigned int screen_height;

		sf::RenderWindow window;
		sf::Event event;

		unique_ptr<TetrisPlayField> tpf;
		esc::AssetManager assetManager;
		TextureAsset * textures;
		SoundAsset * sounds;

		unique_ptr<SoundDirector> soundDirector;

		sf::Clock clock;
};

#endif