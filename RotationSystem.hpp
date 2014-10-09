#ifndef ROTATIONSYSTEM_HPP
#define ROTATIONSYSTEM_HPP

#include<vector>
using std::vector;

#include<string>
using std::string;

#include<SFML/Graphics.hpp>

#include "TetrisPlayField.hpp"
#include "TetrominoType.hpp"

class Tetromino;

class RotationSystem
{
	struct BlockConfigurations
	{
		vector<sf::Vector2i> _0Config;
		vector<sf::Vector2i> _90Config;
		vector<sf::Vector2i> _180Config;
		vector<sf::Vector2i> _270Config;
	};

	public:
	
		virtual ~RotationSystem();

		virtual void setConfiguration(int) = 0;
		virtual sf::Vector2i getCorrectPosition(int) = 0;
		virtual RotationSystem * createNewInstance() = 0;

		const vector<sf::Vector2i> & getBlockConfiguration(int);
		const vector<sf::Vector2i> & getBlockNextConfiguration(int);
		const vector<sf::Vector2i> & getBlockPreviousConfiguration(int);

		const BlockConfigurations & getBlockConfigurations();
		virtual RotationSystem * getStandard();
		const string & getStandardName() const;
		virtual int getSpawningPosition(int);
		
		void updateCurrentPosition(const sf::Vector2i &);
		const sf::Vector2i & getCurrentPosition() const;
		void updateCurrentFace(int);
		int getCurrentFace() const;

		TetrisPlayField * getTetrisPlayField() const;
		void setKickEnable(bool);
		bool isKickEnabled() const;
		TetrominoType getHostType();

		void resetCount();

	protected:

		BlockConfigurations bConfig;
		RotationSystem(const string & , TetrisPlayField &);
		void resetConfigurations();

		bool checkProjectedPosition(const sf::Vector2i &, int);
		void updateType(TetrominoType);

	private:
		
		string name;
		sf::Vector2i currentPosition;
		int currentFace;
		bool _isKickEnabled;
		TetrisPlayField * playField;
		TetrominoType type;
			
};

#endif