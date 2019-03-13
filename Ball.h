#pragma once

#include <vector>
using namespace std;

#include "Point.h"
#include "Screen.h"
#include "Player.h"

class BallState;

class Ball {
	static const char sign = 'o';
	static int m_Counterit;
	Point m_rightEdge, m_leftEdge;
	int Xdirection = 1;
	int Ydirection = -1;
	bool m_bombflag = true;
	short m_pass40 = 0;

public:
	//+----------------------------------ENUMS---------------------------------------------+
	enum XDirection { Up, Down };
	enum States_enum { NORMAL = 0, BECOMING = 1, BOMB = 2, STATES_SIZE = 3 };
	//+-------------------------------C'tors & D'tor---------------------------------------+
	Ball(Point p1, Point p2) : m_leftEdge(p1), m_rightEdge(p2) {};
	Ball() :m_leftEdge(38, 11, 'o'), m_rightEdge(41, 11, 'o'), m_states(STATES_SIZE) {
		NormalState* normalState = new NormalState;
		m_states[NORMAL] = normalState;

		BecomingState* becomingState = new BecomingState;
		m_states[BECOMING] = becomingState;

		BombState* bombState = new BombState;
		m_states[BOMB] = bombState;

		m_curState = m_states[NORMAL];
		ranDirection();
	};
	~Ball() {
		delete m_states[NORMAL];
		delete m_states[BECOMING];
		delete m_states[BOMB];
	}
	//+--------------------------Actions Ball functions------------------------------------+
	void ranDirection() {
		Xdirection = rand() % 2;
		if (Xdirection == 0) {
			--Xdirection;
		}
		Ydirection = rand() % 2;
		if (Ydirection == 0) {
			--Ydirection;
		}
	}
	void move();
	void eraseBall();
	void drawBall();
	int hitInBoard(int x, int y, Ball::XDirection dir, int whichBoard) const;
	void restart();
	void changeYDirection() {
		Ydirection *= -1;
	}
	void changeXDirection() {
		Xdirection *= -1;
	}
	void bounce(int yBoard, int xBoard, int whichBoard);
	void Away() { m_curState->Away(this); }
	void Missed() { m_curState->Missed(this); }
	void Corner() { m_curState->Corner(this); }
	void Center() { m_curState->Center(this); }
	//+----------------------------Set/Get functions---------------------------------------+
	void setBall(int x1, int y1, int x2, char ch) {
		m_leftEdge.setX(x1);
		m_leftEdge.setY(y1);
		m_leftEdge.setChar(ch);
		m_rightEdge.setX(x2);
		m_rightEdge.setY(y1);
		m_rightEdge.setChar(ch);
	}
	Point getTopP() {
		Point top((this->m_leftEdge.getX()) + 1, (this->m_leftEdge.getY()) - 1, (char)sign);
		return top;
	}
	Point getButtomP() {
		Point buttom((this->m_leftEdge.getX()) + 1, (this->m_leftEdge.getY()) + 1, (char)sign);
		return buttom;
	}
	Ball::XDirection getBallDirection() const {
		return Ydirection == 1 ? Down : Up;
	}
	int getXdirection() const {
		return Xdirection;
	}
	int getYdirection() const {
		return Ydirection;
	}
	int getLeftEdgeX() const { return m_leftEdge.getX(); }
	int getLeftEdgeY() const { return m_leftEdge.getY(); }
	int getRightEdgeX() const { return m_rightEdge.getX(); }
	int getRightEdgeY() const { return m_rightEdge.getY(); }

	static int getCounterIt() { return m_Counterit; }
	static void setCouterIt(int setcounter = 0) { m_Counterit = setcounter; }

	bool getbombflag() const { return m_bombflag; }
	void setbombflag(bool bombflag) { m_bombflag = bombflag; }

	void incpass40() { m_pass40++; }
	void resetpass40() { m_pass40 = 0; }
	short getpass40() { return m_pass40; }

	void setState(States_enum state) {
		m_curState = m_states[state];
		if (state == BECOMING || state == BOMB)
			setCouterIt();
	}

public:	//+----------------------------Nested Classes---------------------------------------------+
	class BallState // State Interface
	{
		COLOR m_ballColor;
	public:
		//+-------------------------------C'tors & D'tor---------------------------------------+
		BallState(COLOR ballColor) : m_ballColor(ballColor) {}
		virtual ~BallState() {};
		//+-----------------------------Set\Get functions---------------------------------------+
		COLOR getcolor() { return m_ballColor; }
		//+--------------------------Actions Ball functions------------------------------------+
		virtual void Away(Ball *ball) = 0;
		virtual void Missed(Ball *ball) = 0;
		virtual void Corner(Ball *ball) = 0;
		virtual void Center(Ball *ball) = 0;
	}; // State Interface End




	class NormalState : public BallState // Normal State Class
	{
	public:
		//+-------------------------------C'tors & D'tor---------------------------------------+
		~NormalState() {};
		NormalState() :BallState(COLOR::GREEN_TEXT) {};
		//+--------------------------Actions Ball functions------------------------------------+
		void Away(Ball *ball) override {}

		void Missed(Ball *ball) override {
			ball->restart();
		}

		void Corner(Ball *ball) override {
			ball->changeXDirection();
			ball->changeYDirection();
		}

		void Center(Ball *ball) override {
			ball->changeXDirection();
		}
	}; // Normal State End




	class BecomingState : public BallState // Becoming a Bomb State
	{
	public:
		//+-------------------------------C'tors & D'tor---------------------------------------+
		~BecomingState() {}
		BecomingState() :BallState(COLOR::YELLOW_TEXT) {}
		//+--------------------------Actions Ball functions------------------------------------+
		void Away(Ball *ball) override {
			if (getCounterIt() == 7)
				ball->setState(Ball::BOMB);
		}

		void Missed(Ball *ball) override { /*handle in GameManager*/ }

		void Corner(Ball *ball) override {
			ball->setState(NORMAL);
			ball->changeXDirection();
			ball->changeYDirection();
		}

		void Center(Ball *ball) override {
			ball->setState(NORMAL);
			ball->changeXDirection();
		}


	};// Becoming a Bomb State End




	class BombState : public BallState // Bomb State
	{
	public:
		//+-------------------------------C'tors & D'tor---------------------------------------+
		~BombState() {}
		BombState() :BallState(COLOR::RED_TEXT) {}
		//+--------------------------Actions Ball functions------------------------------------+
		void Away(Ball *ball) override {
			if (getCounterIt() == 4)
				ball->setState(Ball::NORMAL);
		}

		void Missed(Ball *ball) override { /*handle in GameManager*/ }

		void Corner(Ball *ball) override {
			ball->restart();
			ball->setState(NORMAL);
		}

		void Center(Ball *ball) override {
			ball->restart();
			ball->setState(NORMAL);
		}
		//+-----------------------------Set\Get functions---------------------------------------+

	};// Bomb State End




	//+---------------------------------Ball Class----------------------------------------------+
private:
	BallState * m_curState;
	vector<BallState*> m_states;
public:
	BallState * getcurState() { return m_curState; }
};