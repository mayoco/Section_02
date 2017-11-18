#pragma once

#include "FBullCowGame.h"
#include <map>
#include <cstdlib>
#define TMap std::map//to make syntax Unreal friendly

FBullCowGame::FBullCowGame(){ Reset(); }//default constructor

int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,6},{4,8},{5,12},{6,14},{7,20} };
	int32 MaxTries = WordLengthToMaxTries[MyHiddenWord.length()];
	if (MaxTries == 0)MaxTries = 15;
	return MaxTries;
}


void FBullCowGame::Reset()
{

	FString record[5]{"card","sword","switch","herb","wizard"};
	if (bGameIsWon == true) {//change word if win
		int32 random = rand() % 5;
		FString HIDDEN_WORD = record[random];//this MUST no duplicate letter
		MyHiddenWord = HIDDEN_WORD;
	}
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
	else if (!IsLowercase(Guess)) { return EGuessStatus::Not_Lowercase; }
	else if (Guess.length()!=GetHiddenWordLength()) { return EGuessStatus::Wrong_Length; }
	else { return EGuessStatus::OK; }
}


//receives a VALID guess, increment turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();//assuming same length as guess

	//compare letters in guesses and hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar]==MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar)BullCowCount.Bulls++;
				else BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)bGameIsWon = true;
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup our map
	for (char Letter : Word)
	{	
		Letter = tolower(Letter);//handle mixed case
		if (LetterSeen[Letter])return false;
		LetterSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() < 1) { return true; }

	for(char Letter : Word)
	{
		if (Letter != tolower(Letter))return false;
	}
	return true;
}
