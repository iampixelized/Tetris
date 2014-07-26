#include<iostream>
using std::cout;
using std::endl;

#include<map>
using std::map;
using std::pair;

#include "GameApplication.hpp"
#include "RandomGenerator.hpp"
#include "TetrominoKicker.hpp"
#include "TetrisLayer.hpp"
#include "DRS.hpp"

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
	
	tpf.reset(new TetrisPlayField);
	//tpf->setPosition(sf::Vector2f(180.0f, 180.0f));

	assetManager.addAsset("Textures", new TextureAsset(&GameApplication::loadTextureFromFile));
	textures = dynamic_cast<TextureAsset*>(assetManager.getAsset("Textures"));

	window.create(sf::VideoMode(screen_width, screen_height,32), "TETRIS");
	window.setFramerateLimit(40);

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
	DRS drs;
	//Set tetromino drop speed interval
	mechanics.dropInterval		= 0.8f;
	mechanics.lockTime			= 0.5f;
	mechanics.rotationSystem    = drs;

	TetrisLayer tetrisLayer(mechanics, *tpf.get(), assetManager);
	TetrominoKicker kicker(*tpf.get());

	//tetrisLayer.setDotPieces(0,  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
	tetrisLayer.setDotPieces(1,  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
	tetrisLayer.setDotPieces(2,  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
	tetrisLayer.setDotPieces(3,  { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 });
	tetrisLayer.setDotPieces(4,  { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 });
	//tetrisLayer.setDotPieces(5,  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(6,  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(7,  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(8,  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(9,  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(10, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(11, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(12, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	//tetrisLayer.setDotPieces(13, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	tetrisLayer.setDotPieces(14, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	tetrisLayer.setDotPieces(15, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
	tetrisLayer.setDotPieces(16, { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 });
	tetrisLayer.setDotPieces(17, { 0, 0, 0, 1, 1, 1, 1, 0, 1, 0 });
	tetrisLayer.setDotPieces(18, { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 });
	tetrisLayer.setDotPieces(19, { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 });

	Tetromino * tetromino = tetrisLayer.spawnTetromino();
	kicker.setTetromino(tetromino);

	cout << "Content number of t-layer : " << tetrisLayer.getLayerSize() << endl;

	while (window.isOpen())
	{

		float elapsed = clock.restart().asSeconds();

		if (tetromino->isLocked())
		{
			tetrisLayer.spawnTetromino();
			tetromino = tetrisLayer.spawnTetromino();
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return EXITING;

			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Left)
				{
					if (tetromino->checkMovement(-1))
						tetromino->moveLeft();
				}
				else if (event.key.code == sf::Keyboard::Key::Right)
				{
					if (tetromino->checkMovement(1))
						tetromino->moveRight();
				}
				else if (event.key.code == sf::Keyboard::Key::Up)
				{
					if (kicker.checkKick("right", 1))
						tetromino->rotateRight();
					else 
						kicker.kickTetromino(1);
				}
				else if (event.key.code == sf::Keyboard::Key::Down)
				{
					/*
						Note:
						Problem with soft drop plus automatic drop

						every time down button is pressed and the press 
						is occured before the dropInterval the press
						triggers + 1 drop count then another + 1 for
						soft drop after dropInterval making the drop count
						+ 2. Consequently the drop misses count and loses
						1 line when deployed.

						use hard drop for the meantime.
					*/

					 tetromino->softDrop();
					// tetromino->hardDrop();
				}
				else if (event.key.code == sf::Keyboard::Key::Space)
				{

				}
			}
		}

		window.clear();

		tpf->drawGrid(&window);
		tetrisLayer.refreshLayer(elapsed, &window);
		
		window.display();
	}

	return STARTING;
}

bool GameApplication::loadGameAssets()
{
	map<string, string> assetList;
	assetList["blue_block"	] = "asset/textures/blue_block.png";
	assetList["cyan_block"	] = "asset/textures/cyan_block.png";
	assetList["green_block"	] = "asset/textures/green_block.png";
	assetList["orange_block"] = "asset/textures/orange_block.png";
	assetList["purple_block"] = "asset/textures/purple_block.png";
	assetList["red_block"	] = "asset/textures/red_block.png";
	assetList["yellow_block"] = "asset/textures/yellow_block.png";
	assetList["marked_block"] = "asset/textures/marked_block.png";

	for (pair<string, string> p : assetList)
	{
		if (!textures->loadFromFile(p.first, p.second))
			return false;
	}

	return true;
}