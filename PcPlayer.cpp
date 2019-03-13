#include "PcPlayer.h"

int PcPlayer::CalculateFinalY(const Ball& ball) {
	int tempY;
	int tempDirY = ball.getYdirection();
	int steps;
	if (ball.getXdirection() == -1) // the ball is moving left
	{
		tempY = ball.getLeftEdgeY();
		steps = ball.getLeftEdgeX() - getX() - 1; // calculate how many steps the ball would make
	}
	else // the ball is moving right
	{
		tempY = ball.getRightEdgeY();
		steps = getX() - ball.getRightEdgeX() - 1; // calculate how many steps the ball would make
	}
	for (int i = 0; i < steps; i++) // simulate all steps the ball will do until reaches the board line
	{
		if (Screen::isOn_Y_Edge({ 0, tempY, '*' }, tempDirY)) //the ball hit the edge and changes direction
			tempDirY *= -1;
		tempY += tempDirY; //update the y position one step
	}
	return tempY;
}