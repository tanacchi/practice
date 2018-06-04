#include <array>
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

static const std::vector<std::vector<char> > board = {
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'},
  {'O', 'X', 'O', 'X', 'O', 'X', 'O', 'X'}
};

void show1()
{
  for (int i {0}; i < board[0].size() + 1; ++i) std::cout << "--";
  std::cout << std::endl;
  std::cout << "  " << std::flush;
  for (int i {0}; i < board[0].size(); std::cout.put(' '), ++i)
    std::cout << i+1 << std::flush;
  std::cout << std::endl;
  for (int y{0}; y < board.size(); std::cout.put('\n'), ++y) {
    std::cout << y+1 << ' ' << std::flush;
    for (int x {0}; x < board[0].size(); std::cout.put(' '), ++x)
      std::cout.put(board[y][x]);
  }
  for (int i {0}; i < board[0].size() + 1; ++i) std::cout << "--";
  std::cout << std::endl;
}

void show2()
{
  std::stringstream ss;
  for (int i {0}; i < board[0].size() + 1; ++i) ss << "--";
  ss << std::endl;
  ss << "  " << std::flush;
  for (int i {0}; i < board[0].size(); ss.put(' '), ++i) ss << i+1 << std::flush;
  ss << std::endl;
  for (int y{0}; y < board.size(); ss.put('\n'), ++y) {
    ss << y+1 << ' ' << std::flush;
    for (int x {0}; x < board[0].size(); ss.put(' '), ++x) ss.put(board[y][x]);
  }
  for (int i {0}; i < board[0].size() + 1; ++i) ss << "--";
  ss << std::endl;
  std::cout << ss.str();
}

template <typename Func>
decltype(auto) time_test(Func func)
{
  auto start{std::chrono::system_clock::now()};
  for (int i = 0; i < 100000; ++i) func();
  auto end{std::chrono::system_clock::now()};
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main()
{
  // 1. stringstream に流し込んで最後に出力した方が 2倍速いNE
  auto time1{time_test(show1)}, time2{time_test(show2)};
  std::cout << "time : " << time1 << "(millisecond)" << std::endl;
  std::cout << "time : " << time2 << "(millisecond)" << std::endl;

  return 0;
}
