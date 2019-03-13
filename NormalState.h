#pragma once
#include "BallState.h"
#include "Ball.h"

class NormalState : public BallState // Normal State
{
public:
	//+-------------------------------C'tors & D'tor---------------------------------------+
	~NormalState() {};
	NormalState() {};
	//+--------------------------Actions Ball functions------------------------------------+
	void Away(Ball *ball) override {}

	void Missed(Ball *ball) override {
		ball->restart();
	}
	void Corner(Ball *ball) override {
		//ball->bounce(players[0]->getDownY(), players[0]->getX(), (int)players[0]->getSide());
		ball->changeXDirection();
		ball->changeYDirection();
	}
	void Center(Ball *ball) override {
		//ball->bounce(players[0]->getDownY(), players[0]->getX(), (int)players[0]->getSide());
		ball->changeXDirection();
	}
};

