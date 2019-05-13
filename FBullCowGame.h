#pragma once
#include <string>
#include <cctype>

// change for Unreal language compatibility
using int32 = int;
using FString = std::string;

// initialize variables to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Ok,
	Pending, // default value
	Not_Isogram,
	Invalid_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	// verify guess validity and gives back appropriate guess status
	EGuessStatus CheckGuessValidity(FString); 
	void Reset(); // gives back game default value
	// recieves a valid guess, increments turn and return bulls and cows count
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	bool IsIsogram(FString) const;
	// returns true if the PlayerGuess has 1 letter in uppercase.
	bool CheckGuessCase(FString) const;
};