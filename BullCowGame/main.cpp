/* Main class for the Bull Cow Game
This is the console executable for the BullCow class
acting as the view in a MVC pattern

author: lucas.subli@gmail.com
for several reasons the Unreal Coding Standard will be used
https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/index.html
 */

#include <iostream>
#include <string>
#include "FBullCowGame.h"


// make it closer to UE4 syntax
using FText = std::string;
using int32 = int;

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

	// introduce  the game
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}

// play the game
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
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
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
