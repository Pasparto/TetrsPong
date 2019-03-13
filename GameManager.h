#pragma once
#include <iostream>
#include <Windows.h>
#include "UserPlayer.h"
#include "PcPlayer.h"
#include "Tetris.h"
#include "KeyBoardManager.h"
#include "Ball.h" // added

//using namespace std;

class GameManager {
	UserPlayer m_userPlayerLeft, m_userPlayerRight;
	PcPlayer m_pcPlayerLeft, m_pcPlayerRight;
	Player* players[2];
	Tetris m_tetris;
	KeyboardManager m_kbManager;
	Ball m_Ball;
	bool isPlaying = FALSE;
	bool isStared = FALSE;

public:
	GameManager() = default;

	~GameManager() {}
	//+----------------------------Set/Get functions---------------------------------------+
	bool getisPlaying() {
		return isPlaying;
	}

	bool getisStarted() {
		return isStared;
	}

	void setUserPlayers(UserPlayer& user, const Point& down, const Point& up, const char* kbChar) {
		user.setDown(down.getX(), down.getY(), down.getchar()); // Set down
		user.setUp(up.getX(), up.getY(), up.getchar()); //Set Up
		user.setKbChars(kbChar);// Set Keys
	}

	//+------------------------------MENU-------------------------------------------------+
	void printMenu(const bool isStared) // maybe can be static?
	{
		setColor(COLOR::TEAL_TEXT);
		if (isStared)
		{
			cout << "(1) Start a new game - Human vs Human\n" <<
				"(2) Start a new game - Human vs Computer\n" <<
				"(3) Start a new game - Computer vs Computer\n" <<
				"(4) Continue a paused game\n" <<
				"(8) Present instructions and keys\n" <<
				"(9) EXIT" << endl;
		}
		else
		{
			cout << "(1) Start a new game - Human vs Human\n" <<
				"(2) Start a new game - Human vs Computer\n" <<
				"(3) Start a new game - Computer vs Computer\n" <<
				"(8) Present instructions and keys\n" <<
				"(9) EXIT" << endl;
		}
	}

	char printSubMenu() {
		char level;
		cout << "Please Enter Lever for the Computer:" << endl
			<< "(a) BEST (b) GOOD and (C) NOVICE" << endl;
		cin >> level;
		level = tolower(level);
		if (level == 'a' || level == 'b' || level == 'c')
			return level;
		else
			printSubMenu();
	}

	void menuActions(const char input);

	PcPlayer::Levels subMenuActions();
	//+-----------------------------Game-------------------------------------------------+
	void printField();

	void resumeGame();

	void newGame_hxh();

	void newGame_cxc(PcPlayer::Levels level);

	void newGame_hxc(PcPlayer::Levels level);

	void run();

	bool isLoooser() {
		if (players[0]->getX() == 19 || players[1]->getX() == 60)
			return TRUE;
		else
		{
			return FALSE;
		}
	}

	void printLoooserMessage() {
		system("cls");
		if (players[0]->getX() == 19) {
			cout << "Left Player is the" << endl;
		}
		else
			cout << "Right Player is the" << endl;
		std::vector<std::string> v;

		v.push_back("@       @@@    @@@@   @@@@   @@@@  ");
		v.push_back("@      @   @   @      @      @   @ ");
		v.push_back("@      @   @   @@@@   @@@@   @@@@  ");
		v.push_back("@      @   @      @   @      @   @ ");
		v.push_back("@@@@@@  @@@    @@@@   @@@@   @    @");


		for (auto row : v)
		{
			for (auto col : row)
				cout << col;
			cout << endl;
		}
		Sleep(1500);
	}

	void move5Back(Player& player);

	void checkEdge();
};

