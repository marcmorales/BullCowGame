#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString PlayerGuess)
{
	if (PlayerGuess.length() != GetHiddenWordLength()) // if the guess length is not equal to the hidden word length
		return EGuessStatus::Invalid_Length;

	else if (CheckGuessCase(PlayerGuess)) // if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase;

	else if (!IsIsogram(PlayerGuess)) // if the guess isn't an isogram, 
		return EGuessStatus::Not_Isogram;

	else // otherwise
		return EGuessStatus::Ok;// return Ok
}

// returns true if the PlayerGuess has 1 letter in uppercase.
bool FBullCowGame::CheckGuessCase(FString PlayerGuess) const
{
	for (char c : PlayerGuess)
	{
		if (isupper(c))
		{
			return true;
		}
	}
	return false;
}

bool FBullCowGame::IsIsogram(FString PlayerGuess) const
{
	TMap<char, bool> LetterSeen; // setup our map

	// loop through all the letters of the word
	for (auto Letter : PlayerGuess)
	{
		Letter = tolower(Letter); // change uppercase to lowercase char

		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // we do NOT have an Isogram
		}
		else
		{
			LetterSeen[Letter] = true;// add the letter to the map as seen
		}
			
	}
	return true;
}

void FBullCowGame::Reset()
{
	int32 constexpr MAX_TRIES = 8;
	FString const HIDDEN_WORD = "planets";

	bGameWon = false;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	
	return;
}

// recieves a valid guess, increments turn and return count
FBullCowCount FBullCowGame::SubmitGuess(FString PlayerGuess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 PlayerGuessLength = PlayerGuess.length();

	for (int32 i = 0; i < GetHiddenWordLength(); i++) // loop through all letters in the hidden word
	{
		// compare letters against the hidden word
		for (int32 j = 0; j < PlayerGuessLength; j++) 
		{
			// if they match then
			if (MyHiddenWord[i] == PlayerGuess[j])
			{
				// increment bulls if they're in the same place
				if (i == j) BullCowCount.Bulls++;
				// increment cows if not
				else BullCowCount.Cows++;
			}	
		}
	}

	// verify that the game is won or not. Default game status is false
	if (BullCowCount.Bulls == GetHiddenWordLength()) bGameWon = true;

	return BullCowCount;
}
