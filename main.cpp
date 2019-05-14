#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// change for Unreal language compatibility
using int32 = int;
using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetGuess(FText Guess);
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // create game object

int main()
{
	PrintIntro();
	do
	{
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // exit application
}

// introduce game title and the length of the word which the player will guess
void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "((...))          _(_~_)_\n";
	std::cout << "( o o )   BULLS   |o o|\n";
	std::cout << " \\   /      &     (@_@)\n";
	std::cout << "  ^_^      COWS    ) ( \n";
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the (" << BCGame.GetHiddenWordLength() << ") letter ISOGRAM word I'm thinking of?" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset(); // set game status to its default values
	FText Guess = "";

	// keep looping until player won OR max tries were exhausted
	while (BCGame.IsGameWon() == false && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) 
	{
		FText PlayerGuess = GetGuess(Guess);
		std::cout << "Your guess is: " << PlayerGuess << std::endl;
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(PlayerGuess);

		// print number of bulls and cows
		std::cout << "Bulls: " << BullCowCount.Bulls << ".";
		std::cout << " Cows: " << BullCowCount.Cows << "." << std::endl;
	}

	PrintGameSummary();
	return;
}

// will ask player to enter a valid guess. This will loop indefinitely until user enter a valid guess
FText GetGuess(FText Guess)
{
	EGuessStatus Status = EGuessStatus::Pending;
	do
	{
		// take guess from player
		std::cout << std::endl;
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

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
	} while (Status != EGuessStatus::Ok); // keep looping until we get a valid guess.

	return (Guess);
}

// summarize game to the player if they win or not
void PrintGameSummary()
{
	if (BCGame.GetCurrentTry() >= BCGame.GetMaxTries() && BCGame.IsGameWon() == false)
	{
		std::cout << std::endl << "You've exhausted all your attempts, better luck next time!" << std::endl;
	}
	else if (BCGame.IsGameWon() == true)
	{
		std::cout << std::endl << "Congratulations!, your guess is correct!" << std::endl;
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
