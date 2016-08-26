#pragma once
#include "FBullCowGame.h"

using int32 = int;

void FBullCowGame::Reset()
{
  // TODO learn how to init structs correctly
  FLevel LEVEL_ONE;
  LEVEL_ONE.hiddenWord = "you";
  LEVEL_ONE.MaxTries = 4;

  FLevel LEVEL_TWO;
  LEVEL_TWO.hiddenWord = "news";
  LEVEL_TWO.MaxTries = 5;

  FLevel LEVEL_THREE;
  LEVEL_THREE.hiddenWord = "login";
  LEVEL_THREE.MaxTries = 6;

  FLevel LEVEL_FOUR;
  LEVEL_FOUR.hiddenWord = "vodka";
  LEVEL_FOUR.MaxTries = 5;

  CurrentLevelToLevels = { { 1, LEVEL_ONE },{ 2, LEVEL_TWO },
  { 3, LEVEL_THREE },{ 4, LEVEL_FOUR } };

  MyCurrentLevelId ++; // be carefull, init in header file

  constexpr bool IS_GAME_WON = false;
  MyCurrentLevel = CurrentLevelToLevels[MyCurrentLevelId];
  MyMaxLevels = CurrentLevelToLevels.size();

  bGameIsWon = IS_GAME_WON;
  MyMaxTries = MyCurrentLevel.MaxTries;
  MyHiddenWord = MyCurrentLevel.hiddenWord; // this word must be an isogram
  MyCurrentTry = 1;
  return;
}

FBullCowGame::FBullCowGame()
{
  Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
  return MyCurrentLevel.MaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
  return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
  return MyCurrentLevel.hiddenWord.length();
}

int32 FBullCowGame::GetMaxLevels() const
{
  return MyMaxLevels;
}

int32 FBullCowGame::GetCurrentLevelId() const
{
  return MyCurrentLevelId;
}

EGuessStatus FBullCowGame::CheckGuessValidity( FString Guess ) const
{

  if ( !IsIsogram(Guess) ) {
    return EGuessStatus::Not_Isogram;
  }
  else if ( !IsLowercase(Guess) )
  {
    return EGuessStatus::Not_Lowercase;
  }
  else if (Guess.length() != GetHiddenWordLength() ) 
  {
    return EGuessStatus::Wrong_Lenght;
  }
  else {
    return EGuessStatus::OK; 
  }
}

bool FBullCowGame::isGameWon() const
{
  return bGameIsWon;
}

//recieves a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::SumbitValidGuess( FString Guess )
{
  MyCurrentTry++;
  FBullCowCount BullCowCount;
  int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

  // loop trough all letters in the hidden word
  for (int32 MHWChar=0;  MHWChar < WordLength ; MHWChar++)
  {
    // compare letters against the guess
    for ( int32 GChar = 0; GChar < WordLength; GChar++ )
    {
      // if they match then
      if ( Guess[GChar] == MyHiddenWord[MHWChar] )
      {
        if ( MHWChar == GChar ) 
        { // if they're in the same place
          BullCowCount.Bulls++;
        } 
        else
        { // incriment cows if not
          BullCowCount.Cows++;
        }
      }
    }
  }

  if ( BullCowCount.Bulls == WordLength ) 
  { 
    bGameIsWon = true; 
  }
  else 
  {
    bGameIsWon = false;
  }

  return BullCowCount;
}

bool FBullCowGame::IsIsogram( FString Guess ) const
{
  if ( Guess.length() <= 1 ) { return true; }

  TMap<char, bool> LetterSeen;
  for ( char Letter: Guess) 
  {
    Letter = tolower( Letter ); // hande mixed case
    if ( LetterSeen[Letter] ) {
      return false; // we do NOT haee an isogram
    } 
    else 
    {
      LetterSeen[Letter] = true;
    }

  }
  return true;
}

bool FBullCowGame::IsLowercase( FString Guess ) const
{
  
  for ( char Letter : Guess ) 
  {
    if ( !islower(Letter) ) // if not a lowercase letter
      return false;
  }
  return true;
}