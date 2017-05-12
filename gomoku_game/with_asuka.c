#include <stdio.h>

enum Stone {
  SPACE,
  WHITE,
  BLACK
};

char convert_stone_to_char(int stone);
void init_board(int board[][8]);
void show_board(const int board[][8]);

int main() {

  int board[8][8];

  init_board(board);
  
  show_board(board);

  return 0;
}

char convert_stone_to_char(int stone) {
  switch (stone) {
  case WHITE: return 'O';
  case BLACK: return 'X';
  case SPACE: return ' ';
  }
}

void init_board(int board[][8]) {
  int i, j;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      board[i][j] = SPACE;
}

void show_board(const int board[][8]) {
  int i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++)
      printf("%c ", convert_stone_to_char(board[i][j]));
    putchar('\n');
  }
}
