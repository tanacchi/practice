// ------------------------- Include files -------------------------------------
#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"
#include <string.h>

// ------------------------- Definitions ---------------------------------------
#define MAX_FWD_SPIN  10000
#define MAX_REV_SPIN -10000
#define HALF_FWD_SPIN  5000
#define HALF_REV_SPIN -5000
#define NOT_MOVE 0
#define THRESHOLD 200

// ------------------------- Function prototypes -------------------------------
void sensor_test(void);
void wait_Switch(int);
void run_motor(int, int);
void go_straight(void);
void back_straight(void);
void stop_motor(void);
void curv_right(void);
void curv_left(void);
void turn_right(void);
void turn_left(void);
void direct_right(void);
void direct_left(void);
void half_direct_right(void);
void half_direct_left(void);
void split_right(void);
void split_left(void);
void stride_front(void);
void stride_right(int);
void stride_left(int);
void finish_turn(void);
int read_sensor(unsigned char);
int right_isWhite(void);
int left_isWhite(void);
int check_Both_sensor(void);
int check_Both_Black(void);
int check_Both_White(void);
void line_control_LR(int);
void line_control_L(int);
void line_control_R(int);
void stride_Line(int);
int trace_mode_reader(char*);
int stride_mode_reader(char*);
void linetrace_LR(char*);
void linetrace_L(char*);
void linetrace_R(char*);
void on_the_Line(char*);
void ERROR(void);

// ------------------------- Toward patterns (function pointer) ----------------
void (*toward_right[])(void) = {
  curv_right,
  turn_right,
  half_direct_right,
  direct_right,
  split_right
};

void (*toward_left[])(void) = {
  curv_left,
  turn_left,
  half_direct_left,
  direct_left,
  split_left
};

// -------------------------- For Course_1 -------------------------------------
void Course_1(void){
  wait_Switch(1);
  linetrace_LR("jkdfsmxcsdfj");
};

// -------------------------- For Cource_2 -------------------------------------
void Course_2(void){
  wait_Switch(2);
  on_the_Line("front");
  on_the_Line("front");
  linetrace_R("curv");
  on_the_Line("rightT");
  linetrace_LR("curv");
  on_the_Line("front");
  linetrace_LR("half");
  on_the_Line("front");
  on_the_Line("front");
  on_the_Line("right+");
  linetrace_LR("turn");
  finish_turn();
}

// -------------------------- For Course_3 -------------------------------------
void Course_3(void){
  wait_Switch(3);
  linetrace_LR("turn");
  on_the_Line("leftT");
}

// -------------------------- Array of Course ----------------------------------
void (*Course_Select[])(void) = {
  sensor_test,
  Course_1,
  Course_2,
  Course_3
};

// -------------------------- Main ---------------------------------------------
int main(void){
  const unsigned short MainCycle = 60;
  Init(MainCycle);
  Course_Select[0]();
  return 0;
}

// -------------------------- Test code ----------------------------------------
void sensor_test(void){
  while (1) LED(check_Both_sensor());
}

// -------------------------- Particure code -----------------------------------
void wait_Switch(int course_num){
  while(getSW() != 1) LED(course_num);
  while(getSW() == 1) ;
}

// -------------------------- Based run code -----------------------------------
void run_motor(int left, int right){
  Mtr_Run_lv(right, -left, 0, 0, 0, 0);
}

// -------------------------- Basic running pattern-----------------------------
void go_straight(void){
  run_motor(MAX_FWD_SPIN, MAX_FWD_SPIN);
}

void back_straight(void){
  run_motor(MAX_REV_SPIN, MAX_REV_SPIN);
}

void stop_motor(void){
  run_motor(NOT_MOVE, NOT_MOVE);
}

void turn_right(void){
  run_motor(MAX_FWD_SPIN, NOT_MOVE);
}

void turn_left(void){
  run_motor(NOT_MOVE, MAX_FWD_SPIN);
}

void curv_right(void){
  run_motor(MAX_FWD_SPIN, HALF_FWD_SPIN);
}

void curv_left(void){
  run_motor(HALF_FWD_SPIN, MAX_FWD_SPIN);
}

void direct_right(void){
  run_motor(MAX_FWD_SPIN, MAX_REV_SPIN);
}

void direct_left(void){
  run_motor(MAX_REV_SPIN, MAX_FWD_SPIN);
}

void half_direct_right(void){
  run_motor(MAX_FWD_SPIN, HALF_REV_SPIN);
}

void half_direct_left(void){
  run_motor(HALF_REV_SPIN, MAX_FWD_SPIN);
}

void split_right(void){
  run_motor(HALF_REV_SPIN, HALF_REV_SPIN);
}

void split_left(void){
  run_motor(HALF_REV_SPIN, HALF_REV_SPIN);
}

// -------------------------- Super runnning pattern ---------------------------
void stride_front(void){
  while (!check_Both_White()) go_straight();
}

void stride_right(int num){
  while (!check_Both_White()) back_straight();

  int i;
  for (i = 0; i < num; i++){
    while ( left_isWhite()) toward_right[2](); // turn
    while (!left_isWhite()) toward_right[2](); // turn
  }
  while (!check_Both_White()) toward_right[4](); // direct
}

void stride_left(int num){
  while (!check_Both_White()) back_straight();

  int i;
  for (i = 0; i < num; i++){
    while ( right_isWhite()) toward_left[2](); // turn
    while (!right_isWhite()) toward_left[2](); // turn
  }
  while (!check_Both_White()) toward_left[4](); // direct
}

void finish_turn(void){
  back_straight();
  Wait(1000);
  while ( right_isWhite()) direct_right();
  while (!right_isWhite()) direct_right();
  while (check_Both_sensor() != 3){
    if (check_Both_sensor == 0) back_straight();
    if (check_Both_sensor == 1) split_left();
    if (check_Both_sensor == 2) split_right();
  }
}

// -------------------------- Sensor code --------------------------------------
int read_sensor(unsigned char ch){
  if (ADRead(ch) < THRESHOLD) return 1;
  else return 0;
}

int left_isWhite(void){
  return read_sensor(0);
}

int right_isWhite(void){
  return read_sensor(1);
}

int check_Both_sensor(void){
  if ( left_isWhite() &&  right_isWhite()) return 0;  // 0 0
  if ( left_isWhite() && !right_isWhite()) return 1;  // 0 1
  if (!left_isWhite() &&  right_isWhite()) return 2;  // 1 0
  if (!left_isWhite() && !right_isWhite()) return 3;  // 1 1
}

int check_Both_Black(void){
  if (check_Both_sensor() == 3) return 1;
  else return 0;
}

int check_Both_White(void){
  if (check_Both_sensor() == 0) return 1;
  else return 0;
}

// ---------- Control pattern --------------------------------------------------
void line_control_LR(int mode){
  if (check_Both_sensor() == 0) go_straight();
  if (check_Both_sensor() == 1) toward_right[mode]();
  if (check_Both_sensor() == 2) toward_left[mode]();
  if (check_Both_sensor() == 3) go_straight();
}

void line_control_L(int mode){
  if (left_isWhite()) toward_right[mode]();
  else toward_left[mode]();
}

void line_control_R(int mode){
  if (right_isWhite()) toward_left[mode]();
  else toward_right[mode]();
}

void stride_Line(int mode){
  if (mode == 0) stride_front();
  if (mode == 1) stride_right(2);
  if (mode == 2) stride_right(1);
  if (mode == 3) stride_left(2);
  if (mode == 4) stride_left(1);
  if (mode == 5) finish_turn();
}

// -------------------------- Read select mode----------------------------------
int trace_mode_reader(char* selected_mode){
  if (!strcmp(selected_mode, "curv"))  return 1;
  if (!strcmp(selected_mode, "turn"))  return 2;
  if (!strcmp(selected_mode, "half"))  return 3;
  if (!strcmp(selected_mode, "drct"))  return 4;
  if (!strcmp(selected_mode, "split")) return 5;

  ERROR();
}

int stride_mode_reader(char* selected_mode){
  if (!strcmp(selected_mode,"front"))  return 0;
  if (!strcmp(selected_mode,"right+")) return 1;
  if (!strcmp(selected_mode,"rightT")) return 2;
  if (!strcmp(selected_mode,"left+"))  return 3;
  if (!strcmp(selected_mode,"leftT"))  return 4;
  if (!strcmp(selected_mode,"turn"))   return 5;

  ERROR();
}

// -------------------------- Match control pattern & selected mode ------------
void linetrace_LR(char* selected_mode){
  int mode = trace_mode_reader(selected_mode);
  while (!check_Both_Black()) line_control_LR(mode);
  stop_motor();
}

void linetrace_L(char* selected_mode){
  int mode = trace_mode_reader(selected_mode);
  while (!check_Both_Black()) line_control_L(mode);
  stop_motor();
}

void linetrace_R(char* selected_mode){
  int mode = trace_mode_reader(selected_mode);
  while (!check_Both_Black()) line_control_R(mode);
  stop_motor();
}

void on_the_Line(char* selected_mode){
  linetrace_LR("split");
  int mode = stride_mode_reader(selected_mode);
  stride_Line(mode);
  stop_motor();
}

// -------------------------- ERROR message ------------------------------------
void ERROR(void){
  stop_motor();
  int i;
  for (i = 0; i < 120; i++){
    LED((i%2)+1);
    Wait(500);
  }
}
