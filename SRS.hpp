#ifndef SRS_HPP
#define SRS_HPP

#include<string>
using std::string;

#include "RotationSystem.hpp"
#include "Tetromino.hpp"

class SRS : public RotationSystem
{
	public:

		SRS(Tetromino::TetrominoType);
		virtual ~SRS();
		virtual SRS * getStandard();
};

#endif