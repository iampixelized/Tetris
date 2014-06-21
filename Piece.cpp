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