#include "Piece.hpp"

Piece::Piece(const string &pname, const sf::Vector2f &pos, esc::AssetManager &am, int s)
	: esc::Object(pname, pos, am)
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

void Piece::connectPiece(Piece & p)
{
	p.connectPiece(*immediatePiece);
	immediatePiece = &p;
}

Piece * Piece::getImmediatePiece() const
{
	return immediatePiece;
}

