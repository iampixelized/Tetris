#ifndef MIMIC_HPP
#define MIMIC_HPP

#include "IUpdatableObject.hpp"
#include "IDrawableObject.hpp"
#include "TetrominoFactory.hpp"
#include "ObjectLayer.hpp"

#include "Tetromino.hpp"
#include "TetrominoDropper.hpp"

class Mimic : public esc::IUpdatableObject , esc::IDrawableObject 
{
	public:
		
		Mimic(esc::ObjectLayer<Tetromino> &, Tetromino::RPtr rptr , esc::AssetManager&);
		virtual ~Mimic();

		void initialize(Tetromino * t);
		void initialize();

		void project();
		virtual void draw(sf::RenderWindow*);
		virtual void update(float);

	private:
		
		Tetromino * ghost;
		TetrominoFactory factory;
		TetrominoFactory::TLAYER * layer;
		TetrominoDropper dropper;
};


#endif