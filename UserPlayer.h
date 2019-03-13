#pragma once

#include "Player.h"
#include "KeyboardEventListener.h"


// forward declaration
class Ball;

class UserPlayer : public Player, public KeyboardEventListener {
	const char* m_kbChars;
	char curPress = 0;
public:
	//+----------------------------------ENUMS---------------------------------------------+
	enum { kbUp, kbDown, kbBomb };
	//+-------------------------------C'tors & D'tor---------------------------------------+
	UserPlayer() = default;
	UserPlayer(const Point& down, const Point& up, char* kbChars) : Player(down, up), m_kbChars(kbChars) {}
	~UserPlayer() {}
	//+--------------------------Actions board functions-----------------------------------+
	void handleKey(char c);
	void move(Ball& ball);
	//+----------------------------Set/Get functions---------------------------------------+	
	const char* getKbChars() {
		return m_kbChars;
	}
	void setKbChars(const char* KbChars) {
		m_kbChars = KbChars;
	}
};