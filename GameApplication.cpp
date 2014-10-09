#include<iostream>
using std::cout;
using std::endl;

#include<map>
using std::map;
using std::pair;

#include "GameApplication.hpp"
#include "RandomGenerator.hpp"
#include "TetrominoDropper.hpp"
#include "TetrominoLayer.hpp"
#include "TetrominoType.hpp"
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
	tpf->setPosition(sf::Vector2f(180.0f, 180.0f));

	assetManager.addAsset("Textures", new TextureAsset(&GameApplication::loadTextureFromFile));
	textures = dynamic_cast<TextureAsset*>(assetManager.getAsset("Textures"));

	window.create(sf::VideoMode(screen_width, screen_height,32), "Tetris SFML");
	window.setFramerateLimit(60);

	if (!loadGameAssets())
		return 1;

	if (gameLoop() == EXITING)
		window.close();

	system("pause");
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
	bool pause = false;
	DRS drs(*tpf.get()); // DTET Rotation System
		
	TetrominoLayer tetrominoLayer(drs , assetManager);

	TetrominoDropper dropper;
	dropper.setDropInterval(0.8f);
	dropper.setLockInterval(0.5f);

	//tetrominoLayer.setDotPieces(3,  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(4,  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
	//tetrominoLayer.setDotPieces(5,  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
	//tetrominoLayer.setDotPieces(6,  { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 });
	//tetrominoLayer.setDotPieces(7,  { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 });
	//tetrominoLayer.setDotPieces(8,  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(9,  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(10, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(11, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(12, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(13, { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(14, { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(15, { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(16, { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(17, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//tetrominoLayer.setDotPieces(18, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
	//tetrominoLayer.setDotPieces(19, { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 });
	//tetrominoLayer.setDotPieces(20, { 1, 0, 0, 1, 1, 1, 1, 0, 1, 0 });
	//tetrominoLayer.setDotPieces(21, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 });
	//tetrominoLayer.setDotPieces(22, { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 });

	Tetromino * tetromino = tetrominoLayer.spawnTetromino();
	dropper.setTetromino(tetromino);

	cout << "\n\n\n\n\n\n\n\nContent number of t-layer : " << tetrominoLayer.getSize() << endl;

	while (window.isOpen())
	{
		float elapsed = clock.restart().asSeconds();

		if (tpf->getPeakLevel() < 2)
		{
			cout << "Game Over" << endl;
			return GAMEOVER;
		}

		while (window.pollEvent(event))
		{
			// COnvert to switch...

			if (event.type == sf::Event::Closed)
				return EXITING;

			else if (event.type == sf::Event::KeyPressed)
			{
				if (!pause && event.key.code == sf::Keyboard::Key::Left)
				{
					if (tetromino->checkMovement(-1))
						tetromino->moveLeft();
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Right)
				{
					if (tetromino->checkMovement(1))
						tetromino->moveRight();
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Up)
				{
					if (tetromino->checkRotation(1)) tetromino->rotateRight();
					else tetromino->kick(1);
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Down)
				{
					dropper.softDrop();
				}
				else if (event.key.code == sf::Keyboard::Key::P)
				{
					pause = (pause)? false : true;
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Space)
				{
					dropper.hardDrop();
				}
				else if (event.key.code == sf::Keyboard::Key::Escape)
				{
					return EXITING;
				}
			}
		}

		window.clear();

		if (tetromino->isLocked())
		{
			tpf->registerBlocks(tetromino);
			tetromino = tetrominoLayer.spawnTetromino();
			dropper.setTetromino(tetromino);
		}

		if (tpf->getClearedRowsSize() > 0)
			tpf->shiftClearedRows();

		tpf->drawGrid(&window);
		tetrominoLayer.updateLayer(elapsed);
		dropper.update(elapsed);
		tetrominoLayer.drawLayer(&window);


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
	assetList["ghost_block"]  = "asset/textures/ghost_block.png";

	for (pair<string, string> p : assetList)
	{
		if (!textures->loadFromFile(p.first, p.second))
			return false;
	}

	return true;
}