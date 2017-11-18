/*The game logic(n view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame();//constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon()const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameEnd() const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	int32 level = 0;
	bool bGameIsWon;
	FString HiddenWords[7]{ "key","bag","card","herb","sword","dragon","wizard" };//this MUST no duplicate letter


	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;


};