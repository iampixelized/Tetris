#include "GameApplication.hpp"

int main()
{
	GameApplication app;
	app.setScreenSize(800, 600);

	return app.run();
}


//#include<iostream>
//using std::cout;
//using std::endl;
//
//#include<map>
//using std::map;
//using std::pair;
//
//#include<memory>
//using std::unique_ptr;
//
//#include<SFML/System/Clock.hpp>
//
//#include "ObjectLayer.hpp"
//#include "Tetromino.hpp"
//#include "TetrisPlayField.hpp"
//#include "GameApplication.hpp"
//#include "AssetManager.hpp"
//
//typedef esc::Asset<sf::Texture> TextureAsset;
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "");
//	sf::Event event;
//
//	esc::AssetManager assetManager;
//	TextureAsset * 	textures = dynamic_cast<TextureAsset*>(assetManager.getAsset("Textures"));
//
//	assetManager.addAsset("Textures", new TextureAsset(&GameApplication::loadTextureFromFile));
//	textures = dynamic_cast<TextureAsset*>(assetManager.getAsset("Textures"));
//
//	map<string, string> assetList;
//	assetList["blue_block"] = "asset/textures/blue_block.png";
//	assetList["cyan_block"] = "asset/textures/cyan_block.png";
//	assetList["green_block"] = "asset/textures/green_block.png";
//	assetList["orange_block"] = "asset/textures/orange_block.png";
//	assetList["purple_block"] = "asset/textures/purple_block.png";
//	assetList["red_block"] = "asset/textures/red_block.png";
//	assetList["yellow_block"] = "asset/textures/yellow_block.png";
//
//	for (pair<string, string> p : assetList)
//	{
//		if (!textures->loadFromFile(p.first, p.second))
//			return false;
//	}
//
//	TetrisPlayField tpf(sf::Vector2f(10, 22) , sf::Vector2f(100,100));
//	//esc::ObjectLayer<Tetromino> tetrominoLayer;
//	//tetrominoLayer.addNewObject(Tetromino::createTetromino(Tetromino::TetrominoType::I, Tetromino::BlockColor::Blue, tpf, assetManager));
//
//	Tetromino * tetromino = Tetromino::createTetromino(Tetromino::TetrominoType::I, Tetromino::BlockColor::Blue, tpf, assetManager);
//	//Tetromino tetromino(Tetromino::TetrominoType::I, Tetromino::BlockColor::Blue, tpf, assetManager);
//
//
//	sf::Clock clock;
//
//	while (window.isOpen())
//	{
//		float elapsed = clock.getElapsedTime().asSeconds();
//
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::KeyPressed)
//			{
//				if (event.key.code == sf::Keyboard::Key::Left)
//				{
//
//				}
//				else if (event.key.code == sf::Keyboard::Key::Right)
//				{
//					tetromino->rotateRight();
//				}
//				else if (event.key.code == sf::Keyboard::Key::Up)
//				{
//
//				}
//				else if (event.key.code == sf::Keyboard::Key::Down)
//				{
//
//				}
//				else if (event.key.code == sf::Keyboard::Key::Space)
//				{
//
//				}
//			}
//		}
//
//		window.clear();
//
//		tetromino->draw(&window);
//
//		window.display();
//	}
//
//	return 0;
//}
