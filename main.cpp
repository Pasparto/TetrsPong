#include "GameManager.h"

int main() {
	//hide cursor and clean sreen
	hideConsoleCursor();

	GameManager gManager;

	char userInput = '0';
	while (userInput != '9')
	{
		if (!gManager.getisPlaying())
		{
			gManager.printMenu(gManager.getisStarted());
			cin >> userInput;
			gManager.menuActions(userInput);
		}
		else
		{

		}
	}
}

/*
-------------------------------------------------------FIRST-----------------------------
//Ball ball({ 5, 5, '@' });
board.draw();
KeyboardManager kbManager;
kbManager.registerKbListener(&board);
bool missed = false;

while (!missed) {
	for (int i = 0; i < 10; ++i) {
		kbManager.handleKeyboard();
		Sleep(10);
	}
	ball.move();
	// check if ball missed board
	Board::BallPosition state = board.checkBallPosition(ball);
	switch (state) {
	case Board::BallPosition::AWAY:
		break;
	case Board::BallPosition::MISSED:
		missed = true;
		break;
	case Board::BallPosition::CORNER_HIT:
		ball.changeXDirection(); // no break intentionally - change also the Y dir!!!
	case Board::BallPosition::CENTER_HIT:
		ball.changeYDirection();
		break;
	}
}

-------------------------------------------------------SECOND-----------------------------
bool missed = false;

while (!missed) {
for (int i = 0; i < 10; ++i) {
kbManager.handleKeyboard();
Sleep(10);
}
ball.move();
// check if ball missed board
Board::BallPosition stateLeft = playerLeft.checkBallPosition(ball);
Board::BallPosition stateRight = playerRight.checkBallPosition(ball);

switch (stateLeft) {
case Board::BallPosition::AWAY:
break;
case Board::BallPosition::MISSED:
missed = true;
break;
case Board::BallPosition::CORNER_HIT:
ball.changeXDirection(); // no break intentionally - change also the Y dir!!!
case Board::BallPosition::CENTER_HIT:
ball.changeYDirection();
break;
}

switch (stateRight) {
case Board::BallPosition::AWAY:
break;
case Board::BallPosition::MISSED:
missed = true;
break;
case Board::BallPosition::CORNER_HIT:
ball.changeXDirection(); // no break intentionally - change also the Y dir!!!
case Board::BallPosition::CENTER_HIT:
ball.changeYDirection();
break;
}
}
*/