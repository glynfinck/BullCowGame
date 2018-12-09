#pragma once
#include <string>
#include <iostream>

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

enum class EWordLengthStatus 
{
	Invalid,
	Ok,
	Not_A_Valid_Number,
	Not_Within_Range
};


class fbull_cow_game
{
public:
	fbull_cow_game(); // Constructor

	void print_game_intro();
	
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
	bool bgame_won;
	FString CHOSEN_WORD_LENGTH;
	FString my_hidden_word;
	FString HIDDEN_WORD3;
	FString HIDDEN_WORD4;
	FString HIDDEN_WORD5;
	FString HIDDEN_WORD6;
	FString HIDDEN_WORD7;

	// Checks if submitted word length choice is valid
	FString get_valid_word_length() const;
	EWordLengthStatus check_word_length_validity(FString) const;


	bool is_isogram(FString) const;
	bool is_lowercase(FString) const;
	bool is_string_number(FString) const;
	bool is_string_number_within_range(FString) const;
};