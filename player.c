#include <stdio.h>
#include <stdlib.h>
#include "player.h"

player_t* player_new(char token,int value,int target){
  player_t* newplayer = (player_t*)malloc(sizeof(player_t));
  if(newplayer == NULL){
    printf("memory cannot be reserved for a new player");
    exit(EXIT_FAILURE);  
  }    
  newplayer->token = token;
  newplayer->value = value;
  newplayer->target = target;
  newplayer->win = false;
  return newplayer;
}

void player_free(player_t** player){
  if(player!=NULL && *player!=NULL){
    free(*player);
    *player = NULL;  
  }    
}

char player_getToken(player_t* player){
  if(player==NULL){
    printf("player pointer is NULL(1)");
    exit(EXIT_FAILURE);  
  }    
  return player->token;
}

int player_getValue(player_t* player){
  if(player==NULL){
    printf("player pointer is NULL(2)");
    exit(EXIT_FAILURE);  
  }    
  return player->value;
}

int player_getTarget(player_t* player){
  if(player==NULL){
    printf("player pointer is NULL(3)");
    exit(EXIT_FAILURE);  
  }    
  return player->target;
}

bool player_win(player_t* player){
  if(player==NULL){
    printf("player pointer is NULL(4)");
    exit(EXIT_FAILURE);  
  }    
  return player->win;   
}

void player_setWin(player_t* player){
  if(player==NULL){
    printf("player pointer is NULL(5)");
    exit(EXIT_FAILURE);  
  }    
  player->win = true;  
}