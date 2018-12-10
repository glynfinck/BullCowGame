/*  This is the Bull Cow Game class and contains various public and private functions
    and variables. The game logic is as follows:

    The user thinks of any isogram word, and gives out the number of letters in the word.
	The game responds with the number of Cows & Bulls for each guessed word. As with the 
	digit version, "Cow" means a letter in the wrong position, while "Bull" means a letter
	in the right position.
*/

#include "fbull_cow_game.h"
#include <map>
#define TMap std::map

// Using statements
using FString = std::string;
using int32 = int;

// Initializes the game and initializes hidden word to one of length 3 by default
// Also prints intro to the game
fbull_cow_game::fbull_cow_game() 
{ 
	HIDDEN_WORD3 = "eat";
	HIDDEN_WORD4 = "four";
	HIDDEN_WORD5 = "lying";
	HIDDEN_WORD6 = "planet";
	HIDDEN_WORD7 = "tabloid";

	print_game_intro();

	my_hidden_word = HIDDEN_WORD3;
	bgame_won = false;
	my_current_try = 1;
}

// Prints intro to the game
void fbull_cow_game::print_game_intro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the isogram I'm thinking of?\n";
	std::cout << "(Hint: an isogram is a word with no repeating letters)\n\n";
	return;
}

// Getter methods
int32 fbull_cow_game::get_current_try() const { return my_current_try; }
int32 fbull_cow_game::get_hidden_word_length() const { return my_hidden_word.length(); }
bool fbull_cow_game::is_game_won() const { return bgame_won; }

int32 fbull_cow_game::get_max_tries() const 
{ 
	TMap<int32, int32> word_lenght_to_max_tries{ {3,4} , {4,7} , {5,10} , {6,16} , {7,20} };
	return word_lenght_to_max_tries[my_hidden_word.length()];
}

// Resets the game and initializes hidden word to one of length 3 by default
void fbull_cow_game::reset()
{
	// Gets the a chosen word length from the user
	CHOSEN_WORD_LENGTH = get_valid_word_length();

	// Converts the inputted string for chosen word length into an integer
	int w_length = std::stoi(CHOSEN_WORD_LENGTH);

	// Assigns my_hidden_word based on the chosen word length
	// Assumes that the word length inputted from above is between 3 and 7
	if (w_length == 7) {
		my_hidden_word = HIDDEN_WORD7;
	}
	else if (w_length == 6) {
		my_hidden_word = HIDDEN_WORD6;
	}
	else if (w_length == 5) {
		my_hidden_word = HIDDEN_WORD5;
	}
	else if (w_length == 4) {
		my_hidden_word = HIDDEN_WORD4;
	}
	else if (w_length == 3) {
		my_hidden_word = HIDDEN_WORD3;
	}

	// Resets win status and current try
	bgame_won = false;
	my_current_try = 1;
	return;
}


// Checks if the guessed word is the same as the hidden word.
// Returns: True if guess = hidden word
//			False if guess != hidden word
EGuessStatus fbull_cow_game::check_guess_validity(FString guess) const
{
	
	if (!is_isogram(guess)) // If the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!is_lowercase(guess)) // If the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (guess.length() != get_hidden_word_length()) // If the length is wrong
	{
		return EGuessStatus::Invalid_Length;
	}
	else // otherwise
	{
		return EGuessStatus::Ok;
	}
}


// Prompts user for a word length, and then checks if the inputted word lenght is valid.
// Loops until the user inputs a valid word length
FString fbull_cow_game::get_valid_word_length() const
{
	FString length_choice = "";
	EWordLengthStatus status = EWordLengthStatus::Invalid;
	do {
		// Get a word length choice from the user
		std::cout << std::endl << "Choose a valid word length between 3 and 7 (no spaces): ";
		std::getline(std::cin, length_choice);

		status = check_word_length_validity(length_choice);
		// Check the inputted word length and give feedback
		switch (status)
		{
		case EWordLengthStatus::Not_A_Valid_Number:
			break;
		case EWordLengthStatus::Not_Within_Range:
			break;
		case EWordLengthStatus::Ok:
		default:
			// Assume the word length is valid
			break;
		}
	} while (status != EWordLengthStatus::Ok); // Keep looping until a valid guess is received
	return length_choice;
}

// Returns the EWordLengthStatus of an inputted word to check its validity
EWordLengthStatus fbull_cow_game::check_word_length_validity(FString word_length) const 
{
	if (!is_string_number(word_length)) // If the word length is not an integer
	{
		return EWordLengthStatus::Not_A_Valid_Number;// Then the word length is not valid
	}
	else if (!is_string_number_within_range(word_length)) // If the word length is not between 3 and 7
	{
		return EWordLengthStatus::Not_Within_Range; // Then the word length is not valid
	}
	else {
		return EWordLengthStatus::Ok; // The word length is ok
	}		
}

// Receives a VALID guess, increments turn, and returns count
fbull_cow_count fbull_cow_game::submit_valid_guess(FString guess)
{
	my_current_try++;
	fbull_cow_count bull_cow_count;
	int32 word_length = my_hidden_word.length(); // Assuming same length as guess

	// Loop through all letters in the guess
	for (int32 mhw_char = 0; mhw_char < word_length; mhw_char++)
	{
		// Compare letters against the hidden word
		for (int32 j = 0; j < word_length; j++)
		{
			// If they match 
			if (guess[j] == my_hidden_word[mhw_char])
			{
				if (j == mhw_char) // If there in the same place
				{
					bull_cow_count.bulls++; // Increment bulls
				}
				else 
				{
					bull_cow_count.cows++; // Must be a cow
				}
					
			}
		}
	}
	if (bull_cow_count.bulls == word_length) 
	{
		bgame_won = true;
	}
	else 
	{
		bgame_won = false;
	}
	return bull_cow_count;
}

// Returns true if the inputted word is an isogram
bool fbull_cow_game::is_isogram(FString word) const
{
	if (word.length() <= 1) { return true; }

	// setup map
	TMap <char, bool> seen_letters;

	// Loop from through each character in the word
	for (auto letter : word)
	{
		letter = tolower(letter);

		if (seen_letters[letter]) { 
			return false; 
		} else {
			seen_letters[letter] = true;
		}
	}
	return true;
}

// Returns true if the inputted string is comprised of all lowercase characters
bool fbull_cow_game::is_lowercase(FString word) const
{
	if (word.length() < 1) { return true; }
	
	// Loop through each character in the word
	for (auto letter : word) 
	{
		if (!islower(letter)) // if the lowercase of the letter is not equal to the letter
		{
			return false; // then the word does not contain all lowercase letters
		}
		// otherwise, continue looping
	} 
	// the word contains all lowercase letters
	return true;
}

// Returns true if the string coming is only comprised of digits 
// (i.e. "34" or "1" would return true, "abc" or "1one" would return false)
bool fbull_cow_game::is_string_number(FString word) const 
{
	for (int i = 0; i < word.length(); i++) // Loop through each character in the word
	{
		if (!isdigit(word[i])) // If the character is not a digit
		{
			return false;
		}
	}
	return true;
}

// Assumes the input stirng is of length 1 and contains a digit between 0 and 9
bool fbull_cow_game::is_string_number_within_range(FString word) const 
{
	// Converts the FString into an integer
	int length = std::stoi(word);
	if (length <= 7 && length >= 3) { return true; }
	return false;
}
