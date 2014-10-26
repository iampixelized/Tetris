#include<iostream>
using std::cout;
using std::endl;

#include<map>
using std::map;
using std::pair;

#include "GameApplication.hpp"
#include "RandomGenerator.hpp"
#include "TetrominoDropper.hpp"
#include "ObjectLayer.hpp"
#include "TetrominoFactory.hpp"
#include "TetrominoType.hpp"
#include "Mimic.hpp"
#include "DRS.hpp"
#include "SRS.hpp"

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

	//
	esc::ObjectLayer<Tetromino> tetrominoLayer;
	//

	TetrominoFactory tetrominoFactory(tetrominoLayer, Tetromino::RPtr(new SRS(*tpf.get())), assetManager);
	Mimic mimic(tetrominoLayer, Tetromino::RPtr(new SRS(*tpf.get())), assetManager);

	TetrominoDropper dropper;
	dropper.setDropInterval(0.8f); 
	dropper.setLockInterval(0.5f);
	
	Tetromino * tetromino = tetrominoFactory.spawnTetromino();
	dropper.setTetromino(tetromino);
	mimic.initialize(tetromino);


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

				mimic.project();
			}
		}

		window.clear();

		if (tetromino->isLocked())
		{
			tpf->registerBlocks(tetromino);
			tetromino = tetrominoFactory.spawnTetromino();
			dropper.setTetromino(tetromino);
			mimic.initialize(tetromino);
		}

		if (tpf->getClearedRowsSize() > 0)
			tpf->shiftClearedRows();

		tpf->drawGrid(&window);

		mimic.update(elapsed);
		mimic.draw(&window);

		//dropper.update(elapsed);
		tetrominoLayer.updateLayer(elapsed);
		tetrominoLayer.drawLayer(&window);

		window.display();
	}

	return STARTING;
}

bool GameApplication::loadGameAssets()
{
	textures->addPath("blue_block"	 , "asset/textures/blue_block.png"		);
	textures->addPath("cyan_block"	 , "asset/textures/cyan_block.png"		);
	textures->addPath("green_block"	 , "asset/textures/green_block.png"		);
	textures->addPath("orange_block" , "asset/textures/orange_block.png"	);
	textures->addPath("purple_block" , "asset/textures/purple_block.png"	);
	textures->addPath("red_block"	 , "asset/textures/red_block.png"		);
	textures->addPath("yellow_block" , "asset/textures/yellow_block.png"	);
	textures->addPath("marked_block" , "asset/textures/marked_block.png"	);
	textures->addPath("ghost_block"	 , "asset/textures/ghost_block.png"		);

	if (!textures->checkAllAssets())
		return false;

	return true;
}