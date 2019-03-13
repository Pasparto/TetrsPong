#pragma once
#include <stdlib.h>
#include "Player.h"

class PcPlayer : public Player
{
	int m_level = -1;
public:
	//+-------------------------------Enums------------------------------------------------+
	enum class Levels { NOVICE = 10, GOOD = 40, BEST = -1 };
	//+-------------------------------C'tors & D'tor---------------------------------------+
	PcPlayer() = default;
	PcPlayer(const Point& down, const Point& up) : Player(down, up) {}
	~PcPlayer() {}
	//+-------------------------------Get\Set Functions---------------------------------------+
	void setLevel(Levels level) {
		m_level = (int)level;
	}

	int getLevel() { return m_level; }
	//+--------------------------Actions Board Functions-----------------------------------+
	void move(Ball& ball)
	{
		setColor(COLOR::BLUE_TEXT);
		static int finalY;
		static int levelRand = 1;

		if (getLevel() != (int)Levels::BEST && (checkBallPosition(ball) == BallPosition::CENTER_HIT || checkBallPosition(ball) == BallPosition::CORNER_HIT || checkBallPosition(ball) == BallPosition::MISSED))
		{
			levelRand = randNumbers(getLevel());
		}

		finalY = CalculateFinalY(ball); // calculate final position

		if (levelRand == 0) { // 0 is a random numer for missing the ball
			if (finalY >= getDownY() - 3 && finalY <= getUpY() + 3) //needs to move board according to miss the ball
			{
				if (finalY >= 12)
					moveBoardUp();
				else
					moveBoardDown();
			}

		}
		else
		{
			if (getSide() == Player::Sides::LEFT && ball.getXdirection() == -1) {
				if (getUpY() < finalY + 1)
					moveBoardDown();
				else if (getDownY() > finalY - 1)
					moveBoardUp();
			}
			else if (getSide() == Player::Sides::RIGHT && ball.getXdirection() == 1)
			{
				if (getUpY() < finalY + 1)
					moveBoardDown();
				else if (getDownY() > finalY - 1)
					moveBoardUp();
			}
		}

	}

	int CalculateFinalY(const Ball& ball);

	int randNumbers(int level) {
		return rand() % level;
	}
};
