#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() {
	Reset();	
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

void FBullCowGame::Reset() {

	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (false) { // if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;

	} else if (false) { // if the guess isn't all lowercase
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

	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	} else {
		bIsGameWon = false;
	}

	return BullCowCount;
}
