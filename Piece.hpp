#ifndef PIECE_HPP
#define PIECE_HPP

#include<string>
using std::string;

#include<SFML/Graphics.hpp>

#include "TetrisPlayField.hpp"
#include "AssetManager.hpp"
#include "Object.hpp"

class Piece : public esc::Object
{
	public:

		Piece(const string &, sf::Vector2f & pos, esc::AssetManager &, int);
		virtual ~Piece();

		virtual void update(float);
		int getPieceNumber() const;
		void perceivePlayField(TetrisPlayField &);

	private:

		int pieceNumber;
		TetrisPlayField * playField;
};

#endif