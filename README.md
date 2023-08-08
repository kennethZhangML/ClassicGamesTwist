# ClassicGamesTwist
A repo containing reconstructions of classic games using unconventional implementations

1. Pong Game:

The game has a ball and two paddles.
The ball moves in the X and Y directions, bouncing off the top and bottom of the screen.
The ball can be deflected by the paddles, otherwise, the opposing player scores.
The paddles are controlled using the keyboard: w and s for player 1, and i and k for player 2.
The game state, including the positions of the ball and paddles and the scores, is stored in a GameState struct.
The game continuously updates the state, takes input, and draws the current state of the game.

2. Hangman Game:

This is a game in which players guess letters in a word.
The word to guess is selected from a list of animal names.
A maximum number of wrong guesses is allowed.
A visual representation of a hanging man is shown with every wrong guess.
The game keeps track of the words that have been played so that the same word isn't chosen multiple times in a row.
The game has a menu system to start the game or exit.
