#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
#include "player.h"
#include "GameStatus.h"

matrix_t* matrix_ofZero(int rows,int columns);

matrix_t* matrix_ofSpaces(int rows,int columns);

void printf_TicTacToe_board(matrix_t* matrixOfTokens,void (*printElement)(void*));

void printElement(void* element);

bool matrix_lockerIsZero(matrix_t* matrixOfValues,int index);

void put_TokenOnBoard(matrix_t* matrixOfValues,matrix_t* matrixOfTokens,int index,player_t* player);

void check_Winner(matrix_t* matrixOfValues,player_t* playerOne);

void matrix_Destroy(matrix_t** matrix,void(*freeElement)(void**));

void freeElement(void** element);

int main(void){

  //main code

  //create a matrix of 0 values.The values will replaced by the value of the player.
  matrix_t* Board_ofValues = matrix_ofZero(3,3);

  //create a matrix of tokens. This matrix will be print with the players tokens.
  matrix_t* Board_ofTokens = matrix_ofSpaces(3,3);

  //creation of players with their token, value and target.
  player_t* playerOne = player_new('X',1,1);
  player_t* playerTwo = player_new('O',2,8);

  //creation of gameStatus to control the status of the game.
  gameStatus_t* game = gameStatus_new(2);
  
  //index to choose the box.
  int index = 9;
  

  //loop for continue the game while game is not end.
  while(!gameStatus_isGameEnd(game)){
    
    //clean the board and print again.
    system("cls");
    printf_TicTacToe_board(Board_ofTokens,printElement);
    
    //do this if there is not a winner or the turns are lower than nine.
    if(!player_win(playerOne) && !player_win(playerTwo) && gameStatus_getTurn(game)<9){
      
      //print depend of player turn.
      if(gameStatus_getPlayerTurn(game)==1){
        printf("player one turn (%c)\n",player_getToken(playerOne));
      }
      else{
        printf("player two turn (%c)\n",player_getToken(playerTwo));
      }

      //the player select a box of the board
      bool lockIsEmpty = false;
      while(!lockIsEmpty){
        printf("Introduce yoour locker number (0-8):");
        scanf("%d",&index);
        if(index>=0 && index<9 && matrix_lockerIsZero(Board_ofValues,index)){
          lockIsEmpty = true;
        }
        else{
          printf("Invalid locker number. Try Again!\n");
        }
      }

      //update the board 
      if(gameStatus_getPlayerTurn(game)==1){
        put_TokenOnBoard(Board_ofValues,Board_ofTokens,index,playerOne);
        check_Winner(Board_ofValues,playerOne);
      }
      else{
        put_TokenOnBoard(Board_ofValues,Board_ofTokens,index,playerTwo);
        check_Winner(Board_ofValues,playerTwo);
      }

      //update the status of the game.
      gameStatus_changePlayerTurn(game);
      gameStatus_addTurn(game);
    }
    //do this if there is a winner or the board is full.
    else{
      if(!player_win(playerOne) && !player_win(playerTwo)){
        printf("\nDraw!\n");  
      }
      else{
        if(player_win(playerOne)){
          printf("\nplayer one win!\n");
        }
        else{
          if(player_win(playerTwo)){
            printf("\nplayer two win!\n");
          }
        }
      }
      gameStatus_setEndGame(game);
    }
  }
  
  //delete all the used memory
  matrix_Destroy(&Board_ofTokens,freeElement);
  matrix_Destroy(&Board_ofValues,freeElement);
  player_free(&playerOne);
  player_free(&playerTwo);
  gameStatus_free(&game);

  return 0;
}

/**
 * @brief create an int matrix full of zero
 * 
 * @param rows 
 * @param columns 
 * @return matrix_t* 
 */
matrix_t* matrix_ofZero(int rows,int columns){
  matrix_t* newOne = matrix_new(rows,columns);
  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      int* auxiliar = (int*)malloc(sizeof(int));
      *auxiliar = 0;
      matrix_set(newOne,i,j,auxiliar);
    }
  }
  return newOne;
}

/**
 * @brief create a char matrix full of spaces
 * 
 * @param rows 
 * @param columns 
 * @return matrix_t* 
 */
matrix_t* matrix_ofSpaces(int rows,int columns){
  matrix_t* newOne = matrix_new(rows,columns);
  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      char* auxiliar = (char*)malloc(sizeof(char));
      *auxiliar = ' ';
      matrix_set(newOne,i,j,auxiliar);
    }
  }
  return newOne;
}

/**
 * @brief destroy a matrix.
 * 
 * @param matrix 
 * @param freeElement 
 */
void matrix_Destroy(matrix_t** matrix,void(*freeElement)(void**)){
  for(int i=0;i<matrix_rows(*matrix);i++){
    for(int j=0;j<matrix_columns(*matrix);j++){
      void* deleteElement = matrix_get(*matrix,i,j);
      freeElement(&deleteElement);  
    }  
  }      
  matrix_free(matrix);
}

/**
 * @brief procedure to print a board.
 * 
 * @param matrix 
 * @param printElement 
 */
void printf_TicTacToe_board(matrix_t* matrix,void (*printElement)(void*)){
  for(int i=0;i<matrix_rows(matrix);i++){
    for(int j=0;j<matrix_columns(matrix);j++){
      if(i==0){
        printf("|-------------|");
      }
    }
    if(i==0){
      printf("\n");
    }
    for(int k=0;k<matrix_columns(matrix);k++){
      printf("|%d            |",i*matrix_columns(matrix)+k);
    }
    printf("\n");
    for(int l=0;l<matrix_columns(matrix);l++){
      printf("|      ");
      printElement(matrix_get(matrix,i,l));
      printf("      |");
    }
     printf("\n");
    for(int m=0;m<matrix_columns(matrix);m++){
      printf("|             |");
    }
    printf("\n");
    for(int n=0;n<matrix_columns(matrix);n++){
      printf("|-------------|");
    }
    printf("\n");
  }
}

/**
 * @brief auxiliar procedure to print a char pointer.
 * 
 * @param element 
 */
void printElement(void* element){
  printf("%c",*(char*)element);
}

/**
 * @brief auxiliar procedure to free an element.
 * 
 * @param element 
 */
void freeElement(void** element){
  free(*element);  
  element = NULL;  
}

/**
 * @brief return true if the select element of a matrix is zero and false otherwise.
 * 
 * @param matrixOfValues 
 * @param index 
 * @return true 
 * @return false 
 */
bool matrix_lockerIsZero(matrix_t* matrixOfValues,int index){
  int rows = index/matrix_rows(matrixOfValues);
  int columns = index - rows*matrix_columns(matrixOfValues);
  return (*(int*)matrix_get(matrixOfValues,rows,columns)==0);
}

/**
 * @brief procedure to update the matrix of values and the matrix of tokens.
 * 
 * @param matrixOfValues 
 * @param matrixOfTokens 
 * @param index 
 * @param player 
 */
void put_TokenOnBoard(matrix_t* matrixOfValues,matrix_t* matrixOfTokens,int index,player_t* player){
  int row = index/matrix_rows(matrixOfValues);
  int column = index - row*matrix_columns(matrixOfValues);
  
  int* auxiliar0 = matrix_get(matrixOfValues,row,column);
  *auxiliar0 = player_getValue(player);

  char* auxiliar1 = matrix_get(matrixOfTokens,row,column);
  *auxiliar1 = player_getToken(player);

  matrix_set(matrixOfTokens,row,column,auxiliar1);
  matrix_set(matrixOfValues,row,column,auxiliar0);
}

/**
 * @brief check if is a winner depend on the player target.
 * 
 * @param matrixOfValues 
 * @param player 
 */
void check_Winner(matrix_t* matrixOfValues,player_t* player){
  int diagonal1Check = 1;
  int diagonal2Check = 1;
  int rowsCheck = 0;
  int columnsCheck = 0;

  bool checkTarget = false;

  int i=0;

  while(!checkTarget && i<matrix_rows(matrixOfValues)){
    rowsCheck = 1;
    columnsCheck = 1;
    
    int j=0;

    diagonal1Check *= (*(int*)matrix_get(matrixOfValues,i,i));
    diagonal2Check *= (*(int*)matrix_get(matrixOfValues,i,(matrix_columns(matrixOfValues)-1)-i));
    
    while(j<matrix_columns(matrixOfValues)){
      rowsCheck *= (*(int*)matrix_get(matrixOfValues,i,j));
      columnsCheck *= (*(int*)matrix_get(matrixOfValues,j,i));
      j++;
    }
    if(rowsCheck == player_getTarget(player) || columnsCheck == player_getTarget(player)){
      checkTarget = true;
    }
    i++;
  }

  if(checkTarget || diagonal1Check == player_getTarget(player) || diagonal2Check == player_getTarget(player)){
    player_setWin(player);
  }
}
