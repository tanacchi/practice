#include <stdio.h>

#define BOARD_SIZE 8

enum Stone {
  WHITE,
  BLACK,
  SPACE
};

char convert_stone_to_char(int);
void init_board(int board[][BOARD_SIZE]);
void show_board(const int board[][BOARD_SIZE]);
int is_available_position(int x, int y, const int board[][BOARD_SIZE]);

int main() {

  int board[BOARD_SIZE][BOARD_SIZE];
  init_board(board);
  show_board(board);

  int turn = 0;
  
  while (turn++ < 5) {
    int x, y;
    do {
      puts("Input the position !\n"
           "[x y]");
      scanf("%d %d", &x, &y);
    } while (!is_available_position(x, y, board));
    board[y][x] = (turn%2) ? BLACK : WHITE;
    show_board(board);
  }
  puts("See you ~~");
  
  return 0;
}

char convert_stone_to_char(int stone) {
  return
    (stone == WHITE) ? 'O' :
    (stone == BLACK) ? 'X' :
    ' ';
}

void init_board(int board[][BOARD_SIZE]) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      board[i][j] = SPACE;
}

void show_board(const int board[][BOARD_SIZE]) {
  int i, j;
  puts("----------------------------");
  printf("  ");
  for (i = 0; i < BOARD_SIZE; putchar(' '), i++) printf("%d", i);
  putchar('\n');
  for (i = 0; i < BOARD_SIZE; putchar('\n'), i++) { 
    printf("%d ", i);
    for (j = 0; j < BOARD_SIZE; putchar(' '), j++) 
      putchar(convert_stone_to_char(board[i][j]));
  }
  putchar('\n');
  puts("--------------------------");
}

int is_available_position(int x, int y, const int board[][BOARD_SIZE]) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE) && (board[y][x] == SPACE);
}
