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
#include "Scorer.hpp"

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
	assetManager.addAsset("Sounds", new SoundAsset(&GameApplication::loadSoundFromFile));
	
	textures = dynamic_cast<TextureAsset*>(assetManager.getAsset("Textures"));
	sounds = dynamic_cast<SoundAsset*>(assetManager.getAsset("Sounds"));

	window.create(sf::VideoMode(screen_width, screen_height,32), "Tetris SFML");
	window.setFramerateLimit(60);

	soundDirector.reset(new SoundDirector(*sounds));

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

sf::SoundBuffer * GameApplication::loadSoundFromFile(const string & path)
{
	sf::SoundBuffer * s = new sf::SoundBuffer();

	if (!s->loadFromFile(path))
		return nullptr;

	return s;
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

	Scorer scorer(*tpf.get());

	cout << "\n\n\n\n\n\n\n\nContent number of t-layer : " << tetrominoLayer.getSize() << endl;

	while (window.isOpen())
	{
		float elapsed = clock.restart().asSeconds();

		if (tpf->getPeakLevel() < 2)
		{
			cout << "Game Over" << endl;
			//soundDirector->playSound("gameover");
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
					{ 
						tetromino->moveLeft();
						soundDirector->playSound("move");
					}
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Right)
				{
					if (tetromino->checkMovement(1))
					{ 
						tetromino->moveRight();
						soundDirector->playSound("move");
					}
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Up)
				{
					if (tetromino->checkRotation(1)) tetromino->rotateRight();
					else tetromino->kick(1);

					soundDirector->playSound("rotate");
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Down)
				{
					dropper.softDrop();
					soundDirector->playSound("rotate");
				}
				else if (event.key.code == sf::Keyboard::Key::P)
				{
					pause = (pause)? false : true;
				}
				else if (!pause && event.key.code == sf::Keyboard::Key::Space)
				{
					dropper.hardDrop();
					soundDirector->playSound("harddrop");
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
		{
			scorer.makeScore();
			tpf->shiftClearedRows();

			if (tpf->getClearedRowsSize() == 1)
				soundDirector->playSound("lineclear1");
			else if (tpf->getClearedRowsSize() == 2)
				soundDirector->playSound("lineclear2");
			else if (tpf->getClearedRowsSize() == 3)
				soundDirector->playSound("lineclear3");	
			else if (tpf->getClearedRowsSize() == 4)
				soundDirector->playSound("tetris");
		}

		tpf->drawGrid(&window);

		dropper.update(elapsed);
		tetrominoLayer.updateLayer(elapsed);
		tetrominoLayer.drawLayer(&window);

		mimic.update(elapsed);
		mimic.draw(&window);

		scorer.update(elapsed);

		window.display();
	}

	tetrominoLayer.deleteAll();

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

	map<string , string> sfxlist;
	sfxlist["rotate"]		= "asset/sounds/rotate.wav";
	sfxlist["harddrop"]		= "asset/sounds/harddrop.wav";
	sfxlist["move"]			= "asset/sounds/move.wav";
	sfxlist["lineclear1"]	= "asset/sounds/lineclear1.wav";
	sfxlist["lineclear2"]	= "asset/sounds/lineclear2.wav";
	sfxlist["lineclear3"]	= "asset/sounds/lineclear3.wav";
	sfxlist["tetris"]		= "asset/sounds/tetris.wav";
	sfxlist["selectmove"]	= "asset/sounds/selectmove.wav";
	sfxlist["selected"]		= "asset/sounds/selected.wav";
	sfxlist["gameover"]		= "asset/sounds/gameover.wav";

	for (pair<string, string> slist : sfxlist)
	{
		if(!sounds->loadFromFile(slist.first , slist.second))
			return false;
	}

	if (!textures->checkAllAssets())
		return false;

	return true;
}