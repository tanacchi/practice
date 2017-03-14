#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <random>
#include <string>

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

struct usr_status {
  game  game_mode;
  stone active_player;
  int   round;
};

constexpr std::size_t board_size {10};
using board_row  = std::array<stone, board_size>;
using board_type = std::array<board_row, board_size>;

task_mode task_disp(const board_type&, usr_status&);
void init_board(board_type&);
task_mode task_input(board_type&, const usr_status&);
task_mode task_op(board_type&, usr_status&);
task_mode task_switch(usr_status&);
const char* convert_num_into_char(stone);  // HACK: 要らなさそう
bool is_inside_board(int, int);
bool check_length(board_type&, int, int);
task_mode task_judge(board_type&);
task_mode task_play_again();
task_mode task_rand(board_type&, const usr_status&);
const char* convert_full_into_half_byte(int);

int main(int argc, char** argv) {

  task_mode mode {task_mode::OP};
  board_type board;
  usr_status status;

  if (argc < 2) status.game_mode = game::PERSONAL;  // HACK: switch内で処理したい
  else if (!std::char_traits<char>::compare(argv[1], "--auto", 6)) status.game_mode = game::AUTO;
  else status.game_mode = game::PERSONAL;

  while (true) {
    switch (mode) {
    case task_mode::OP:
      mode = task_op(board, status);
      break;
    case task_mode::DISP:
      mode = task_disp(board, status);
      break;
    case task_mode::INPUT:
      mode = task_input(board, status);
      break;
    case task_mode::RAND:
      mode = task_rand(board, status);
      break;
    case task_mode::SWITCH:
      mode = task_switch(status);
      break;
    case task_mode::JUDGE:
      mode = task_judge(board);
      break;
    case task_mode::ASK:
      mode = task_play_again();
      break;
    case task_mode::ED:
      std::cout << "See you~~" << std::endl;
      return 0;
    }
  }
}

task_mode task_op(board_type& board, usr_status& status) {
  status.active_player = stone::BLACK;
  status.round = 0;
  init_board(board);
  task_disp(board, status); // HACK: ここにtaskシリーズはどうかと

  return (status.game_mode == game::AUTO) ? task_mode::RAND : task_mode::INPUT;
}

task_mode task_disp(const board_type& board, usr_status& status) {
  std::cout.put('\f');
  std::cout << status.round + 1 <<  "番手\n  ";  // TODO: 表示に五目並べ感を出したい

  for (std::size_t i {}; i < board.size(); ++i)
    std::cout << convert_full_into_half_byte(i);
  std::cout.put('\n');

  for (auto it {board.begin()}; it != board.end(); ++it) {
    std::cout << convert_full_into_half_byte(it - board.begin());
    std::for_each(it->begin(), it->end(), [](const auto& value){std::cout << convert_num_into_char(value);});
    std::cout.put('\n');
  }
  std::cout << std::endl;

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

task_mode task_input(board_type& board, const usr_status& status) {  // TODO: task_randと統合, 入力をもうちょい工夫
  std::cout << convert_num_into_char(status.active_player) <<  "の番です。どこに置きますか？\n > " << std::flush;

  std::size_t pos_x, pos_y;
  std::cin >> pos_x >> pos_y;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (!is_inside_board(pos_x, pos_y) || board[pos_y][pos_x] != stone::SPACE) {
    std::cout << "\n不正な入力です。" << std::endl;
    return task_mode::INPUT;
  }

  board[pos_y][pos_x] = status.active_player;
  return task_mode::DISP;
}

task_mode task_rand(board_type& board, const usr_status& status) {
  static std::default_random_engine rand {std::random_device{}()};
  static std::uniform_int_distribution<std::size_t> dist {0, board_size - 1};
  board_row::size_type  pos_x = dist(rand);
  board_type::size_type pos_y = dist(rand);
  if (!is_inside_board(pos_x, pos_y) || !(board[pos_y][pos_x] == stone::SPACE))
    return task_mode::RAND;
  board[pos_y][pos_x] = status.active_player;
  return task_mode::DISP;
}

task_mode task_switch(usr_status& status) {
  ++status.round;
  status.active_player = (status.active_player == stone::BLACK) ? stone::WHITE : stone::BLACK;
  return (status.game_mode == game::AUTO) ? task_mode::RAND : task_mode::INPUT;
}

task_mode task_judge(board_type& board) {
  for (std::size_t i {}; i < board_size; i++) {
    for (std::size_t j {}; j < board_size; j++) {
      if (board[i][j] == stone::SPACE) continue;
      if (check_length(board, j, i)) {
        std::cout << convert_num_into_char(board[i][j]) << "の勝ちです。" << std::endl;
        return task_mode::ASK;
      }
    }
  }
  return task_mode::SWITCH;
}

task_mode task_play_again() {

  std::cout << "プレイアゲイン？？(yes/no)\n > " << std::flush;
  std::string input;
  std::cin >> input;
  std::cout.put('\n');

  if (input == "yes") return task_mode::OP;
  if (input == "no")  return task_mode::ED;
  std::cout << "不正な入力です" << std::endl;
  return task_mode::ASK;
}

void init_board(board_type& board) {
  std::for_each(board.begin(), board.end(), [](auto& e){e.fill(stone::SPACE);});
}


const char* convert_num_into_char(stone value) {
  switch (value) {
  case stone::SPACE: return "  ";
  case stone::BLACK: return "● ";
  case stone::WHITE: return "○ ";
  }
}

bool is_inside_board(int input_x, int input_y) {
  return (0 <= input_x && input_x < board_size) && (0 <= input_y && input_y < board_size);
}

bool check_length(board_type& board, int x, int y) {  // FIXME: まれに判定ミスが生じる
  int i, j, len_flag;                                                // XXX: 右上方向の判定をしていない
  int dx[] = { 0, 1, 1, 1 };
  int dy[] = { 1, 0, 1,-1 };

  for (i = 0; i < 4; i++) {
    for (j = 1, len_flag = 1; j <= 4; j++) {
      if (board[y][x] != board[y+j*dy[i]][x+j*dx[i]]
          || !is_inside_board(x+j*dx[i], y+j*dy[i])) {
        len_flag = 0;
        break;
      }
    }
    if (len_flag == 1) return true;
  }
  return false;
}
