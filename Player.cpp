#pragma once

#include "Player.h"

//+--------------------------Actions board functions-----------------------------------+

void Player::drawBoard()
{
	setColor(COLOR::BLUE_TEXT);
	Point temp = m_Down;
	temp.draw();
	while (temp != m_Up) {
		temp.move(0, 1);
		temp.draw();
	}
}

void Player::eraseBoard() {
	Point temp = m_Down;
	temp.erase();
	while (temp != m_Up) {
		temp.move(0, 1);
		temp.erase();
	}
}

void Player::reposition(int steps) {
	eraseBoard();
	if (getSide() == Sides::LEFT)
	{
		setDown(getX() + steps, 10);
		setUp(getX() + steps, 12);
	}
	else
	{
		setDown(getX() - steps, 11);
		setUp(getX() - steps, 13);
	}
	drawBoard();
}

Player::BallPosition Player::checkBallPosition(const Ball & ball)
{
	int ballpos = ball.hitInBoard(this->getX(), this->getDownY(), ball.getBallDirection(), (int)getSide());

	switch (ballpos)
	{
	case 0:
		return BallPosition::MISSED;
	case 1:
		return BallPosition::CENTER_HIT;
	case 2:
		return BallPosition::CORNER_HIT;
	case 3:
		return BallPosition::AWAY;
	}
}

Player::Sides Player::getSide() { // check which side of the screen the board is playing
	return (getX() > (Screen::RIGHT_DEAD) ? Sides::RIGHT : Sides::LEFT);
}