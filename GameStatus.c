#include <stdio.h>
#include <stdlib.h>
#include "GameStatus.h"

gameStatus_t* gameStatus_new(int amountOfPlayers){
  gameStatus_t* newOne = (gameStatus_t*)malloc(sizeof(gameStatus_t));
  if(newOne == NULL){
    printf("memory cannot be reserved for a new gameStatus");
    exit(EXIT_FAILURE);  
  }   
  newOne->amountOfPlayers = amountOfPlayers;
  newOne->endedGame = false;
  newOne->playerTurn = 1;
  newOne->amountOfTurns = 0;
  return newOne;
}

void gameStatus_free(gameStatus_t** game){
  if(game!=NULL &&  *game!=NULL){
    free(*game);
    *game = NULL;  
  }  
}

bool gameStatus_isGameEnd(gameStatus_t* game){
  if(game == NULL){
    printf("gameStatus pointer is NULL(1)");
    exit(EXIT_FAILURE);  
  }  
  return game->endedGame;
}

int gameStatus_getPlayerTurn(gameStatus_t* game){
  if(game == NULL){
    printf("gameStatus pointer is NULL(2)");
    exit(EXIT_FAILURE);  
  }  
  return game->playerTurn;
}

void gameStatus_changePlayerTurn(gameStatus_t* game){  
  if(game == NULL){
    printf("gameStatus pointer is NULL(3)");
    exit(EXIT_FAILURE);  
  }  
  if(game->playerTurn == game->amountOfPlayers){
    if(game->amountOfPlayers == 1){
      game->playerTurn = 0;  
    }  
    else{
      game->playerTurn = 1;
    }
  }
  else{
    game->playerTurn++;  
  }
}

void gameStatus_setEndGame(gameStatus_t* game){  
  if(game == NULL){
    printf("gameStatus pointer is NULL(4)");
    exit(EXIT_FAILURE);  
  }  
  game->endedGame = true;
}

int gameStatus_getTurn(gameStatus_t* game){
  if(game == NULL){
    printf("gameStatus pointer is NULL(5)");
    exit(EXIT_FAILURE);  
  }  
  return game->amountOfTurns;
}

void gameStatus_addTurn(gameStatus_t* game){
  if(game == NULL){
    printf("gameStatus pointer is NULL(6)");
    exit(EXIT_FAILURE);  
  }  
  game->amountOfTurns++;
}