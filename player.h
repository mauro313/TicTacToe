#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <stdbool.h>

//player construct for tictactoe game.

typedef struct _player{
  char token;
  int value;
  int target;
  bool win;
}player_t;

player_t* player_new(char token,int value,int target);

void player_free(player_t** player);

char player_getToken(player_t* player);

int player_getValue(player_t* player);

int player_getTarget(player_t* player);

bool player_win(player_t* player);

void player_setWin(player_t* player);

#include "player.c"

#endif //PLAYER_H_INCLUDED
