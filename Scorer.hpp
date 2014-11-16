#ifndef SCORER_HPP
#define SCORER_HPP

#include "IUpdatableObject.hpp"
#include "TetrisPlayField.hpp"

class Scorer : esc::IUpdatableObject
{
	public:

		explicit Scorer(TetrisPlayField &);
		virtual ~Scorer();

		virtual void update(float elapsedTime);

		int getScore();
		void setScoreIncrement(int inc);
		int getScoreIncrement() const;

		bool isScoreStreakTriggered() const;
		void setStreakThreshold(float threshold);
		virtual void makeScore();


	private:

		void resetScoreStatus();

		int currentScore;
		int combo;
		int scoreIncrement;

		float streakElapsed;
		float streakThreshold;

		bool _isScoreStreakTriggered;

		TetrisPlayField * pField;

};

#endif