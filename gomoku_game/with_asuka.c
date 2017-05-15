#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
int is_available_position(int x, int y, const int (*board)[BOARD_SIZE]);
int count_space(const int (*board)[BOARD_SIZE]);

int main() {
  srand((unsigned)time(NULL));
  int board[BOARD_SIZE][BOARD_SIZE];

  init_board(board);
  show_board(board);

  int turn = 0;
  int x, y;
  while (count_space(board)) {
    turn++;
    do {
      set_hand(&x, &y);
    } while (!is_available_position(x, y, board));
    board[y][x] = (turn%2) ? WHITE : BLACK;
    show_board(board);
    
    int i;
    for (i = 0; i < 100000000; i++) ;
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
  puts("------------------------------");
  printf("  ");
  for (i = 0; i < BOARD_SIZE; putchar(' '), i++) printf("%d", i+1);
  putchar('\n');
  for (i = 0; i < BOARD_SIZE; putchar('\n'), i++) {
    printf("%d ", i+1);
    for (j = 0; j < BOARD_SIZE; putchar(' '), j++)
      putchar(convert_stone_to_char(board[i][j]));
  }
  puts("------------------------------");
}

void set_hand(int* x, int* y) {
  /* puts("Set your hand !!"); */
  /* scanf("%d %d", x, y); */
  /* (*x)--; */
  /* (*y)--; */
  *x = rand() % 8;
  *y = rand() % 8;
}

int is_available_position(int x, int y, const int (*board)[BOARD_SIZE]) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE) && (board[y][x] == SPACE);
}

int count_space(const int (*board)[BOARD_SIZE]) {
  int i, j;
  int count = 0;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      if (board[i][j] == SPACE) count++;
  return count;
}
