#include <stdio.h>

#define BOARD_SIZE 8

enum Stone {
  SPACE,
  WHITE,
  BLACK
};

char convert_stone_to_char(int stone);
void init_board(int (*board)[BOARD_SIZE]);
void show_board(const int (*board)[BOARD_SIZE]);
void set_hand(int* x, int* y);

int main() {

  int board[BOARD_SIZE][BOARD_SIZE];

  init_board(board);
  show_board(board);
  int turn = 1;
    
  while (1) {
    printf("turn = %d\n", turn);
    turn += 1;
    int x, y;
    set_hand(&x, &y);
    board[y-1][x-1] = (turn % 2) ? BLACK : WHITE;
    show_board(board);
  }
  
  return 0;
}

char convert_stone_to_char(int stone) {
  return
    (stone == WHITE) ? 'O' :
    (stone == BLACK) ? 'X' :
    ' ';
}

void init_board(int (*board)[BOARD_SIZE]) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      board[i][j] = SPACE;
}

void show_board(const int (*board)[BOARD_SIZE]) {
  int i, j;
  puts("-------------------------");
  printf("  ");
  for (i = 0; i < BOARD_SIZE; i++) printf("%d ", i+1);
  putchar('\n');
  for (i = 0; i < BOARD_SIZE; putchar('\n'), i++) {
    printf("%d ", i+1);
    for (j = 0; j < BOARD_SIZE; putchar(' '), j++)
      putchar(convert_stone_to_char(board[i][j]));
  }
  puts("-------------------------");
}

void set_hand(int* x, int* y) {
  printf("Input your hand ! [x y]\n> ");
  scanf("%d %d", x, y);
}
