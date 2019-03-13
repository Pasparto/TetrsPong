#include "UserPlayer.h"

//+--------------------------Actions board functions-----------------------------------+

void UserPlayer::handleKey(char c)
{//setColor(COLOR::PINK_BACKGROUND);		//dddsetColor(COLOR::PINK_BACKGROUND);
	curPress = c;
}

void UserPlayer::move(Ball& ball) {
	setColor(COLOR::BLUE_TEXT);
	if (curPress == m_kbChars[kbUp])
	{
		if (getUpY() > Screen::MIN_Y + 2)
		{
			moveBoardUp();
		}
	}
	else if (curPress == m_kbChars[kbDown])
	{
		if (getDownY() < Screen::MAX_Y - 2)
		{
			moveBoardDown();
		}
	}
	else if (curPress == m_kbChars[kbBomb])
	{
		if (ball.getbombflag()) {
			ball.setState(Ball::BECOMING);
			ball.setbombflag(false);
			ball.resetpass40();
		}
	}
	curPress = 0;
}

