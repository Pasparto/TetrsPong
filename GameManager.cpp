#include "GameManager.h"

void GameManager::menuActions(const char input)
{
	PcPlayer::Levels level;
	switch (input)
	{
	case '1':
		GameManager::newGame_hxh();
		break;
	case '2':
		level = subMenuActions();
		GameManager::newGame_hxc(level);
		break;
	case '3':
		level = subMenuActions();
		GameManager::newGame_cxc(level);
		break;
	case '4':
		if (isStared)
			GameManager::resumeGame();
		else
		{
			cout << "No Game Began!" << endl;
		}
		break;
	case '8':
		cout << "For the left player: q/Q - UP\ta/A - DOWN\nFor the right player: p/P - UP\tl/L - DOWN\n" << endl;
		break;
	case '9':
		break;
	default:
		cout << "You were bad boy\nPlease Try Another Option.\n";
		break;
	}
}

PcPlayer::Levels GameManager::subMenuActions() {
	char level = printSubMenu();
	switch (level)
	{
	case 'a':
		return PcPlayer::Levels::BEST;
	case 'b':
		return PcPlayer::Levels::GOOD;
	case 'c':
		return PcPlayer::Levels::NOVICE;
	default:
		break;
	}
}

void GameManager::printField()
{
	cout << endl << endl << endl;
	for (int i = 0; i < 80; i++)
		cout << '@';
	cout << endl;
	for (int i = 0; i <= 20; i++)
	{
		cout << endl;
	}
	for (int i = 0; i < 80; i++)
		cout << '@';
	cout << endl;
}

void GameManager::checkEdge() {
	if (Screen::isOn_Y_Edge(m_Ball.getTopP()) || Screen::isOn_Y_Edge(m_Ball.getButtomP())) {
		m_Ball.changeYDirection();
	}
}

void GameManager::move5Back(Player& player) {
	if (player.getSide() == UserPlayer::Sides::LEFT)
	{
		player.eraseBoard();
		player.setDown(player.getX() - 5, player.getDownY());
		player.setUp(player.getX() - 5, player.getUpY());
		player.drawBoard();
	}
	else
	{
		player.eraseBoard();
		player.setDown(player.getX() + 5, player.getDownY());
		player.setUp(player.getX() + 5, player.getUpY());
		player.drawBoard();
	}
	//printField();
}

void GameManager::newGame_hxh() {
	setUserPlayers(m_userPlayerLeft, { 4,10,'#' }, { 4,12,'#' }, "qas");
	setUserPlayers(m_userPlayerRight, { 76,11,'#' }, { 76,13,'#' }, "plk");// construct 2 boards
	players[0] = &m_userPlayerLeft;
	players[1] = &m_userPlayerRight;
	m_kbManager.registerKbListener(&m_userPlayerLeft); // register the board
	m_kbManager.registerKbListener(&m_userPlayerRight); // register the board
	m_tetris.flushGraveyard();
	//clean screen
	system("cls");
	printField();
	run();
}

void GameManager::newGame_cxc(PcPlayer::Levels level) {
	m_pcPlayerLeft = { { 4,10,'#' },{ 4,12,'#' } };
	m_pcPlayerRight = { { 76,11,'#' },{ 76,13,'#' } };
	m_pcPlayerLeft.setLevel(level);
	m_pcPlayerRight.setLevel(level);
	players[0] = &m_pcPlayerLeft;
	players[1] = &m_pcPlayerRight;
	m_tetris.flushGraveyard();
	//clean screen
	system("cls");
	printField();
	run();
}

void GameManager::newGame_hxc(PcPlayer::Levels level) {
	setUserPlayers(m_userPlayerLeft, { 4,10,'#' }, { 4,12,'#' }, "qas");
	m_kbManager.registerKbListener(&m_userPlayerLeft); // register the board
	m_pcPlayerRight = { { 76,11,'#' },{ 76,13,'#' } };
	m_pcPlayerRight.setLevel(level);
	players[0] = &m_userPlayerLeft;
	players[1] = &m_pcPlayerRight;
	m_tetris.flushGraveyard();
	//clean screen
	system("cls");
	printField();
	run();
}

void GameManager::resumeGame() {
	//clean screen
	system("cls");
	printField();
	m_tetris.reDrawTetris();
	run();
}

void GameManager::run()
{
	//set flags
	isPlaying = TRUE;
	isStared = TRUE;
	bool isFull;

	//draw boards
	players[0]->drawBoard();
	players[1]->drawBoard();

	//states  variables for the boards
	UserPlayer::BallPosition stateLeft, stateRight;

	while (isPlaying)
	{
		m_kbManager.handleKeyboard();
		checkEdge();
		players[0]->move(m_Ball); // Move Left Player
		players[1]->move(m_Ball); // Move Right Player
		stateLeft = players[0]->checkBallPosition(m_Ball); // Check Left Player Position
		stateRight = players[1]->checkBallPosition(m_Ball);// Check Right Player Position

		//+--------------------------------------------------------------Left Board------------------------------------------------------------+		
		switch (stateLeft) {
		case UserPlayer::BallPosition::AWAY:
			checkEdge();
			//BECOMING and BOMB - Check if Away and Start Counting
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BecomingState) || typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				if (stateRight == UserPlayer::BallPosition::AWAY)
				{
					m_Ball.Away();
				}
			}
			break;


		case UserPlayer::BallPosition::MISSED:
			//NORMAL - Check if missed the board
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::NormalState))
			{
				isFull = m_tetris.playTetris(*players[0]);
				if (isFull)
					move5Back(*players[0]);
				players[0]->reposition(1);
			}
			//BECOMING - Check if hit dead board or edge
			else if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BecomingState)) {
				checkEdge();
				if (m_Ball.getLeftEdgeX() == 0 || m_tetris.checkGraveyard(m_Ball))
				{
					m_Ball.restart();
					isFull = m_tetris.playTetris(*players[0]);
					if (isFull)
						move5Back(*players[0]);
					players[0]->reposition(1);
					m_Ball.setState(Ball::NORMAL);
				}
			}
			//BOMB - Check if hit dead board or edge
			else if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				checkEdge();
				if (m_Ball.getLeftEdgeX() == 0 || m_tetris.checkGraveyard(m_Ball))
				{
					(m_Ball.getLeftEdgeX() == 0) ? m_tetris.deleteColoum(m_Ball.getLeftEdgeX()) : m_tetris.deleteColoum(m_Ball.getLeftEdgeX() - 1);
					m_Ball.restart();
					m_Ball.changeXDirection();
					m_Ball.setState(Ball::NORMAL);
				}
			}
			m_Ball.Missed();
			if (isLoooser())
			{
				printLoooserMessage();
				isPlaying = false;
			}
			break;
			break;


		case UserPlayer::BallPosition::CORNER_HIT:
			//BOMB - Check if hit the board
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				isFull = m_tetris.playTetris(*players[0]);
				if (isFull)
					move5Back(*players[0]);
				players[0]->reposition(3);
			}
			m_Ball.Corner();
			checkEdge();
			//m_Ball.bounce(players[0]->getDownY(), players[0]->getX(), (int)players[0]->getSide()); // Bounse Effect
			break;


		case UserPlayer::BallPosition::CENTER_HIT:
			//BOMB - Check if hit the board
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				isFull = m_tetris.playTetris(*players[0]);
				if (isFull)
					move5Back(*players[0]);
				players[0]->reposition(3);
			}
			m_Ball.Center();
			checkEdge();
			//m_Ball.bounce(players[0]->getDownY(), players[0]->getX(), (int)players[0]->getSide()); // Bounse Effect
			break;
		}


		//+--------------------------------------------------------------Right Board------------------------------------------------------------+	
		switch (stateRight) {
		case UserPlayer::BallPosition::AWAY:
			checkEdge();
			//BECOMING and BOMB - Check if Away and Start Counting
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BecomingState) || typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				if (stateLeft == UserPlayer::BallPosition::AWAY)
				{
					m_Ball.Away();
				}
			}
			break;


		case UserPlayer::BallPosition::MISSED:
			//NORMAL - Check if missed the board
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::NormalState))
			{
				isFull = m_tetris.playTetris(*players[1]);
				if (isFull)
					move5Back(*players[1]);
				players[1]->reposition(1);
			}
			//BECOMING - Check if hit dead board or edge
			else if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BecomingState)) {
				checkEdge();
				if (m_Ball.getRightEdgeX() == 79 || m_tetris.checkGraveyard(m_Ball))
				{
					m_Ball.restart();
					isFull = m_tetris.playTetris(*players[1]);
					if (isFull)
						move5Back(*players[1]);
					players[1]->reposition(1);
					m_Ball.setState(Ball::NORMAL);
				}
			}
			//BOMB - Check if hit dead board or edge
			else if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				checkEdge();
				if (m_Ball.getRightEdgeX() == 79 || m_tetris.checkGraveyard(m_Ball))
				{
					(m_Ball.getRightEdgeX() == 79) ? m_tetris.deleteColoum(m_Ball.getRightEdgeX()) : m_tetris.deleteColoum(m_Ball.getRightEdgeX() + 1);
					m_Ball.restart();
					m_Ball.changeXDirection();
					m_Ball.setState(Ball::NORMAL);
				}
			}
			m_Ball.Missed();
			if (isLoooser())
			{
				printLoooserMessage();
				isPlaying = false;
			}
			break;


		case UserPlayer::BallPosition::CORNER_HIT:
			//BOMB - Check if hit the board
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				isFull = m_tetris.playTetris(*players[1]);
				if (isFull)
					move5Back(*players[1]);
				players[1]->reposition(3);
			}
			m_Ball.Corner();
			checkEdge();
			//m_Ball.bounce(players[1]->getDownY(), players[1]->getX(), (int)players[1]->getSide()); // Bounse Effect
			break;


		case UserPlayer::BallPosition::CENTER_HIT:
			//BOMB - Check if hit the board
			if (typeid(*(m_Ball.getcurState())) == typeid(Ball::BombState)) {
				isFull = m_tetris.playTetris(*players[1]);
				if (isFull)
					move5Back(*players[1]);
				players[1]->reposition(3);
			}
			m_Ball.Center();
			checkEdge();
			//m_Ball.bounce(players[1]->getDownY(), players[1]->getX(), (int)players[1]->getSide()); // Bounse Effect
			break;
		}

		// Here I check if pass the x=40 line
		if (m_Ball.getLeftEdgeX() == 40)
		{
			m_Ball.incpass40();
			if (m_Ball.getpass40() >= 4)
				m_Ball.setbombflag(1);
		}

		m_Ball.move();
		players[0]->drawBoard();
		players[1]->drawBoard();
		Sleep(80);

		// if the user press ESC
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			system("cls");
			isPlaying = false;
		}
	}
	system("cls");
}


