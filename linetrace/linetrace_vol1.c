#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

#define NULL 0

#define HIGH  10000
#define MIDLE  5000
#define LOW       0

#define WW 0
#define BB 3

enum Mode {
	MODE_INIT,
	MODE_READ,
	MODE_TRACE,
	MODE_OVER,
	MODE_SHIFT,
	MODE_ED
};

enum {
	LEFT,
	RIGHT
};

int task_init(const unsigned short MainCycle);
int task_read(int* position, int nextRun);
int task_shift(int* runOrder);
int task_ed();

void run_motor(int left, int right) {
	Mtr_Run_lv(right, -left, 0, 0, 0, 0);
}

int read_sensor(unsigned char ch) {
	return (ADRead(ch) > 200) ? 1 : 0;
}

int judge_position(int isLeftBlack, int isRightBlack) {
	if (!isLeftBlack && !isRightBlack) return 0;
	if (!isLeftBlack &&  isRightBlack) return 1;
	if ( isLeftBlack && !isRightBlack) return 2;
	if ( isLeftBlack &&  isRightBlack) return 3;
}

void Line_control(int* Param, int Position) {
	switch (Position) {
	case 0: run_motor(Param[0], Param[0]); break;
	case 1: run_motor(Param[0], Param[1]); break;
	case 2: run_motor(Param[1], Param[0]); break;
	case 3: run_motor(Param[0], Param[0]); break;
	}
	Wait(0.1);
}

void Line_over(int* Param, int Position) {
	switch (Position) {
	case 0: run_motor( Param[0],  Param[1]); break;
	case 1: run_motor( Param[1], -Param[0]); break;
	case 2: run_motor( Param[0], -Param[1]); break;
	case 3: run_motor( Param[0],  Param[1]); break;
	}
	Wait(0.1);
}

int traceList[][2] = {
		{HIGH, LOW},
		{HIGH, LOW},
		{HIGH, LOW},
		{HIGH, LOW},
		NULL
};

int overList[][2] = {
		{HIGH,  LOW},
		{ LOW, HIGH},
		{HIGH,  LOW},
		{ LOW, HIGH},
		NULL
};

int task_trace(int runOrder, int Position) {
	LED(1);
	Line_control(traceList[runOrder], Position);
	return (Position != BB) ? MODE_READ : MODE_OVER;
}

int task_over(int runOrder, int Position) {
	LED(2);
	Line_over(overList[runOrder], Position);
	return (Position != WW) ? MODE_READ : MODE_SHIFT;
}

int main() {
	int mode = 0;
	int Position;
	int runOrder = 0;
	int nextRun = MODE_TRACE;

	while (1) {
		switch (mode) {
		case MODE_INIT:
			mode = task_init(60);
			break;
		case MODE_READ:
			mode = task_read(&Position, nextRun);
			break;
		case MODE_TRACE:
			mode = task_trace(runOrder, Position);
			break;
		case MODE_OVER:
			mode = task_over(runOrder, Position);
			nextRun = MODE_OVER;
			break;
		case MODE_SHIFT:
			mode = task_shift(&runOrder);
			nextRun = MODE_TRACE;
			break;
		case MODE_ED:
			mode = task_ed();
			return 0;
		}
	}
}

int task_init(const unsigned short MainCycle) {
	Init(MainCycle);
	return MODE_READ;
}

int task_read(int* position, int nextRun) {
	*position = judge_position(read_sensor(LEFT), read_sensor(RIGHT));
	return nextRun;
}

int task_shift(int* runOrder) {
	(*runOrder)++;
	return (traceList[*runOrder] != NULL && overList[*runOrder] != NULL) ? MODE_READ : MODE_ED;
}

int task_ed() {
	run_motor(LOW, LOW);
	LED(3);
	return MODE_ED;
}
