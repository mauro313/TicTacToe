#ifndef GAMESTATUS_H_INCLUDED
#define GAMESTATUS_H_INCLUDED
#include <stdbool.h>

//construct for the status of the game

typedef struct _gameStatus{
  bool endedGame;
  int amountOfPlayers;
  int playerTurn;
  int amountOfTurns;
}gameStatus_t;

gameStatus_t* gameStatus_new(int amounOfPlayers);

void gameStatus_free(gameStatus_t** game);

bool gameStatus_isGameEnd(gameStatus_t* game);

int gameStatus_getPlayerTurn(gameStatus_t* game);

void gameStatus_changePlayerTurn(gameStatus_t* game);

void gameStatus_setEndGame(gameStatus_t* game);

int gameStatus_getTurn(gameStatus_t* game);

void gameStatus_addTurn(gameStatus_t* game);

#include "GameStatus.c"

#endif //GAMESTATUS_H_INCLUDED
