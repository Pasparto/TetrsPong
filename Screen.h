#pragma once
#include <Windows.h>
#include "Point.h"

class Screen {
public:
	enum { MAX_X = 79, MAX_Y = 24 };
	enum { MIN_X = 1, MIN_Y = 4 };
	enum { LEFT_DEAD = 19, RIGHT_DEAD = 60 };
	enum class COLOR // A class to handle coloring the ouput. From the internet.
	{
		// Text foreground colors
		// Standard text colors
		GRAY_TEXT = 8, BLUE_TEXT, GREEN_TEXT,
		TEAL_TEXT, RED_TEXT, PINK_TEXT,
		YELLOW_TEXT, WHITE_TEXT,
		// Faded text colors
		BLACK_TEXT = 0, BLUE_FADE_TEXT, GREEN_FADE_TEXT,
		TEAL_FADE_TEXT, RED_FADE_TEXT, PINK_FADE_TEXT,
		YELLOW_FADE_TEXT, WHITE_FADE_TEXT,
		// Standard text background color
		GRAY_BACKGROUND = GRAY_TEXT << 4, BLUE_BACKGROUND = BLUE_TEXT << 4,
		GREEN_BACKGROUND = GREEN_TEXT << 4, TEAL_BACKGROUND = TEAL_TEXT << 4,
		RED_BACKGROUND = RED_TEXT << 4, PINK_BACKGROUND = PINK_TEXT << 4,
		YELLOW_BACKGROUND = YELLOW_TEXT << 4, WHITE_BACKGROUND = WHITE_TEXT << 4,
		// Faded text background color
		BLACK_BACKGROUND = BLACK_TEXT << 4, BLUE_FADE_BACKGROUND = BLUE_FADE_TEXT << 4,
		GREEN_FADE_BACKGROUND = GREEN_FADE_TEXT << 4, TEAL_FADE_BACKGROUND = TEAL_FADE_TEXT << 4,
		RED_FADE_BACKGROUND = RED_FADE_TEXT << 4, PINK_FADE_BACKGROUND = PINK_FADE_TEXT << 4,
		YELLOW_FADE_BACKGROUND = YELLOW_FADE_TEXT << 4, WHITE_FADE_BACKGROUND = WHITE_FADE_TEXT << 4
	};

	static bool isOn_Y_Edge(const Point& p) {
		return p.y <= MIN_Y || p.y >= MAX_Y;
	}
	static bool isOn_X_Edge(const Point& p) {
		return p.x <= MIN_X || p.x >= MAX_X;
	}
	static bool isOn_Y_Edge(const Point& p, int dirY) {
		return  (p.getY() - 1 <= MIN_Y && dirY == -1) || (p.getY() + 1 == MAX_Y && dirY == 1);
	}

	// Outside functions
	void setColor(COLOR color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		// pick the colorattribute
		SetConsoleTextAttribute(hConsole, (int)color);
	}
};
