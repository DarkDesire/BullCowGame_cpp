/*
  This is the console executable, that makes use of the BullCowGame class
  This acts as the view in MVC pattern, and is responsible for all
  user interaction. FOr game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void GameLoop();
void PrintIntro();
bool AskToPlayAgain();
void PrintGameSummary();
FText GetValidGuess();

FBullCowGame BCGame; //instantiate a new game, which we re-use acros plays

int main() {
 
  bool bPlayAgain = false;
  do 
  {
    PrintIntro();
    GameLoop();
    bPlayAgain = AskToPlayAgain();
  } while ( bPlayAgain );
  
  return 0;
}

void PrintIntro()
{
  std::cout << "       `:::.                                                                    ";
  std::cout << "    ,#########@                    @###@      ####                 @###:        ";
  std::cout << "   @###########   +###             @####      ####                 ####:        ";
  std::cout << "  @###########'   ####+   ````     @####      ####                 ####:        ";
  std::cout << "  ######',,:##    ####+   ####     @####      ####                 ####:        ";
  std::cout << " @####:           '###    ####     @####      ####                 ####:        ";
  std::cout << " #####                    ####     @####      ####                 ####:        ";
  std::cout << " ####             ++++`   ####+++  @####      ####  ,''''    ''''  ####,'####,  ";
  std::cout << ",####             ####, #########  @####::::::####  '####    ####  ###########@ ";
  std::cout << ";####    ######@  ####, #########  @##############  '####    ####  ############.";
  std::cout << "'####   `#######  ####, #########  @##############  '####    ####  #####+,'#####";
  std::cout << "'####   `#######  ####,   ####     @##############  '####    ####  ####`   :####";
  std::cout << ";####   `#######  ####,   ####     @####      ####  '####    ####  ####`    ####";
  std::cout << ",####      :####  ####,   ####     @####      ####  '####    ####  ####`    ####";
  std::cout << " ####      ;####  ####,   ####     @####      ####  '####    ####  ####`    ####";
  std::cout << " #####     ;####  ####,   ####     @####      ####  '####    ####  ####`    ####";
  std::cout << " @####@    :####  ####,   ####     @####      ####  '####    ####  ####`    ####";
  std::cout << "  ##############  ####,   #####    @####      ####  :####: ,#####  #####: `####@";
  std::cout << "  .#############  ####,   @######  @####      ####   ############  ############.";
  std::cout << "    ###########@  ####,    ######  @####      ####   @###########  ###########@ ";
  std::cout << "     ,@######+    @@@@.     @####  #@@@#      @@@@    '#####; @@@  @@@  @####+  ";
  std::cout << "\n\n\tBull and Cows Game" << std::endl;
  return;
}

// plays a single game to completion
void GameLoop()
{
  BCGame.Reset();
  int32 MaxTries = BCGame.GetMaxTries();
  int32 MaxLevels = BCGame.GetMaxLevels();
  int32 CurrentLevelId = BCGame.GetCurrentLevelId();
  std::cout << "\tCurrent Level: " << CurrentLevelId<< " of " << MaxLevels << std::endl;
  std::cout << "\tCan you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl << std::endl;

  // loop asking for guesses while the game 
  // is NOT won and there are still tries remaining
  while ( !BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries && CurrentLevelId <= MaxLevels ) {
    FText Guess = GetValidGuess(); 

    // Sumbit valid guess to the game, and receive counts
    FBullCowCount BullCowCount = BCGame.SumbitValidGuess( Guess );

    std::cout << "Bulls = " << BullCowCount.Bulls;
    std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
  }

  PrintGameSummary();

  return;
}

void PrintGameSummary() {
  if (BCGame.isGameWon()){
    std::cout << "WELL DONE! - YOU WON!";
  }
  else 
  {
    std::cout << "Good luck next time!";
  }
  std::cout << std::endl << std:: endl;
  return;
}



// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
  bool bIsValidInput = false;

  FText Guess = "";
  EGuessStatus Status = EGuessStatus::Invalid_Status;
  do {
    int32 CurrentTry = BCGame.GetCurrentTry();
    std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
    std::getline( std::cin, Guess );

    EGuessStatus Status = BCGame.CheckGuessValidity( Guess );
    switch ( Status ) {
      case EGuessStatus::Wrong_Lenght:
        std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
        break;
      case EGuessStatus::Not_Lowercase:
        std::cout << "Word should be in lowercase.\n\n";
        break;
      case EGuessStatus::Not_Isogram:
        std::cout << "Please enter a word without repeating letters.\n\n";
        break;
      default:
        bIsValidInput = true;
    }
  } while ( !bIsValidInput );
  return Guess;
}

bool AskToPlayAgain() {
  std::cout << "Do you want to play again? (y/n)" << std::endl;
  FText Response = "";
  std::getline( std::cin, Response );
  std::cout << std::endl;
  return ((Response[0] == 'y') || (Response[0] == 'Y'));
}