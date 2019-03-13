#pragma once

#include "Point.h"
#include "Ball.h"
#include "Screen.h"
#include "utils.h"

// forward declaration
class Ball;

class Player {
	Point m_Up, m_Down;
	friend class Tetris;
public:
	//+----------------------------------ENUMS---------------------------------------------+
	enum class BallPosition { MISSED, CENTER_HIT, CORNER_HIT, AWAY };
	enum class Sides { LEFT, RIGHT };
	//+-------------------------------C'tors & D'tor---------------------------------------+
	Player() = default;
	Player(const Point& down, const Point& up) : m_Down(down), m_Up(up) {}
	virtual ~Player() {};
	//+--------------------------Actions board functions-----------------------------------+
	void drawBoard();
	void eraseBoard();
	void reposition(int steps);
	void moveBoardUp() {
		m_Up.erase();
		m_Up.move(0, -1); // when we decrease we going up
		m_Down.move(0, -1);
		m_Down.draw();
	}
	void moveBoardDown() {
		m_Down.erase();
		m_Down.move(0, 1);// when we increase we going down
		m_Up.move(0, 1);
		m_Up.draw();
	}
	BallPosition checkBallPosition(const Ball& ball);

	virtual void move(Ball& cBall) {};
	//+----------------------------Set/Get functions---------------------------------------+
	int getX()const {
		return m_Up.getX();
	}
	int getUpY()const {
		return m_Up.getY();
	}
	int getDownY()const {
		return m_Down.getY();
	}

	void setDown(int x, int y)
	{
		m_Down.setX(x);
		m_Down.setY(y);
	}
	void setUp(int x, int y)
	{
		m_Up.setX(x);
		m_Up.setY(y);
	}
	void setDown(int x, int y, char c)
	{
		m_Down.setX(x);
		m_Down.setY(y);
		m_Down.setChar(c);
	}
	void setUp(int x, int y, char c)
	{
		m_Up.setX(x);
		m_Up.setY(y);
		m_Up.setChar(c);
	}

	Sides getSide();
};