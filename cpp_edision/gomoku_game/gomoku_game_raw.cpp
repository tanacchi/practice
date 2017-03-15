#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

constexpr std::size_t board_size {10};

enum class task_mode {
  OP,
  DISP,
  INPUT,
  RAND,
  SWITCH,
  JUDGE,
  ASK,
  ED
};

enum class game {
  PERSONAL,
  AUTO
};

enum class stone {
  SPACE,
  BLACK,
  WHITE,
};

struct usr_status_t {
  game game_mode;
  stone active_player;
  int round;  
};

task_mode task_disp(stone[][board_size], usr_status_t*); //CAUTION: want to int[size][size], but it mean int[][size]. by @FORNO.
void init_board(stone[][board_size]);
task_mode task_input(stone[][board_size], usr_status_t);
task_mode task_op(stone[][board_size], usr_status_t*);
task_mode task_switch(usr_status_t*);
const char* convert_num_into_char(stone);  // HACK: 要らなさそう
bool is_inside_board(int, int);
bool check_length(stone[][board_size], int, int);
task_mode task_judge(stone[][board_size]);
task_mode task_play_again();
task_mode task_rand(stone[][board_size], usr_status_t);
const char* convert_full_into_half_byte(int);

int main(int argc, char** argv) {

  task_mode mode = task_mode::OP;
  stone board[board_size][board_size];
  usr_status_t usr_status;

  if (argc < 2) usr_status.game_mode = game::PERSONAL;  // HACK: switch内で処理したい
  else if (!strcmp(argv[1], "--auto")) usr_status.game_mode = game::AUTO;
  else usr_status.game_mode = game::PERSONAL;
       
  while (1) {
    switch (mode) {
    case task_mode::OP:
      mode = task_op(board, &usr_status);
      break;
    case task_mode::DISP:
      mode = task_disp(board, &usr_status);
      break;
    case task_mode::INPUT:
      mode = task_input(board, usr_status);
      break;
    case task_mode::RAND:
      mode = task_rand(board, usr_status);
      break;
    case task_mode::SWITCH:
      mode = task_switch(&usr_status);
      break;
    case task_mode::JUDGE:
      mode = task_judge(board);
      break;
    case task_mode::ASK:
      mode = task_play_again();
      break;
    case task_mode::ED:
      printf("See you~~\n");
      return 0;
    }
  }
} 

task_mode task_op(stone board[][board_size], usr_status_t* usr_status) {
  usr_status->active_player = stone::BLACK;
  usr_status->round = 0;
  srand((unsigned)time(NULL));
  init_board(board);
  task_disp(board, usr_status); // HACK: ここにtaskシリーズはどうかと
                                // NOTE: こっちのほうが処理がわかりやすくなるならこれもこれでありですよ。
                                //       そのために返り値でmode変更してるってところもあります。
                                //       つまり、戻り値を利用せずに単体で利用できるのも魅力です。
                                //       NOTE by @FORNO.

  return (usr_status->game_mode == game::AUTO) ? task_mode::RAND : task_mode::INPUT;
}

task_mode task_disp(stone board[][board_size], usr_status_t* usr_status) {
  int i, j;
  putchar('\f');
  if (usr_status->round) printf("%d番手\n", usr_status->round);  // TODO: 表示に五目並べ感を出したい
  usr_status->round++;
  printf("　");  
  for (i = 0; i < board_size; i++) printf("%s", convert_full_into_half_byte(i));
  putchar('\n');

  for (i = 0; i < board_size; i++) {
    printf("%s", convert_full_into_half_byte(i));
    for (j = 0; j < board_size; j++) printf("%s ", convert_num_into_char(board[i][j]));
    putchar('\n');
  }
  putchar('\n');
  
  return task_mode::JUDGE;
}

const char* convert_full_into_half_byte(int i) {
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

task_mode task_input(stone board[][board_size], usr_status_t usr_status) {  // TODO: task_randと統合, 入力をもうちょい工夫
  int pos_x, pos_y;
  
  printf("%s の番です。どこに置きますか？\n",
         (usr_status.active_player == stone::BLACK) ? "●" : "○");
  scanf("%d %d", &pos_x, &pos_y);
  putchar('\n');
  
  if (is_inside_board(pos_x, pos_y) && board[pos_y][pos_x] == stone::SPACE) {
    board[pos_y][pos_x] = usr_status.active_player;
    return task_mode::DISP;
  }
  else {
    printf("不正な入力です。\n");
    return task_mode::INPUT;
  }
}

task_mode task_rand(stone board[][board_size], usr_status_t usr_status) {
  int pos_x = rand() % 10;
  int pos_y = rand() % 10;
  int i;
  if (is_inside_board(pos_x, pos_y) && board[pos_y][pos_x] == stone::SPACE) {
    board[pos_y][pos_x] = usr_status.active_player;
    return task_mode::DISP;
  }
  else return task_mode::RAND;
}

task_mode task_switch(usr_status_t* usr_status) {
  usr_status->active_player = (usr_status->active_player == stone::BLACK) ? stone::WHITE : stone::BLACK;
  return (usr_status->game_mode == game::AUTO) ? task_mode::RAND : task_mode::INPUT;
}

task_mode task_judge(stone board[][board_size]) {
  int i, j, len_flag;
  for (i = 0; i <= board_size; i++) {
    for (j = 0; j <= board_size; j++) {
      if (board[i][j] == stone::SPACE) continue;
      if (check_length(board, j, i)) {
        printf("%s の勝ちです。\n", (board[i][j] == stone::BLACK) ? "●" : "○"); // HACK: covert_num... ベタ書きのほうが綺麗かも
        return task_mode::ASK;
      }
    }
  }
  return task_mode::SWITCH;
}

task_mode task_play_again() {
  char input[8] = {0};
  
  printf("プレイアゲイン？？(yes/no)\n"
         ">");
  scanf("%7s", input);
  putchar('\n');
  
  if (!strcmp("yes", input))       return task_mode::OP;
  else if (!strcmp("no", input))   return task_mode::ED;
  else printf("不正な入力です\n"); return task_mode::ASK;
}

void init_board(stone board[][board_size]) {
  int i, j;
  for (i = 0; i < board_size; i++)
    for (j = 0; j < board_size; j++)
      board[i][j] = stone::SPACE;
}


const char* convert_num_into_char(stone value) {
  switch (value) {
  case stone::SPACE: return " ";
  case stone::BLACK: return "●";
  case stone::WHITE: return "○";
  }
}

bool is_inside_board(int input_x, int input_y) {
  return (0 <= input_x && input_x < board_size) && (0 <= input_y && input_y < board_size);
}

bool check_length(stone board[][board_size], int x, int y) {  // FIXME: まれに判定ミスが生じる
  int i, j, len_flag;                                                // XXX: 右上方向の判定をしていない
  int dx[] = { 0, 1, 1, 1 };
  int dy[] = { 1, 0, 1,-1 };

  for (i = 0; i < 4; i++) {
    for (j = 1, len_flag = 1; j <= 4; j++) {
      if (!is_inside_board(x+j*dx[i], y+j*dy[i]) ||
          board[y][x] != board[y+j*dy[i]][x+j*dx[i]]) {
        len_flag = 0;
        break;
      }
    }
    if (len_flag == 1) return true;
  }
  return false;
}
