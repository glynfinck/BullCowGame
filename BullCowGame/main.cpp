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
FText get_guess();
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

	// Loop for the number of turns asking for guesses
	// TODO change from for to while loop once we are validating tries
	for (int32 i = 0; i < max_tries; i++)
	{
		FText guess = get_guess(); // TODO make loop check for valid
		
		// Submit valid guess to the game, and receive counts
		fbull_cow_count bull_cow_count = bc_game.submit_guess(guess);
		// Print number of bulls and cows
		std::cout << "Bulls = " << bull_cow_count.bulls;
		std::cout << ". Cows = " << bull_cow_count.cows << std::endl;
	}
	// TODO add a game summary
}

FText get_guess() 
{
	std::cout << std::endl << "Try " << bc_game.get_current_try();
	std::cout << ". Enter your guess here: ";
	FText guess = "";
	std::getline (std::cin, guess);
	return guess;
}

bool ask_to_play_again()
{
	std::cout << std::endl << "Do you want to play again (y/n)? ";
	FText response = "";
	std::getline (std::cin, response);
	std::cout << std::endl;
	return (response[0] == 'y') || (response[0] == 'Y');
}