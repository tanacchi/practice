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
int is_inside_board(int x, int y);
int check_length(int x, int y, const int (*board)[BOARD_SIZE]);
int is_game_finish(const int (*board)[BOARD_SIZE]);

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
    if (is_game_finish(board)) break;
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
  return  is_inside_board(x, y) && (board[y][x] == SPACE);
}

int count_space(const int (*board)[BOARD_SIZE]) {
  int i, j;
  int count = 0;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      if (board[i][j] == SPACE) count++;
  return count;
}

int is_inside_board(int x, int y) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

int check_length(int x, int y, const int (*board)[BOARD_SIZE]) {
  const int dx[] = { 1, 1, 1, 0 };
  const int dy[] = {-1, 0, 1, 1 };
  int i, j;
  int mystone = board[y][x];
  for (i = 0; i < 4; i++) {
    for (j = 1; is_inside_board(x+dx[i]*j, y+dy[i]*j); j++) {
      if (mystone == board[y+dy[i]*j][x+dx[i]*j]) continue;
      else if (j > 5) return 1;
      else break;
    }
  }
  return 0;
}

int is_game_finish(const int (*board)[BOARD_SIZE]) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {
      if (check_length(i, j, board)) return 1;
    }
  }
  return 0;
}
