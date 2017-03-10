#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE  10

enum TASK_MODE {
  MODE_OP,
  MODE_DISP,
  MODE_INPUT,
  MODE_RAND,
  MODE_SWITCH,
  MODE_JUDGE,
  MODE_ASK,
  MODE_ED
};

enum GAME {
  PERSONAL,
  AUTO
};

enum STONE {
  STONE_SPACE,
  STONE_BLACK, 
  STONE_WHITE,
};

typedef struct {
  int GAME_MODE;
  int active_player;
  int round;  
} usr_status_t;

int task_disp(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t* usr_status);
void init_board(int board[BOARD_SIZE][BOARD_SIZE]);
int task_input(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t usr_status);
int task_op(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t* usr_status);
int task_switch(usr_status_t* usr_status);
char* convert_num_into_char(int stone);  // HACK: 要らなさそう
int is_inside_board(int input_x, int input_y);
int check_length(int board[BOARD_SIZE][BOARD_SIZE], int x, int y);
int task_judge(int board[BOARD_SIZE][BOARD_SIZE]);
int task_play_again();
int task_rand(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t usr_status);
char* convert_full_into_half_byte(int i);

int main(int argc, char** argv) {

  int mode = MODE_OP;
  int board[BOARD_SIZE][BOARD_SIZE];
  usr_status_t usr_status;

  if (argc < 2) usr_status.GAME_MODE = PERSONAL;  // HACK: switch内で処理したい
  else if (!strcmp(argv[1], "--auto")) usr_status.GAME_MODE = AUTO;
  else usr_status.GAME_MODE = PERSONAL;
       
  while (1) {
    switch (mode) {
    case MODE_OP:
      mode = task_op(board, &usr_status);
      break;
    case MODE_DISP:
      mode = task_disp(board, &usr_status);
      break;
    case MODE_INPUT:
      mode = task_input(board, usr_status);
      break;
    case MODE_RAND:
      mode = task_rand(board, usr_status);
      break;
    case MODE_SWITCH:
      mode = task_switch(&usr_status);
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

int task_op(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t* usr_status) {
  usr_status->active_player = STONE_BLACK;
  usr_status->round = 0;
  srand((unsigned)time(NULL));
  init_board(board);
  task_disp(board, usr_status);  // HACK: ここにtaskシリーズはどうかと

  return (usr_status->GAME_MODE == AUTO) ? MODE_RAND : MODE_INPUT;
}

int task_disp(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t* usr_status) {
  int i, j;
  putchar('\f');
  if (usr_status->round) printf("%d番手\n", usr_status->round);  // TODO: 表示に五目並べ感を出したい
  usr_status->round++;
  printf("　");  
  for (i = 0; i < BOARD_SIZE; i++) printf("%s", convert_full_into_half_byte(i));
  putchar('\n');

  for (i = 0; i < BOARD_SIZE; i++) {
    printf("%s", convert_full_into_half_byte(i));
    for (j = 0; j < BOARD_SIZE; j++) printf("%s ", convert_num_into_char(board[i][j]));
    putchar('\n');
  }
  putchar('\n');
  
  return MODE_JUDGE;
}

char* convert_full_into_half_byte(int i) {
  switch (i) {
  case 0: return "０";
  case 1: return "１";
  case 2: return "２";
  case 3: return "３";
  case 4: return "４";
  case 5: return "５";
  case 6: return "６";
  case 7: return "７";
  case 8: return "８";
  case 9: return "９";
  }
}

int task_input(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t usr_status) {  // TODO: task_randと統合, 入力をもうちょい工夫
  int pos_x, pos_y;
  
  printf("%s の番です。どこに置きますか？\n",
         (usr_status.active_player == STONE_BLACK) ? "●" : "○");
  scanf("%d %d", &pos_x, &pos_y);
  putchar('\n');
  
  if (board[pos_y][pos_x] == STONE_SPACE && is_inside_board(pos_x, pos_y)) {
    board[pos_y][pos_x] = usr_status.active_player;
    return MODE_DISP;
  }
  else {
    printf("不正な入力です。\n");
    return MODE_INPUT;
  }
}

int task_rand(int board[BOARD_SIZE][BOARD_SIZE], usr_status_t usr_status) {
  int pos_x = rand() % 10;
  int pos_y = rand() % 10;
  int i;
  if (board[pos_y][pos_x] == STONE_SPACE && is_inside_board(pos_x, pos_y)) {
    board[pos_y][pos_x] = usr_status.active_player;
    for (i = 0; i < 100000000; i++) ;
    return MODE_DISP;
  }
  else return MODE_RAND;
}

int task_switch(usr_status_t* usr_status) {
  usr_status->active_player = (usr_status->active_player == STONE_BLACK) ? STONE_WHITE : STONE_BLACK;
  return (usr_status->GAME_MODE == AUTO) ? MODE_RAND : MODE_INPUT;
}

int task_judge(int board[BOARD_SIZE][BOARD_SIZE]) {
  int i, j, len_flag;
  for (i = 0; i <= BOARD_SIZE; i++) {
    for (j = 0; j <= BOARD_SIZE; j++) {
      if (board[i][j] == STONE_SPACE) continue;
      if (check_length(board, j, i)) {
        printf("%s の勝ちです。\n", (board[i][j] == STONE_BLACK) ? "●" : "○"); // HACK: covert_num... ベタ書きのほうが綺麗かも
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

int check_length(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {  // FIXME: まれに判定ミスが生じる
  int i, j, len_flag;                                                // XXX: 右上方向の判定をしていない
  int dx[] = { 0, 1, 1, 1 };
  int dy[] = { 1, 0, 1,-1 };

  for (i = 0; i < 4; i++) {
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
