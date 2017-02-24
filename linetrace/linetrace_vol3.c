#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

#define NULL 0

#define FAST 10000
#define SLOW  5000
#define STOP     0

enum Mode{
	MODE_INIT,
	MODE_OP,
	MODE_READ,
	MODE_RUN,
	MODE_SHIFT,
	MODE_ED
};

enum Sensor_result{
	WW, WB, BW, BB
};

enum LR {
	LEFT,
	RIGHT
};

//          {{}, {}, {}, {}},

int param_list[][4][2] = {

		//WW            WB            BW            BB
		{{FAST, FAST}, {SLOW, FAST}, {FAST, SLOW}, {FAST, FAST}}, //  0.over start line
		{{STOP, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, SLOW}}, //  1.right edge until T
		{{FAST, STOP}, {FAST, SLOW}, {SLOW, FAST}, {FAST, FAST}}, //  2.over T zone
		{{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}}, //  3.trace until +
		{{FAST, FAST}, {FAST,-FAST}, {-FAST,FAST}, {FAST, FAST}}, //  4.over +
		{{FAST, FAST}, {FAST,-SLOW}, {-SLOW,FAST}, {FAST, FAST}}, //  5.trace until condenser
		{{FAST, FAST}, {SLOW, FAST}, {SLOW, FAST}, {FAST, FAST}}, //  6.enter condenser
		{{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}}, //  7.run between condenser
		{{FAST, FAST}, {SLOW, FAST}, {FAST, SLOW}, {FAST, FAST}}, //  8.get out condenser
		{{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}}, //  9.trace until +
		{{FAST, FAST}, {SLOW,-FAST}, {-FAST,SLOW}, {FAST, FAST}}, // 10.over +
		{{SLOW,-SLOW}, {SLOW,-SLOW}, {SLOW,-SLOW}, {SLOW,-SLOW}}, // 11.turn right until WB
		{{SLOW,-SLOW}, {SLOW,-SLOW}, {SLOW,-SLOW}, {SLOW,-SLOW}}, // 12.turn right until WW
		{{FAST, STOP}, {FAST, STOP}, {STOP, FAST}, {STOP, FAST}}, // 13.left edge until T
		{{FAST, STOP}, {FAST, STOP}, {FAST, STOP}, {FAST, STOP}}, // 14.turn right until WW
		{{FAST, FAST}, {FAST,-SLOW}, {-SLOW,FAST}, {FAST, FAST}}, // 15.trace until く
		{{STOP,-FAST}, {STOP,-FAST}, {STOP,-FAST}, {STOP,-FAST}}, // 16.toward right
		{{SLOW, FAST}, {FAST, SLOW}, {SLOW, FAST}, {FAST, SLOW}}, // 17.right edge until +
		NULL
};

//     {{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}}, // Normal trace

int order_preset[] = {
		WW, BB, WW, BB, WW, BB, WW, BB, WW, BB,
		WW, WB, WW, BB, WW, BB, WW, BB
};

int read_sensor(unsigned char ch);
void motor_run(int* param);
int judge_position();
int task_init(const unsigned short main_cycle);
int task_op();
int task_read(int* run_order, int* position);
int task_run(int run_order, int position);
int task_shift(int* run_order);
int task_ed();


int main() {
	int position, run_order = 0;
	int mode = MODE_INIT;

	while (1) {
		LED(run_order%4);
		switch (mode) {
		case MODE_INIT:
			mode = task_init(120);
			break;
		case MODE_OP:
			mode = task_op();
			break;
		case MODE_READ:
			mode = task_read(&run_order, &position);
			break;
		case MODE_RUN:
			mode = task_run(run_order, position);
			break;
		case MODE_SHIFT:
			mode = task_shift(&run_order);
			break;
		case MODE_ED:
			mode = task_ed();
			break;
		}
	}
	return 0;
}

int read_sensor(unsigned char ch) {
	return (ADRead(ch) > 200) ? 1 : 0;
}

void motor_run(int* param) {
	Mtr_Run_lv(param[1], -param[0], 0, 0, 0, 0);
	Wait(1);
}

int judge_position() {
	return (read_sensor(0) << 1 | read_sensor(1));
}

int task_init(const unsigned short main_cycle) {
	Init(main_cycle);
	return MODE_OP;
}

int task_op() {
	return (!getSW()) ? MODE_OP : MODE_READ;
}

int task_read(int* run_order,int* position) {
	*position = judge_position();
	return (*position != order_preset[*run_order]) ? MODE_RUN : MODE_SHIFT;
}

int task_run(int run_order ,int position) {  
	motor_run(param_list[run_order][position]);
	return MODE_READ;
}

int task_shift(int* run_order) {
	(*run_order)++;
	return (param_list[*run_order] != NULL) ? MODE_RUN : MODE_ED;
}

int task_ed() {
	static int stop[2] = {STOP, STOP};
	motor_run(stop);
	return MODE_ED;
}
