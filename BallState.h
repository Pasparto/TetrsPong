#pragma once
// Forward declarations
class Ball;
//#include "Ball.h"
//class Player;

class BallState // State Interface
{
public:
	//+-------------------------------C'tors & D'tor---------------------------------------+
	virtual ~BallState() {};
	//+--------------------------Actions Ball functions------------------------------------+
	virtual void Away(Ball *ball) = 0;
	virtual void Missed(Ball *ball) = 0;
	virtual void Corner(Ball *ball) = 0;
	virtual void Center(Ball *ball) = 0;
};
