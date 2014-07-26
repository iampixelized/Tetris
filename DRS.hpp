#ifndef DRS_HPP
#define DRS_HPP

#include<string>
using std::string;

#include "RotationSystem.hpp"
#include "Tetromino.hpp"

class DRS : public RotationSystem
{
	public:

		explicit DRS();
		virtual ~DRS();

		virtual DRS * getStandard();
		virtual void setConfiguration(int);
};

#endif