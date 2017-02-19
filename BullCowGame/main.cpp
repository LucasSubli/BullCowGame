// Main class for the Bull Cow Game
// author: lucas.subli@gmail.com
// for several reasons the Unreal Coding Standard will be used
// https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/index.html

#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
string GetAndPrintGuess();

// the entry point for our application
int main() {

	// prints the intro
	PrintIntro();

	// gets the user guess
	GetAndPrintGuess();

	// print an endl for fashion
	cout << endl;
	return 0;
}

// prints the intro of the game
void PrintIntro() {

	// pre define the sizae of the word used on the game
	constexpr int WORD_LENGTH = 9;

	// introduce  the game
	cout << "Welcome to Bulls and Cows, a fun word game." << endl;
	cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?" << endl;
	cout << endl;

	return;
}

// gets the user guess
string GetAndPrintGuess() {

	string Guess = "";

	cout << "Enter your guess: ";
	getline(cin, Guess);

	// repeat the guess to the user
	cout << "Your guess: " << Guess << endl;

	return Guess;
}