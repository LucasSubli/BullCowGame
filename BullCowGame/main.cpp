// Main class for the Bull Cow Game
// author: lucas.subli@gmail.com
// for several reasons the Unreal Coding Standard will be used
// https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/index.html

#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();

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

	// pre define the sizae of the word used on the game
	constexpr int WORD_LENGTH = 9;

	// introduce  the game
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}

// play the game
void PlayGame() {

	int MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	for (int count = 1; count <= MaxTries; count++) {

		std::string Guess = GetGuess();
		// repeat the guess to the user
		std::cout << "Your guess: " << Guess << std::endl;
		// another endline for fashion
		std::cout << std::endl;
	}
}

// gets the user guess
std::string GetGuess() {

	int CurrentTry = BCGame.GetCurrentTry();

	std::string Guess = "";

	std::cout << "Try " << CurrentTry << ". ";
	std::cout << "Enter your guess: ";
	std::getline(std::cin, Guess);

	return Guess;
}


// asks the user if he wats to play again
bool AskToPlayAgain() {

	std::cout << "Do you want to play again (y/n)?";
	std::string Response = "";
	std::getline(std::cin, Response);
	// another endline for fashion
	std::cout << std::endl;

	return (Response[0] == 'y' || Response[0] == 'Y');
}
