#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;

// this is called function prototype
void PrintIntro();
void PlayGame();
FText GetGuess(FText Guess);
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	PrintIntro();
	do
	{
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // exit application
}

void PrintIntro()
{
	// introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter ISOGRAM I'm thinking of?" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	FText Guess = "";
	// keep looping until player won OR max tries were exhausted
	while (BCGame.IsGameWon() == false && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) 
	{
		FText PlayerGuess = GetGuess(Guess);
		std::cout << "Your guess is: " << PlayerGuess << std::endl;

		// print number of bulls and cows
		FBullCowCount BullCowCount = BCGame.SubmitGuess(PlayerGuess);
		std::cout << "Bulls: " << BullCowCount.Bulls << ".";
		std::cout << " Cows: " << BullCowCount.Cows << "." << std::endl;
	}

	PrintGameSummary();

	return;
}

FText GetGuess(FText Guess)
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	EGuessStatus Status = EGuessStatus::Pending;
	do
	{
		// get a guess from the player
		std::cout << "Try " << CurrentTry << ", " << "Enter your guess: ";
		std::getline(std::cin, Guess);
		std::cout << std::endl;

		// verify guess validity and update Status with proper return value.
		Status = BCGame.CheckGuessValidity(Guess); 

		switch (Status)
			{
			case EGuessStatus::Invalid_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " digit letter word." << std::endl;
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter your guess in all lowercase." << std::endl;
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter an Isogram word (no repeating letter word)." << std::endl;
				break;
			case EGuessStatus::Pending:
				std::cout << "Pending error. Please verify that you are submitting a proper Isogram word and retry." << std::endl;
				break;
			default:
				// assume the guess is valid
				break;
			}
	} while (Status != EGuessStatus::Ok); // keep looping until we get a valid input.

	return (Guess);
}

// summarize game to the player if they win or not
void PrintGameSummary()
{
	if (BCGame.GetCurrentTry() >= BCGame.GetMaxTries() && BCGame.IsGameWon() == false)
	{
		std::cout << "You've exhausted all your attempts, better luck next time!" << std::endl;
	}
	else if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congratulations!, your guess is correct!" << std::endl;
	}
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (Yes/No): ";
	FText Response = "";
	std::getline(std::cin, Response);
	char ResponseChar = Response[0];

	//check answer if yes/1 or no/0
	if ((ResponseChar == 'Y') || (ResponseChar == 'y')) return true;
	else return false;
}
