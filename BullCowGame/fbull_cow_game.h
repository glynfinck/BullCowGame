#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All values initialized to zero
struct fbull_cow_count 
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus 
{
	Invalid,
	Ok,
	Not_Isogram,
	Not_Lowercase,
	Invalid_Length,
};


class fbull_cow_game
{
public:
	fbull_cow_game(); // Constructor
	
	int32 get_max_tries() const;
	int32 get_current_try() const;
	int32 get_hidden_word_length() const;
	bool is_game_won() const;
	
	EGuessStatus check_guess_validity(FString) const;
	
	void reset(); // TODO make a more rich return value

	// Counts bulls & cows, and increases try number (assumes valid guess)
	fbull_cow_count submit_valid_guess(FString); 
	

// Please try and ignore this and focus on the interface above
private:
	// See constructor for initialization
	int32 my_current_try;
	int32 my_max_tries;
	bool bgame_won;
	FString my_hidden_word;

	bool is_isogram(FString) const;
	bool is_lowercase(FString) const;
};