#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE  10

// 選択したポジションがtureか否かを個々でやる必要あり

enum MODE {
  MODE_OP,
  MODE_DISP,
  MODE_INPUT,
  MODE_RAND,
  MODE_SWITCH,
  MODE_JUDGE,
  MODE_ASK,
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
int task_op(int board[BOARD_SIZE][BOARD_SIZE], int* active_player);
int task_switch(int* active_player);
char* convert_num_into_char(int stone);
int is_inside_board(int input_x, int input_y);
int check_length(int board[BOARD_SIZE][BOARD_SIZE], int x, int y);
int task_judge(int board[BOARD_SIZE][BOARD_SIZE]);
int task_play_again();
int task_rand(int board[BOARD_SIZE][BOARD_SIZE], int active_player);

int main() {

  int mode = MODE_OP;
  int board[BOARD_SIZE][BOARD_SIZE];
  int active_player;

  while (1) {
    switch (mode) {
    case MODE_OP:
      mode = task_op(board, &active_player);
      break;
    case MODE_DISP:
      mode = task_disp(board);
      break;
    case MODE_INPUT:
      mode = task_input(board, active_player);
      break;
    case MODE_RAND:
      mode = task_rand(board, active_player);
      break;
    case MODE_SWITCH:
      mode = task_switch(&active_player);
      break;
    case MODE_JUDGE:
      mode = task_judge(board);
      break;
    case MODE_ASK:
      mode = task_play_again();
      break;
    case MODE_ED:
      printf("See you~~\n");
      return 0;
    }
  }
} 

int task_op(int board[BOARD_SIZE][BOARD_SIZE], int* active_player) {
  *active_player = STONE_BLACK;
  srand((unsigned)time(NULL));
  init_board(board);
  task_disp(board);

  return MODE_RAND;
}

int task_disp(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j;
  static int round;
  if (round) printf("%d番手\n", round);
  round++;
  printf("  ");  
  for (i = 0; i < BOARD_SIZE; i++) printf("%d ", i);
  putchar('\n');

  for (i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i);
    for (j = 0; j < BOARD_SIZE; j++) printf("%s ", convert_num_into_char(board[i][j]));
    putchar('\n');
  }
  putchar('\n');
  
  return MODE_JUDGE;
}

int task_input(int board[BOARD_SIZE][BOARD_SIZE], int active_player) {
  int pos_x, pos_y;
  
  printf("%s の番です。どこに置きますか？\n",
         (active_player == STONE_BLACK) ? "●" : "○");
  scanf("%d %d", &pos_x, &pos_y);
  putchar('\n');
  
  if (board[pos_y][pos_x] == STONE_SPACE && is_inside_board(pos_x, pos_y)) {
    board[pos_y][pos_x] = active_player;
    return MODE_DISP;
  }
  else {
    printf("不正な入力です。\n");
    return MODE_INPUT;
  }
}

int task_rand(int board[BOARD_SIZE][BOARD_SIZE], int active_player) {
  int pos_x = rand() % 10;
  int pos_y = rand() % 10;
  if (board[pos_y][pos_x] == STONE_SPACE && is_inside_board(pos_x, pos_y)) {
    board[pos_y][pos_x] = active_player;
    return MODE_DISP;
  }
  else return MODE_RAND;
}

int task_switch(int* active_player) {
  *active_player = (*active_player == STONE_BLACK) ? STONE_WHITE : STONE_BLACK;
  return MODE_RAND;
}

int task_judge(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j, len_flag;
  for (i = 0; i <= BOARD_SIZE - 5; i++) {
    for (j = 0; j <= BOARD_SIZE - 5; j++) {
      if (board[i][j] == STONE_SPACE) continue;
      if (check_length(board, j, i)) {
        printf("%s の勝ちです。\n", (board[i][j] == STONE_BLACK) ? "●" : "○");
        return MODE_ASK;
      }
    }
  }
  return MODE_SWITCH;
}

int task_play_again() {
  char input[8] = {0};
  
  printf("プレイアゲイン？？(yes/no)\n"
         ">");
  scanf("%7s", input);
  putchar('\n');
  
  if (!strcmp("yes", input))       return MODE_OP;
  else if (!strcmp("no", input))   return MODE_ED;
  else printf("不正な入力です\n"); return MODE_ASK;
}

void init_board(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      board[i][j] = STONE_SPACE;
}


char* convert_num_into_char(int stone) {
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
