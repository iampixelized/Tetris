#include<utility>

#include "Mimic.hpp"

Mimic::Mimic(esc::ObjectLayer<Tetromino> & olt, Tetromino::RPtr rs, esc::AssetManager & am)
	: 
	  layer(&olt)
	, factory(olt, std::move(rs), am)
{

}

Mimic::~Mimic(){}

void Mimic::initialize(Tetromino * t)
{
	if (t == nullptr) return;

	if (ghost != nullptr)
		layer->deleteObject(ghost->getID());
	
	ghost = factory.spawnTetromino(t->getType(), Tetromino::BlockColor::Ghost);
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
	layer->drawLayer(w);
}

void Mimic::update(float e)
{
	layer->updateLayer(e);
}

