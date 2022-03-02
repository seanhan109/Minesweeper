# minesweeper
This project was part of a final assignment for my COMP_SCI 211 class, in which I implemented a basic version of minesweeper.

## project specifications
1. Left clicking a mine will reveal that square, which will either be a mine, a number from 1-8 indicating the number of mines adjacent to it (including corners), or a blank square, indicating that there are no mines adjacent to the square.
2. Right clicking a mine will place a flag on the square at that location.
3. A number will be displayed on the top left side of the screen, which is calculated using the formula (number of mines on the board - number of flags placed by the player). When this number reaches zero, the player will no longer be able to place flags until they remove a flag they have already placed.
4. Mines will be placed at random throughout the board, changing after every reset.
5. Clicking on a square with no adjacent mines reveal all adjacent squares with no adjacent mines, and one extra layer of tiles indicating the number of mines around it.
6. A running timer keeping track of the time it took the player to complete the current run, resetting after each reset.
7. Revealing a mine results in the game stopping, all mines being revealed, and the offending mine and any misplaced flags being highlighted in red.
8. Winning the game (when all squares except mines are revealed) will place flags in all the locations of the mines, and will stop the timer.
9. 4 different size options, of size 10x10 and 10 mines, 14x18 with 40 mines, 16x30 with 99 mines, and a custom board size and mines specified by the user (sizes courtesy of the google minesweeper).
10. There is a "face" button that displays a smiley face emoji when the game is ongoing, a frowny face emoji when the player loses the game, and a smiling face with sunglasses emoji when the player wins the game. Clicking on the face will reset the game.
