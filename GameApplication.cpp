#include<iostream>
using std::cout;
using std::endl;

#include<map>
using std::map;
using std::pair;

#include "GameApplication.hpp"
#include "RandomGenerator.hpp"
#include "TetrisLayer.hpp"

GameApplication::GameApplication()
	:
	gameState(INITIATING)
{	
	screen_width = 800;
	screen_height = 600;
}

GameApplication::~GameApplication()
{
	//
}

void GameApplication::setScreenSize(unsigned int width, unsigned int height)
{
	screen_width = (width < 800) ? 800 : width;
	screen_height = (height < 600) ? 600 : height;
}

int GameApplication::run()
{
	gameState = STARTING;
	
	tpf.reset(new TetrisPlayField(sf::Vector2f(10, 22)));
	tpf->setPosition(sf::Vector2f(100, 100));

	assetManager.addAsset("Textures", new TextureAsset(&GameApplication::loadTextureFromFile));
	textures = dynamic_cast<TextureAsset*>(assetManager.getAsset("Textures"));

	window.create(sf::VideoMode(screen_width, screen_height,32), "TETRIS");

	if (!loadGameAssets())
		return 1;

	if (gameLoop() == EXITING)
		window.close();

	return 0;
}

sf::Texture * GameApplication::loadTextureFromFile(const string & path)
{
	sf::Texture * t = new sf::Texture();
	
	if (!t->loadFromFile(path))
		return nullptr;

	return t;
}

GameApplication::GameState GameApplication::gameLoop()
{
	TetrisLayer tetrisLayer(*tpf.get(), assetManager);
	tetrisLayer.spawnTetromino();
	Tetromino * tetromino = tetrisLayer.getCurrentTetromino();

	while (window.isOpen())
	{

		float elapsed = clock.restart().asSeconds();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return EXITING;

			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Left)
				{
					tetromino->moveLeft();
				}
				else if (event.key.code == sf::Keyboard::Key::Right)
				{
					tetromino->moveRight();
				}
				else if (event.key.code == sf::Keyboard::Key::Up)
				{
					tetromino->rotateRight();
				}
				else if (event.key.code == sf::Keyboard::Key::Down)
				{

				}
				else if (event.key.code == sf::Keyboard::Key::Space)
				{

				}
			}
		}

		window.clear();

		tpf->drawGrid(&window);
		tetrisLayer.refreshLayer(elapsed, &window, true);

		window.display();
	}

	return STARTING;
}

bool GameApplication::loadGameAssets()
{
	map<string, string> assetList;
	assetList["blue_block"] = "asset/textures/blue_block.png";
	assetList["cyan_block"] = "asset/textures/cyan_block.png";
	assetList["green_block"] = "asset/textures/green_block.png";
	assetList["orange_block"] = "asset/textures/orange_block.png";
	assetList["purple_block"] = "asset/textures/purple_block.png";
	assetList["red_block"] = "asset/textures/red_block.png";
	assetList["yellow_block"] = "asset/textures/yellow_block.png";

	for (pair<string, string> p : assetList)
	{
		if (!textures->loadFromFile(p.first, p.second))
			return false;
	}

	return true;
}