#pragma once

#include <iostream>
#include <fstream>
#include "Player.h"
using namespace std;

class Tetris
{
private:
	enum Size { ROWS = Screen::MAX_Y, COL = Screen::MAX_X + 1 };
	short int Graveyard[ROWS][COL] = { 0 };
	Player deadBoardCopy;

public:
	//+-------------------------------C'tors & D'tor---------------------------------------+

	//+----------------------------Set/Get functions---------------------------------------+
	void setGraveyard(int row, int coloum) {
		Graveyard[row][coloum] = 1;
	}

	//+--------------------------Actions tetris functions----------------------------------+
	short int findEmptyColoumn();

	void updateGraveyard(short int emptyColoumn);

	void moveTetris(short int emptyColoumn);

	void flushGraveyard();

	void printGraveyard() { // ---temp function
		ofstream myfile;
		myfile.open("Graveyard.txt");
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				myfile << Graveyard[i][j];
			}
			myfile << endl;
		}
		myfile.close();
	}

	void reDrawTetris();

	bool isFullColoumn(int coloumn);

	void deleteColoum(int coloumn);

	void clear5Back(int xCor);

	bool playTetris(const Player& justDied) {
		deadBoardCopy = justDied; // first of all I take a copy
		int xCor = deadBoardCopy.getX();

		short int emptyColoumn = findEmptyColoumn();

		moveTetris(emptyColoumn);// move the tetris block

		updateGraveyard(emptyColoumn); // update the graveyard

		bool fullColoumn = isFullColoumn(emptyColoumn);

		if (fullColoumn)
		{
			deleteColoum(emptyColoumn);
			clear5Back(xCor);
			//printGraveyard();
			return TRUE;
		}
		return FALSE;
	}

	bool checkGraveyard(const Ball& ball) {
		//Check Left
		if (Graveyard[ball.getLeftEdgeY()][ball.getLeftEdgeX() - 1] || Graveyard[ball.getLeftEdgeY() - 1][ball.getLeftEdgeX()] || Graveyard[ball.getLeftEdgeY() + 1][ball.getLeftEdgeX()])
			return true;
		//Check right
		else if (Graveyard[ball.getRightEdgeY()][ball.getRightEdgeX() + 1] || Graveyard[ball.getRightEdgeY() - 1][ball.getRightEdgeX()] || Graveyard[ball.getRightEdgeY() + 1][ball.getRightEdgeX()])
			return true;
		return false;
	}
};



