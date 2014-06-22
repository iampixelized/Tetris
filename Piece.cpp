#include "Piece.hpp"

Piece::Piece(const string &oname, sf::Vector2f &pos, esc::AssetManager &am, int p)
	: esc::Object(oname, pos, am), pieceNumber((p<1)? 1:p)
{
	
}

Piece::~Piece()
{

}

void Piece::update(float e)
{

}

int Piece::getPieceNumber() const
{
	return pieceNumber;
}

void Piece::perceivePlayField(TetrisPlayField &tpf)
{
	playField = &tpf;
}

void Piece::deploy()
{
	sf::Vector2i pos = sf::Vector2i(esc::Object::getPosition() - playField->getPosition());
	pos.x /= playField->getGridOffset();
	pos.y /= playField->getGridOffset();
	
	playField->setActive(pos, true);
}
