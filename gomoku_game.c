#include <stdio.h>

#define BOARD_SIZE  10
#define STONE_SPACE 0
#define STONE_BLACK 1 
#define STONE_WHITE 2

void disp_board(int board[BOARD_SIZE][BOARD_SIZE]);
void init_board(int board[BOARD_SIZE][BOARD_SIZE]);
void input_hand(int board[BOARD_SIZE][BOARD_SIZE], int active_player);
void init_game(int board[BOARD_SIZE][BOARD_SIZE], int* active_player);

int main() {

  int board[BOARD_SIZE][BOARD_SIZE];
  int active_player;
  
  init_game(board, active_player);
  
  disp_board(board);
  
  return 0;
} 

void init_game(int board[BOARD_SIZE][BOARD_SIZE], int* active_player) {
  *active_player = STONE_BLACK;
  init_board(board);
}

void init_board(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      board[i][j] = STONE_SPACE;
}

void disp_board(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j;

  printf("  ");  
  for (i = 0; i < BOARD_SIZE; i++) printf("%d ", i);
  putchar('\n');
  
  for (i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i);
    for (j = 0; j < BOARD_SIZE; j++) {
      switch (board[i][j]) {
      case STONE_SPACE: printf("  "); break;
      case STONE_BLACK: printf("● "); break;
      case STONE_WHITE: printf("○ "); break;
      }
    }
    putchar('\n');
  }
}

