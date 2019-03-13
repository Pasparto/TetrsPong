#include "Ball.h"
int Ball::m_Counterit = 0;

//+-------------------------------Actions Functions------------------------------+
// erase the ball and draw it again in the middle
void Ball::restart() {
	eraseBall();
	setBall(Screen::MAX_X / 2, Screen::MAX_Y / 2, (Screen::MAX_X / 2) + 3, sign);
}

//This function moves the call by the data members Xdirection, Ydirection
void Ball::move()
{
	eraseBall();
	m_leftEdge.move(Xdirection, Ydirection);
	m_rightEdge.move(Xdirection, Ydirection);
	drawBall();

	Ball::m_Counterit++; // Update the counter iterator
}

//Function for erase the ball(puts " " in every point of the ball matrix)
void Ball::eraseBall() {
	Point tempTopP(m_leftEdge.getX() + 1, m_leftEdge.getY() - 1, sign);
	Point tempBottomP(m_leftEdge.getX() + 1, m_leftEdge.getY() + 1, sign);
	while (tempTopP.getX() != m_rightEdge.getX()) {//Draw first and last rows of the ball
		tempTopP.erase();
		tempTopP.move(1, 0);
		tempBottomP.erase();
		tempBottomP.move(1, 0);
	}
	tempTopP = m_leftEdge;
	while (tempTopP.getX() != m_rightEdge.getX()) {//draw middle row
		tempTopP.erase();
		tempTopP.move(1, 0);
	}
	tempTopP.erase();
}

// Draw the ball
void Ball::drawBall()
{
	setColor(m_curState->getcolor());
	Point tempTopP(m_leftEdge.getX() + 1, m_leftEdge.getY() - 1, sign);
	Point tempBottomP(m_leftEdge.getX() + 1, m_leftEdge.getY() + 1, sign);
	while (tempTopP.getX() != m_rightEdge.getX()) {//Draw first and last rows of the ball
		tempTopP.draw(sign);
		tempTopP.move(1, 0);
		tempBottomP.draw(sign);
		tempBottomP.move(1, 0);
	}
	tempTopP = m_leftEdge;
	while (tempTopP.getX() != m_rightEdge.getX()) {//draw middle row
		tempTopP.draw(sign);
		tempTopP.move(1, 0);
	}
	tempTopP.draw(sign);


}

// Check if the ball hit the board
int Ball::hitInBoard(int x, int y, Ball::XDirection dir, int whichBoard) const {
	if (Xdirection < 0) {
		if (m_leftEdge.getX() == x + 1 || m_leftEdge.getX() == x) {
			if (m_leftEdge.getY() >= y && m_leftEdge.getY() <= y + 2) {
				return 1;
			}
			else if ((m_leftEdge.getY() == y - 1 && dir == Down) || (m_leftEdge.getY() == y + 3 && dir == Up)) {
				return 2;
			}
		}
		if (m_leftEdge.getX() == x) {
			if (m_leftEdge.getY() + 2 == y && dir == Down || m_leftEdge.getY() - 2 == (y + 2) && dir == Up) {
				return 2;
			}
		}
	}
	if (Xdirection > 0) {
		if (m_rightEdge.getX() == (x - 1) || m_rightEdge.getX() == x) {
			if (m_rightEdge.getY() >= y && m_rightEdge.getY() <= y + 2) {
				return 1;
			}
			else if ((m_rightEdge.getY() == (y - 1) && dir == Down) || (m_rightEdge.getY() == y + 3) && dir == Up) {
				return 2;
			}
		}
		if (m_rightEdge.getX() == x) {
			if (m_rightEdge.getY() + 2 == y && dir == Down || m_rightEdge.getY() - 2 == (y + 2) && dir == Up) {
				return 2;
			}
		}
	}
	if ((whichBoard == 0 && m_leftEdge.getX() < x) || (whichBoard == 1 && m_rightEdge.getX() > x)) {
		return 0;
	}
	else
		return 3;
}

// Bounce animation
void Ball::bounce(int yBoard, int xBoard, int whichBoard) {
	eraseBall();
	m_leftEdge.move(Xdirection, Ydirection);
	m_rightEdge.move(Xdirection, Ydirection);
	drawBall();
	Point tempTopP(m_leftEdge.getX() + 1, m_leftEdge.getY() - 1, sign);//0,1
	Point tempBottomP(m_leftEdge.getX() + 1, m_leftEdge.getY() + 1, sign);//2,1
	Point tempCenterP(m_leftEdge.getX() + 1, m_leftEdge.getY(), sign);//1,1
	Point * arrp[3]{ &tempTopP,&tempCenterP,&tempBottomP };
	if (whichBoard == 0) {//left board
		for (int i = 0; i < 3; i++) {
			if (arrp[i]->getX() == xBoard && arrp[i]->getY() >= yBoard && arrp[i]->getY() <= (yBoard + 2))
			{
				arrp[i]->drawBoardsign();
			}

		}
		if (m_leftEdge.getX() < xBoard) {
			m_leftEdge.erase();
		}
	}
	if (whichBoard == 1) {//right board
		for (int i = 0; i < 3; i++) {
			arrp[i]->move(1, 0);
		}
		for (int i = 0; i < 3; i++) {
			if (arrp[i]->getX() == xBoard && arrp[i]->getY() >= yBoard && arrp[i]->getY() <= (yBoard + 2))
			{
				arrp[i]->drawBoardsign();
			}
		}
		if (m_rightEdge.getX() > xBoard) {
			m_rightEdge.erase();
		}
	}
	Sleep(100);
}
