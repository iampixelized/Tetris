#include<iostream>
using std::cout;
using std::endl;

#include "Scorer.hpp"

Scorer::Scorer(TetrisPlayField & pf)
	:
	  pField(&pf)
	, currentScore(0)
	, combo(0)
	, scoreIncrement(100)
	, streakElapsed(0.0f)
	, streakThreshold(5.0f)
	, _isScoreStreakTriggered(false)
{

}

Scorer::~Scorer(){}

void Scorer::update(float dt)
{
	if (_isScoreStreakTriggered)
	{
		streakElapsed += dt;
		
		if (streakElapsed >= streakThreshold)
		{
			_isScoreStreakTriggered = false;
			resetScoreStatus();
			streakElapsed -= 1.0 * pField->getClearedRowsSize();
			cout << "Streak expired after : " << streakElapsed << endl;
		}
	}
}

int Scorer::getScore()
{
	return currentScore;
}

void Scorer::setScoreIncrement(int inc)
{
	scoreIncrement = (inc <= 0) ? 100 : inc;
}

int Scorer::getScoreIncrement() const
{
	return scoreIncrement;
}


void Scorer::setStreakThreshold(float t)
{
	streakThreshold = (t < 1.0f) ? 1.0f : t;
}

void Scorer::makeScore()
{	
	int linesCleared = pField->getClearedRowsSize();
	
	combo += linesCleared;
	currentScore += linesCleared * scoreIncrement;
	_isScoreStreakTriggered = true;
	streakElapsed = 0.0f;
	
	cout << "Score : " << currentScore << endl;
	cout << "Combo : " << combo << endl;
}

void Scorer::resetScoreStatus()
{
	combo = 0;
	streakElapsed = 0.0f;
	_isScoreStreakTriggered = false;
}
