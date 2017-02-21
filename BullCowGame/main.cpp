/* Main class for the Bull Cow Game
This is the console executable for the BullCow class
acting as the view in a MVC pattern

author: lucas.subli@gmail.com
for several reasons the Unreal Coding Standard will be used
https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/index.html
 */
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"


// make it closer to UE4 syntax
using FText = std::string;
using int32 = int;


// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// instantiate a new game
FBullCowGame BCGame;

// the entry point for our application
int main() {

	bool bPlayAgain = false;

	PrintIntro();

	do {
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	// exit the application
	return 0;
}

// prints the intro of the game
void PrintIntro() {

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "If you type a right letter in a wrong place yout get a Cow." << std::endl;
	std::cout << "         ___ " << std::endl;
	std::cout << "        (o o) " << std::endl;
	std::cout << "         \\ /-------\\ " << std::endl;
	std::cout << "          O| COW  | \\ " << std::endl;
	std::cout << "           |------|  * " << std::endl;
	std::cout << "           ^      ^ " << std::endl;
	std::cout << "If you type a right letter in the right place yout get a Bull." << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {" << std::endl;
	std::cout << "          (o o)" << std::endl;
	std::cout << "   /-------\\ /" << std::endl;
	std::cout << "  / | BULL |O " << std::endl;
	std::cout << " *  |-,--- |  " << std::endl;
	std::cout << "    ^      ^  " << std::endl;
	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	std::cout << "Tip: An isogram is a word without a repeating letter" << std::endl;
	std::cout << std::endl;

	return;
}

// plays a single game to completion
void PlayGame() {

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for guesses while the game is not won
	// and there are tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game andf get the count back
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls : " << BullCowCount.Bulls;
		std::cout << ". Cows : " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();


	return;
}

// loop until the user gives a valid guess
FText GetValidGuess() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		// get a guess from the user
		int32 RemainingTries = BCGame.GetMaxTries() - BCGame.GetCurrentTry() + 1;
		std::cout << RemainingTries << " tries remaining. Enter your guess: ";
		std::getline(std::cin, Guess);

		// verify the validity of the guess
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " leter word.\n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n\n";
				break;
			default:
				// assume the guess is valid
				break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until no errors

	return Guess;
}

// print the game summary
void PrintGameSummary() {

	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WIN.\n\n";
	} else {
		std::cout << "YOU LOST - Better luck next time. \n\n";
	}
	return;
}


// asks the user if he wats to play again
bool AskToPlayAgain() {

	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	// another endline for fashion
	std::cout << std::endl;

	return (Response[0] == 'y' || Response[0] == 'Y');
}
