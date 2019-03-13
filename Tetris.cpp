#include "Tetris.h"

//+--------------------------Actions board functions-----------------------------------+

short int Tetris::findEmptyColoumn() { // The function return the first available *coloumn* the board can fit
	int xCor = deadBoardCopy.getX();
	int yCor = deadBoardCopy.getUpY() - 1; // bottom

	if (deadBoardCopy.getSide() == Player::Sides::LEFT)
	{
		for (short int i = xCor - 1; i >= 0; i--)
		{
			for (short int j = yCor; j >= yCor - 2; j--)
			{
				if (Graveyard[j][i] == 1)
					return i + 1;
			}
		}
		return 0;
	}
	else
	{
		for (short int i = xCor + 1; i <= 79; i++)
		{
			for (short int j = yCor; j >= yCor - 2; j--)
			{
				if (Graveyard[j][i] == 1)
					return i - 1;
			}
		}
		return 79;
	}
}

void Tetris::updateGraveyard(short int emptyColoumn) {
	setGraveyard(deadBoardCopy.getDownY(), emptyColoumn); // the top
	setGraveyard(deadBoardCopy.getDownY() - 1, emptyColoumn); // the middle
	setGraveyard(deadBoardCopy.getUpY() - 1, emptyColoumn); // the bottom															
}

void Tetris::moveTetris(short int emptyColoumn) {
	int xCor = deadBoardCopy.getX();

	if (deadBoardCopy.getSide() == Player::Sides::LEFT)
	{
		while (xCor >= emptyColoumn + 1) // the screen value is 1 bigger the the matrix
		{
			deadBoardCopy.drawBoard();
			Sleep(100);
			deadBoardCopy.eraseBoard();
			deadBoardCopy.m_Up.move(-1, 0);
			deadBoardCopy.m_Down.move(-1, 0);
			xCor -= 1;
		}
	}
	else
	{
		while (xCor <= emptyColoumn - 1) // the screen value is 1 bigger the the matrix
		{
			deadBoardCopy.drawBoard();
			Sleep(100);
			deadBoardCopy.eraseBoard();
			deadBoardCopy.m_Up.move(1, 0);
			deadBoardCopy.m_Down.move(1, 0);
			xCor += 1;
		}
	}
	deadBoardCopy.drawBoard();

}

void Tetris::flushGraveyard() {
	for (int i = 0; i < Screen::MAX_Y; i++)
	{
		for (int j = 0; j < Screen::MAX_X + 1; j++)
		{
			Graveyard[i][j] = 0;
		}
	}
}

void Tetris::reDrawTetris() {
	for (int i = 0; i < Screen::MAX_Y; i++)
	{
		for (int j = 0; j < Screen::MAX_X + 1; j++)
		{
			if (Graveyard[i][j] == 1)
			{
				gotoxy(j, i + 1);
				cout << "#";
			}
		}
	}
}

bool Tetris::isFullColoumn(int coloumn) {
	for (int i = 3; i < Size::ROWS; i++)
	{
		if (Graveyard[i][coloumn] == 0) {
			return FALSE;
		}
	}
	return TRUE;
}

void Tetris::deleteColoum(int coloumn) {
	for (int i = 3; i < Size::ROWS; i++)
	{
		Graveyard[i][coloumn] = 0;
		gotoxy(coloumn, i + 1);
		cout << " "; // the first delete the field + the last wont deleted
	}
}

void Tetris::clear5Back(int xCor) {
	if (deadBoardCopy.getSide() == Player::Sides::RIGHT)
	{
		for (int i = 3; i < Size::ROWS; i++)
		{
			for (int j = xCor; j < xCor + 5; j++)
			{
				gotoxy(j, i + 1);
				cout << " ";
				Graveyard[i][j] = 0;
				printGraveyard();
			}

		}
	}
	else
	{
		for (int i = 3; i < Size::ROWS; i++)
		{
			for (int j = xCor; j > xCor - 5; j--)
			{
				gotoxy(j, i + 1);
				cout << " ";
				Graveyard[i][j] = 0;
			}

		}
	}
}


