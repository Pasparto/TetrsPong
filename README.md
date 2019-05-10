# Tetris-Pong Game
## *Requirements and Guidelines*
The exercise required to implement a game combining in some way two known games: Pong and Tetris.
It implemented Studio 2017 with standard C++ libraries and run on Windows with Console screen of standard size (80*25).

## *Rules*
Pong game requires the player to move a “Board” using the keyboard, in order to hit a ball
and “return” it to the other player, as in a tennis game.

In our Pong game, once a player misses the ball a “copy” of his board will “drop” as in tetris
game to the “lowest” position on his side of the screen (for the player on the right => board
will go to the right, for the player on the left => board will go to the left) - and the new position
of the board will go “up” by one, making him one step closer to losing.

In case “dropped boards” complete a full line, the entire line would disappear and the board
would gain back five lines (go back five lines) - note: if there are old boards in these lines
they will be deleted.
The player whose board reaches the position of “¼ of screen” as defined below - loses.

*Keys:*
 | Left Player | Right Player
------------ | -------------| -------------
