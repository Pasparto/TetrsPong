#pragma once

#include <iostream>
#include "utils.h"

class Point {
	int x, y;
	char ch;
	friend class Screen;
public:
	Point() = default;
	Point(int x1, int y1, char c) : x(x1), y(y1), ch(c) {}
	void move(int dir_x, int dir_y) {
		x += dir_x;
		y += dir_y;
	}
	void draw() {
		draw(ch);
	}
	void draw(char c) {
		gotoxy(x, y);
		std::cout << c;
	}
	void erase() {
		//setColor(COLOR::BLACK_BACKGROUND); BLACK BALL
		draw(' ');
	}
	void drawBoardsign() {
		draw('#');
	}
	//----------------------------------Get/Set Functions--------------------
	int getX()const { return x; }
	int getY()const { return y; }
	char getchar()const { return ch; }

	void setY(int y) {
		this->y = y;
	}
	void setX(int x) {
		this->x = x;
	}
	void setChar(char c) {
		ch = c;
	}
	//----------------------------------Operators---------------------------
	bool operator!=(const Point& other) const {
		return x != other.x || y != other.y;
	}
};