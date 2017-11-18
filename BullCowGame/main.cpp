/*This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern,and is responsible for all 
user interation.For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
void PrintGameEnd();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;//instantiate a new game, which we re-use across plays

//the entry point for our application
int main(){
	do {
		PrintIntro();
		PlayGame();
	} 
	while (!BCGame.IsGameEnd()&&AskToPlayAgain());
	PrintGameEnd();
	return 0;//exit the application
}



void PrintIntro(){
	std::cout << "**************************************************************" << std::endl;
	std::cout << "	             ------------------------------------------" << std::endl;
	std::cout << "	 _  A   A   |Hi, Friend! Lets play a word game!        |" << std::endl;
	std::cout << "	{  (*T.T*)  |Guess a word what I am thinking about,    |" << std::endl;
	std::cout << "	 { />   <\\  |[acorn] means right letter in right place |" << std::endl;
	std::cout << "	  \\_A_____A |[peanut] means right letter in wrong place|" << std::endl;
	std::cout << "	             ------------------------------------------" << std::endl;

}

void PlayGame()
{
	BCGame.Reset();
	std::cout << "-*Can you guess the " << BCGame.GetHiddenWordLength()
		<< " letter isogram I'm thinking about?*-\n\n";

	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the number of try asking for guesses
	while (!BCGame.IsGameWon()&&BCGame.GetCurrentTry()<=MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "(*T.T*) <"<<" Acorns = " << BullCowCount.Bulls;
		std::cout << ".Peanuts = " << BullCowCount.Cows<<"\n\n";

	}
	PrintGameSummary();
}

void PrintGameSummary(){
	if (BCGame.IsGameWon()) {
		std::cout << " A   A  -*************************-\n";
		std::cout << "(> v <) -*Congratuation! You Win!*-\n";
		std::cout << "<     > -*************************-\n";
	}
	else {
		std::cout << " A   A  -************************-\n";
		std::cout << "(O A O) -*Better luck next time!*-\n";
		std::cout << "/>    > -************************-\n";
	}
}

void PrintGameEnd()
{
	std::cout << " A   A  -*You have guessed all  *-\n";
	std::cout << "(O v O) -*words.                *-\n";
	std::cout << "/>    > -*Thank you for playing!*-\n";
}

//loop continually until the user gives a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status=EGuessStatus::Invalid_Status;
	do 
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess:";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);//keep looping until we get no error
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again(y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0]=='y'||Response[0]=='Y';
}
