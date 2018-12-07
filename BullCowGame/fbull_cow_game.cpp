#include "fbull_cow_game.h"

// Using statements
using FString = std::string;
using int32 = int;

// Initializes the game
fbull_cow_game::fbull_cow_game() { reset(); }

// Getter methods
int32 fbull_cow_game::get_max_tries() const { return my_max_tries; }
int32 fbull_cow_game::get_current_try() const { return my_current_try; }
int32 fbull_cow_game::get_hidden_word_length() const { return my_hidden_word.length(); }

// Resets the game
void fbull_cow_game::reset()
{
	constexpr int32 MAX_TRIES = 8;
	my_max_tries = MAX_TRIES;

	const FString HIDDEN_WORD = "plane";
	my_hidden_word = HIDDEN_WORD;

	my_current_try = 1;
	return;
}

// Returns the status of the game (False = Not Won, True = Won)
bool fbull_cow_game::is_game_won() const
{
	return false;
}



// Checks if the guessed word is the same as the hidden word.
// Returns: True if guess = hidden word
//			False if guess != hidden word
EGuessStatus fbull_cow_game::check_guess_validity(FString) const
{
	// if the guess isn't an isogram
	if (false)
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (false) // if the lenght is wrong
	{
		return EGuessStatus::Invalid_Length;
	}
	else // otherwise
	{
		EGuessStatus::Ok;
	}
}




// Receives a VALID guess, increments turn, and returns count
fbull_cow_count fbull_cow_game::submit_guess(FString guess)
{
	// Increment the turn number
	my_current_try++;
	// Setup a return variable
	fbull_cow_count bull_cow_count;

	// Loop through all letters in the guess
	int32 hidden_word_length = my_hidden_word.length();
	for (int32 mhw_char = 0; mhw_char < hidden_word_length; mhw_char++)
	{
		// Compare letters against the hidden word
		for (int32 j = 0; j < hidden_word_length; j++)
		{
			// If they match 
			if (my_hidden_word[mhw_char] == guess[j]) 
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

	return bull_cow_count;
}
