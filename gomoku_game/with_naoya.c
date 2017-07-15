#include <stdio.h>

enum Stone {
  Space,
  Black,
  White
};

enum Task {
  Op,
  Disp,
  Input,
  Judge,
  Switch,
  Ask,
  End
};

void init_board(enum Stone (*board)[8]) {
  int i, j;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      board[i][j] = Black;
}

char to_char(enum Stone stone) {
  switch (stone) {
  case Space: return ' ';
  case Black: return 'X';
  case White: return 'O';
  }
}

void show(enum Stone (*board)[8]) {
  int i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      putchar(to_char(board[i][j]));
      putchar(' ');
    }
    putchar('\n');
  }
}

int main() {

  enum Stone board[8][8];
  enum Task task = Op;

  init_board(board);
  show(board);

  printf("Input hand !");
  int x, y;
  scanf("%d %d", &x, &y);
  board[y][x] = Space;

  show(board);

  /* while (1) { */
  /*   switch (task) { */
  /*   case Op: */
  /*     break; */
  /*   case Disp: */
  /*     break; */
  /*   case Input: */
  /*     break; */
  /*   case Judge: */
  /*     break; */
  /*   case Switch: */
  /*     break; */
  /*   case Ask: */
  /*     break; */
  /*   case End: */
  /*     break; */
  /*   } */
  /* } */

  return 0;
}

