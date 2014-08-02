#ifndef PIECE
#define PIECE

#include "TetrisPlayField.hpp"
#include "AssetManager.hpp"
#include "Object.hpp"

class Piece : public esc::Object
{
	public:

		Piece(const string &, const sf::Vector2f &pos, esc::AssetManager &, int);
		virtual ~Piece();

		virtual void update(float);
		int getPieceNumber() const;
		void perceivePlayField(TetrisPlayField &);
		
		void connectPiece(Piece &);
		Piece * getImmediatePiece() const;

	private:

		int pieceNumber;
		TetrisPlayField * playField;
		Piece * immediatePiece;
};

#endif