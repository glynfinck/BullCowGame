#include "fbull_cow_game.h"
#include <map>
#define TMap std::map

// Using statements
using FString = std::string;
using int32 = int;

// Initializes the game
fbull_cow_game::fbull_cow_game() { reset(); }

// Getter methods
int32 fbull_cow_game::get_current_try() const { return my_current_try; }
int32 fbull_cow_game::get_hidden_word_length() const { return my_hidden_word.length(); }
bool fbull_cow_game::is_game_won() const { return bgame_won; }

int32 fbull_cow_game::get_max_tries() const 
{ 
	TMap<int32, int32> word_lenght_to_max_tries{ {3,4} , {4,7} , {5,10} , {6,16} , {7,20} };
	return word_lenght_to_max_tries[my_hidden_word.length()];
}

// Resets the game
void fbull_cow_game::reset()
{
	const FString HIDDEN_WORD3 = "eat";
	const FString HIDDEN_WORD4 = "four";
	const FString HIDDEN_WORD5 = "lying";
	const FString HIDDEN_WORD6 = "planet";
	const FString HIDDEN_WORD7 = "tabloid";


	const FString HIDDEN_WORD = HIDDEN_WORD3;

	my_hidden_word = HIDDEN_WORD;
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
		return EGuessStatus::Not_Lowercase; // TODO write a function
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