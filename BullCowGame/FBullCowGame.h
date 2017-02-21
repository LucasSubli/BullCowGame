/*Header file for the BullCowGame class

author: lucas.subli@gmail.com
for several reasons the Unreal Coding Standard will be used
https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/index.html
*/
#pragma once

#include <string>

// make it closer to UE4 syntax
using FString = std::string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

// status from checking the guess
enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

// the class declaration
class FBullCowGame {

public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);


private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};