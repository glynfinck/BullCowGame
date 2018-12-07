# Bull Cow Game
A simple game that runs on a windows console written in C++.

Game Objective:

The user thinks of any isogram word, and gives out the number of letters in the word.

The game responds with the number of Cows & Bulls for each guessed word. As with the digit version, "Cow" means a letter in the wrong position, while "Bull" means a letter in the right position.

Example Game:

If the secret word is HEAT, a guess of COIN would result in:

Guess 1: "COIN" would result in  "0 Bulls, 0 Cows" (all of the guessed letters are wrong)

Guess 2: "EATS" would result in  "0 Bulls, 3 Cows" (since E, A, T are all present, but not in the guessed positions)

Guess 3: "TEAL" would result in  "2 Bulls, 1 Cow" (since E and A are in the right positions, while T is in the wrong position)

.
.
.

The game would continue until the user scores "4 Bulls" for guessing HEAT exactly or if they run out of the
amount of maximum tries (8 tries).
