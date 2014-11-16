#ifndef SRS_HPP
#define SRS_HPP

#include<string>
using std::string;

#include<map>
using std::map;
using std::pair;

#include<vector>
using std::vector;

#include "RotationSystem.hpp"
#include "TetrisPlayField.hpp"

class SRS : public RotationSystem
{
	typedef map<int , map<int, vector<sf::Vector2i>>> CheckTable;

	public:
		
		explicit SRS(TetrisPlayField &);
		virtual ~SRS();

		virtual SRS * getStandard();
		virtual void setConfiguration(int);
		virtual sf::Vector2i getCorrectPosition(int);
		virtual SRS * createNewInstance();

		int getSpawningPosition(int);

	private:
		
		TetrominoType hostType;

		CheckTable checkTable;
		CheckTable checkTableI;
};

#endif
