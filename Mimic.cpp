#include<utility>

#include "Mimic.hpp"

Mimic::Mimic(Tetromino::RPtr rptr, esc::AssetManager & am)
	: layer(std::move(rptr), am)
{

}

Mimic::~Mimic(){}

void Mimic::initialize(Tetromino * t)
{
	if (t == nullptr) return;

	if (ghost != nullptr)
		layer.deleteObject(ghost->getID());
	
	ghost = layer.spawnTetromino(t->getType() , Tetromino::BlockColor::Ghost);
	t->setMimic(ghost);
	dropper.setTetromino(ghost);
	dropper.hardDrop(false);
}

void Mimic::project()
{
	dropper.hardDrop(false);
}

void Mimic::draw(sf::RenderWindow * w)
{
	layer.drawLayer(w);
}

void Mimic::update(float e)
{
	layer.updateLayer(e);
}

