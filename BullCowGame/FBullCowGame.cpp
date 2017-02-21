/*File for the BullCowGame class that controls the game.
No view code or direct use interaction.

author: lucas.subli@gmail.com
for several reasons the Unreal Coding Standard will be used
https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/index.html
*/
#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map // to make syntax UE4 friendly


FBullCowGame::FBullCowGame() { Reset(); } // default constructor

// Getters and setters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }


// compute the max number of tries
int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {2,3}, {3,5}, {4,7}, {5,11}, {6,15}, {7,20}, {8,27} };

	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

// resets the game to the default values
void FBullCowGame::Reset() {

	const FString HIDDEN_WORD = "planet"; // this word MUST be an istogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;

	return;
}

// checks if the guess is valid
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) { // if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;

	} else if (!IsLowercase(Guess)) { // if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase;

	} else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong
		return EGuessStatus::Wrong_Length;

	} else {
		return EGuessStatus::OK;
	}
}

// receives a guess, increments turn, and retuirns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); // asssuming the same length as guess
	 
	// loop through all letters in the hidedn word
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++) {

		// compare letters against the hidden guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {

			if (Guess[GChar] == MyHiddenWord[HWChar]) { // if they match

				if (HWChar == GChar) { // if they are in the same place
					BullCowCount.Bulls++;

				} else { // if they are not
					BullCowCount.Cows++;

				}
			}
		}
	}

	// check if the user has won
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	} else {
		bIsGameWon = false;
	}

	return BullCowCount;
}

// checks if the word is an isogram
bool FBullCowGame::IsIsogram(FString Word) const {

	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	// for all the letters of the word
	for (auto Letter : Word) {

		// handle mixed cases
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) {
			return false; // NOT an isogram
		} else {
			LetterSeen[Letter] = true; //add the letter to the map
		}
	}
		
	return true;
}


// checks if the word is all lower case
bool FBullCowGame::IsLowercase(FString Word) const {

	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
