#ifndef DRS_HPP
#define DRS_HPP

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<map>
using std::map;

#include "RotationSystem.hpp"
#include "TetrisPlayField.hpp"

class Tetromino;

class DRS : public RotationSystem
{
	typedef map<int , vector<sf::Vector2i>> CheckTable; 

	public:

		explicit DRS(TetrisPlayField &);
		virtual ~DRS();

		virtual DRS * getStandard();
		virtual void setConfiguration(int);
		virtual sf::Vector2i getCorrectPosition(int);

		int getSpawningPosition(int);

	private:
		
		CheckTable checkTable;
};

#endif