/*This is the console executable, that makes use of the bull_cow class
This actas as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the fbull_cow_game class.


*/

#include <iostream>
#include <string>
#include "fbull_cow_game.h"

using FText = std::string;
using int32 = int32;

void print_intro();
void play_game();
FText get_valid_guess();
void print_game_summary();
bool ask_to_play_again();

fbull_cow_game bc_game; // Instantiate a new game

// The entry point for the application.
int main() 
{
	do {
		print_intro();
		play_game();
	} 
	while (ask_to_play_again());

	return 0; // Exit the application
}

void print_intro()
{
	// Print the introduction text for the game.
	std::cout << "Welcome to Bulls & Cows!" << std::endl;
	std::cout << "Can you guess the " << bc_game.get_hidden_word_length();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	return;
}

void play_game()
{
	bc_game.reset();
	int32 max_tries = bc_game.get_max_tries();

	// Loop asking for guesses while game
	// is NOT won and there are still tries remaining
	while (!bc_game.is_game_won() && bc_game.get_current_try() <= max_tries) // TODO change from FOR to WHILE loop
	{
		FText guess = get_valid_guess();
		
		// Submit valid guess to the game, and receive counts
		fbull_cow_count bull_cow_count = bc_game.submit_valid_guess(guess);

		// Print number of bulls and cows
		std::cout << "Bulls = " << bull_cow_count.bulls;
		std::cout << ". Cows = " << bull_cow_count.cows << std::endl;
	}
	print_game_summary();
	// TODO add a game summary
}

// Loop continually unitl the user enters a valid guess
FText get_valid_guess() 
{
	FText guess = "";
	EGuessStatus status = EGuessStatus::Invalid;
	do {
		// Get a guess from the player
		std::cout << std::endl << "Try " << bc_game.get_current_try();
		std::cout << ". Enter your guess here: ";
		std::getline(std::cin, guess);

		// Check guess status and give feedback
		status = bc_game.check_guess_validity(guess);
		switch (status)
		{
		case EGuessStatus::Invalid_Length:
			std::cout << "Please enter a " << bc_game.get_hidden_word_length() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word in all lowercase characters." << std::endl;
			break;
		case EGuessStatus::Ok:
		default:
			// Assume the guess is valid
			break;
		}
	} while (status != EGuessStatus::Ok); // Keep looping until we receive a valid guess
	return guess;
}

bool ask_to_play_again()
{
	std::cout << std::endl << "Do you want to play again with the hidden word (y/n)? ";
	FText response = "";
	std::getline (std::cin, response);
	std::cout << std::endl;
	return (response[0] == 'y') || (response[0] == 'Y');
}

void print_game_summary() {
	if (bc_game.is_game_won())
	{
		std::cout << "\nCongratulations... You Won!";
	}
	else 
	{
		std::cout << "\nBetter luck next time...";
	}
	return;
}