#include <stdio.h>

#define BOARD_SIZE  10

enum MODE {
  MODE_INIT,
  MODE_OP,
  MODE_DISP,
  MODE_INPUT,
  MODE_SWITCH,
  MODE_JUDGE,
  MODE_ED
};

enum STONE {
  STONE_SPACE,
  STONE_BLACK, 
  STONE_WHITE,
};

int task_disp(int board[BOARD_SIZE][BOARD_SIZE]);
void init_board(int board[BOARD_SIZE][BOARD_SIZE]);
int task_input(int board[BOARD_SIZE][BOARD_SIZE], int active_player);
int task_init(int board[BOARD_SIZE][BOARD_SIZE], int* active_player);
int task_switch(int* active_player);
char* convert_stone_into_char(int stone);
int is_inside_board(int input_x, int input_y);
int check_length(int board[BOARD_SIZE][BOARD_SIZE], int x, int y);
int task_judge(int board[BOARD_SIZE][BOARD_SIZE]);

int main() {

  int mode = MODE_INIT;
  int board[BOARD_SIZE][BOARD_SIZE];
  int active_player = 1;

  while (1) {
    switch (mode) {
      case MODE_INIT:
        mode = task_init(board, &active_player);
        break;
      case MODE_DISP:
        mode = task_disp(board);
        break;
      case MODE_INPUT:
        mode = task_input(board, active_player);
        break;
      case MODE_SWITCH:
        mode = task_switch(&active_player);
        break;
      case MODE_JUDGE:
        mode = task_judge(board);
        break;
      case MODE_ED:
        printf("See you~~\n");
        return 0;
    }
  }
} 

int task_init(int board[BOARD_SIZE][BOARD_SIZE], int* active_player) {
  *active_player = STONE_BLACK;
  init_board(board);
  task_disp(board);

  return MODE_INPUT;
}

int task_disp(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j;

  printf("  ");  
  for (i = 0; i < BOARD_SIZE; i++) printf("%d ", i);
  putchar('\n');

  for (i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i);
    for (j = 0; j < BOARD_SIZE; j++) {
      printf("%s ", convert_stone_into_char(board[i][j]));
    }
    putchar('\n');
  }
  putchar('\n');
  return MODE_JUDGE;
}

int task_input(int board[BOARD_SIZE][BOARD_SIZE], int active_player) {
  int pos_x, pos_y;

  printf("%s の番です。どこに置きますか？\n",
      (active_player == STONE_BLACK) ? "●" : "○");
  while (1) {
    scanf("%d %d", &pos_y, &pos_x);
    putchar('\n');
    if (board[pos_x][pos_y] == STONE_SPACE && is_inside_board(pos_x, pos_y)) break;
    else printf("不正な入力です。\n");
  }
  board[pos_x][pos_y] = active_player;
  return MODE_DISP;
}

int task_switch(int* active_player) {
  *active_player = (*active_player == STONE_BLACK) ? STONE_WHITE : STONE_BLACK;
  return MODE_INPUT;
}

int task_judge(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j, len_flag;
  for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == STONE_SPACE) continue;
      if (check_length(board, j, i)) {
        printf("%s の勝ちです。\n", (board[i][j] == STONE_BLACK) ? "●" : "○");
        return MODE_ED;
      }
    }
  }
  printf("foo\n");
  return MODE_SWITCH;
}

void init_board(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      board[i][j] = STONE_SPACE;
}


char* convert_stone_into_char(int stone) {
  switch (stone) {
    case STONE_SPACE: return " ";
    case STONE_BLACK: return "●";
    case STONE_WHITE: return "○";
  }
}

int is_inside_board(int input_x, int input_y) {
  return ((0 <= input_x && input_x < BOARD_SIZE) && (0 <= input_y && input_y < BOARD_SIZE));
}

int check_length(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
  int i, j, len_flag;
  int dx[] = { 0, 1, 1 };
  int dy[] = { 1, 0, 1 };

  for (i = 0; i < 3; i++) {
    for (j = 1, len_flag = 1; j <= 4; j++) {
      if (board[y][x] != board[y+j*dy[i]][x+j*dx[i]]) {
        len_flag = 0;
        break;
      }
    }
    if (len_flag == 1) return 1;
  }
  return 0;
}
