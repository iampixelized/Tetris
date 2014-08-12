#ifndef ROTATIONSYSTEM_HPP
#define ROTATIONSYSTEM_HPP

#include<vector>
using std::vector;

#include<string>
using std::string;

#include<map>
using std::map;

#include<SFML/Graphics.hpp>

class RotationSystem
{
	public:

		typedef map<string, map<int, sf::Vector2i>> CheckTable;

		struct BlockConfigurations
		{
			vector<sf::Vector2i> _0Config;
			vector<sf::Vector2i> _90Config;
			vector<sf::Vector2i> _180Config;
			vector<sf::Vector2i> _270Config;
		};

		virtual const vector<sf::Vector2i> & getBlockConfiguration(int);
		virtual const BlockConfigurations & getBlockConfigurations();
		
		virtual RotationSystem * getStandard() = 0;
		virtual void setConfiguration(int) = 0;

		const string & getStandardName() const;

		sf::Vector2i getCheckTableTest(const string &, int);
		const CheckTable & getCheckTable() const;

	protected:

		explicit RotationSystem(const string &);
		virtual ~RotationSystem();

		void reset();

		BlockConfigurations bConfig;
		CheckTable checkTable;

	private:
		
		string name;
			
};

#endif