/*
  The game logic (no view code or direct user interaction)
  The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>
#include <map>

#define TMap std::map // to make syntax Unreal friendly
using FString = std::string; 
using int32 = int;

struct FBullCowCount 
{
  int32 Bulls = 0;
  int32 Cows = 0;
};

struct FLevel {
  FString hiddenWord = ""; // TODO check if this ok to init in such way?
  int32 MaxTries = 0;
};

enum EGuessStatus 
{
  Invalid_Status,
  OK,
  Not_Isogram,
  Wrong_Lenght,
  Not_Lowercase
};

class FBullCowGame {
  public:
    FBullCowGame(); // constructor
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    int32 GetMaxLevels() const;
    int32 GetCurrentLevelId() const;
    EGuessStatus CheckGuessValidity( FString ) const;
    bool isGameWon() const;

    void Reset();

    FBullCowCount SumbitValidGuess( FString );

  private:
    TMap<int32, FLevel> CurrentLevelToLevels;
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;
    int32 MyCurrentLevelId = - 1; //because we start game from Restert
    FLevel MyCurrentLevel;
    int32 MyMaxLevels;

    bool IsIsogram( FString ) const;
    bool IsLowercase( FString ) const;

};
