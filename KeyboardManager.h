#pragma once

#include <list>
#include "KeyboardEventListener.h"


class KeyboardManager {
	enum { NUM_CHARS = 26 };
	std::list<KeyboardEventListener*> kbListeners[NUM_CHARS];

	int getIndex(char c) {
		int index = c - 'a';
		if (index < 0 || index >= NUM_CHARS) {
			index = c - 'A';
			if (index < 0 || index >= NUM_CHARS) {
				return -1;
			}
		}
		return index;
	}

public:
	void registerKbListener(KeyboardEventListener* pKbListener);
	void handleKeyboard();
};