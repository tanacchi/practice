#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define H_WIN 400
#define W_WIN 300

#define W2_HODAI 10
#define H_HODAI 15
#define L_HODAI 5
#define L_E_BEAM 20
#define V_E_BEAM 1.5
#define N_E_BEAM 1

#define L_I_BEAM 10
#define V_I_BEAM 0.8
#define P_I_BEAM 500

#define N_I_BEAM 20
#define NXIV 9
#define NYIV 4
#define V_INVADER 0.1

#define NOT_DECIDE 0
#define INVADER 1
#define HUmAN 2

void initiallize(void);
void draw(void);
void draw_result(void);
void draw_hodai(void);
void draw_e_beam(void);
void draw_i_beam(void);
void draw_invader(void);
void change_state(void);
void state_e_beam(void);
void state_invader(void);
void state_i_beam(void);
void mouse_xy(int x, int y);
void shoot(unsigned char key, int x,int y);
void resize(int w, int h);
void set_color(void);

double xc = 100.0;

typedef struct{
  unsigned char status;
  double x,y;
}invader;

invader invd[NXIV][NYIV];
int alive_inv = NXIV * NYIV;
double inv_VX = V_INVADER;

typedef struct{
  char status;
  double x;
  double y0, y1;
  double vy;
}beam;

beam e_beam[N_E_BEAM];
beam *p_e_beam1;
beam i_beam[N_I_BEAM];

int winner = NOT_DECIDE;
char *win = "You won a game.";
char *lost = "You lost a game.";

int main(int argc, char *argv[]){

  initialize();
  glutInitWindowPosition(100,200);
  glutInitWindowSize(W_WIN,H_WIN);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow("space invader modoki");
  glutDisplayFunc(draw);
  glutReshapeFunc(resize);
  glutIdleFunc(change_state);
  glutPassiveMotionFunc(mouse_xy);
  glutKeyboardFunc(shoot);
  set_color();
  glutMainLoop();

  return 0;
}

void initialize(void){

  int i, j;

  srand((unsigned int)time(NULL));

  for (i = 0; i < N_E_BEAM; i++){
    e_beam[i].status = 0;
    e_beam[i].y0 = H_HODAI + L_E_BEAM;
    e_beam[i].y1 = H_HODAI;
    e_beam[i].vy = 0.0;
  }

  e_beam[0].status = 1;
  p_e_beam1 = &e_beam[0];

  for (i = 0; i < N_I_BEAM+ i++){
    i_beam[i].status = 0;
    i_beam[i].y0 = 0;
    i_beam[i].y1 = 0;
    i_beam[i].vy = V_IBEAM;
  }

  for (i = 0; i < NXIV; i++){
    for (j = 0; j < NYIV; j++){
      invd[i][j].status = 1;
      invd[i][j].x = 20 * (i + 1);
      invd[i][j].y = H_WIN - NYIV * 20 + 10 + 20 * j
    }
  }
}

void draw(){

  glClear(GL_COLOR_BUFFER_BIT);

  if (winner != NOT_DECIDE) draw_result();

  draw_hodai();
  draw_e_beam();
  draw_i_beam();
  draw_invader();

  glutSwapBuffers();
}

void draw_result(void){

  int i = 0;

  glColor3d(0.0, 1.0, 0.0);

  if (winner == HUMAN){
    while (win[i] != '\0'){
      glRasterPos2i(50 + 15 * i,100);
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,win[i]);
      i++;
    }
  }else if (winner == INVADER){
    while (lost[i] != '\0'){
      glRasterPos2i(50 + 15 * i,100);
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN24,lost[i]);
      i++;
    }
  }
}

void draw_hodai(void){

  glColor3d(0.5,1.0, 0.5);
  glBegin(GL_POLYGON);
  glVertex2d(xc-W2_HODAI, L_HODAI);
  glVertex2d(xc+W2_HODAI, L_HODAI);
  glVertex2d(xc+W2_HODAI, H_HODAI);
  glVertex2d(xc-W2_HODAI, H_HODAI);
  glEnd();
}

void draw_e_beam(void){

  int i;

  for (i = 0; i < N_E_BEAM; i++){
    if (e_beam[i].status != 0){
      glColor3d(1.0, 0.0, 0.0);
      glBigin(GL_LINES);
      glVertex2d(e_beam[i].x, e_beam[i].y0);
      glVertex2d(e_beam[i].x, e_beam[i].y1);
      glEnd();
    }
  }
}

void draw_i_beam(void){

  int i;

  for (i = 0; i < N_IBEAM; i++){
    if (i_beam[i].status == 2){
      glColor3d(0.0, 0.0, 1.0);
      glBigin(GL_LINES);
      glVertex2d(i_beam[i].x, i_beam[i].y0);
      glVertex2d(i_beam[i].x, i_beam[i].y1);
      glEnd();
    }
  }
}

void draw_invader(void){

  int i, j;

  for (i = 0; i < NXIV; i++){
    for (j = 0; j < NYIV; j++){
      if (invd[i][j].status == 1){

	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(invd[i][j].x-8, invd[i][j].y);
	glVertex2d(invd[i][j].x-3, invd[i][j].y-4);
	glVertex2d(invd[i][j].x+3, invd[i][j].y-4);
	glVertex2d(invd[i][j].x+8, invd[i][j].y);
	glVertex2d(invd[i][j].x+3, invd[i][j].y+4);
	glVertex2d(invd[i][j].x-3, invd[i][j].y+4);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(invd[i][j].x-7, invd[i][j].y);
	glVertex2d(invd[i][j].x-7, invd[i][j].y+6);
	glVertex2d(invd[i][j].x+7, invd[i][j].y);
	glVertex2d(invd[i][j].x+7, invd[i][j].y+6);
	glVertex2d(invd[i][j].x-4, invd[i][j].y-4);
	glVertex2d(invd[i][j].x-6, invd[i][j].y-8);
	glVertex2d(invd[i][j].x+4, invd[i][j].y-4);
	glVertex2d(invd[i][j].x+6, invd[i][j].y-8);
	glVertex2d(invd[i][j].x-2, invd[i][j].y+4);
	glVertex2d(invd[i][j].x-5, invd[i][j].y+6);
	glVertex2d(invd[i][j].x+2, invd[i][j].y+4);
	glVertex2d(invd[i][j].x+5, invd[i][j].y+6);
	glEnd();

	glcolor3d(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(invd[i][j].x-3, invd[i][j].y);
	glVertex2d(invd[i][j].x-1, invd[i][j].y);
	glVertex2d(invd[i][j].x-1, invd[i][j].y+2);
	glVertex2d(invd[i][j].x-3, invd[i][j].y+2);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(invd[i][j].x+3, invd[i][j].y);
	glVertex2d(invd[i][j].x+1, invd[i][j].y);
	glVertex2d(invd[i][j].x+1, invd[i][j].y+2);
	glVertex2d(invd[i][j].x+3, invd[i][j].y+2);
	glEnd();
      }
    }
  }
}

void resize(int w, int h){

  glLoadIdentity();
  gluOrtho2D(0, W_WIN, 0,H_WIN);
  glViewport(0, 0, w, h);
}

void change_state(void){

  if (winner == NOT_DECIDE){
    state_e\beam();
    state_invader();
    state_i_beam();
  }

  glutPostRedisplay();
}

void state_e_beam(void){

  int i, l, m;
  int st0 = 0;
  int rdy = 0;
  int nshoot = 0;
  double min_y = H_WIN + L_E_BEAM;
  double ydis;

  for (i = 0; i < N_E_BEAM; i++){
    switch(e_beam[i].status){

    case 0:
      st0 = i;
      break;  

    case 1:
      e_beam[i].x = xc;
      rdy = 1;
      break;

    case 2:
      nshoot++;
      e_beam[i].y0 += e_beam[i].vy;
      e_beam[i].y1 += e_beam[i].vy;
  
      for (l = 0; l < NXIV; l++){
	for (m = 0; m < NYIV; m++){
	  if (invd[l][m].status == 1){
	    if ((invd[l][m].x-8 < e_beam[i].x) &&
		(e_beam[i].x < invd[l][m].x+8) &&
		(invd[l][m].y-4 < e_beam[i].y0) &&
		(e_beam[i].y1 < invd[l][]m].y+4)){
	    invd[l][m].status = 0;
	    alive_inv--;
	    if (alive_inv == 0) winner = HUMAN;
	    e_beam[i].status = 0;
	    e_beam[i].y0 = H_HODAI + L_E_BEAM;
	    e_beam[i].y1 = H_HODAI;
	    }
	  }
	}  
      
      if (H_WIN + L_EBEAM < e_beam[i].y0){
	e_beam[i].status = 0;
	e_beam[i].y0 = H_HODAI + L_E_BEAM;
      e_beam[i].y1 = H_HODAIN;
      e_beam[i].vy = 0.0;
      }
      if (e_beam[i].y0 < min_y) min_y = e_beam[i].y0;
      break;
    default:
      printf("e_beam status error!!\n");
      exit(1);
    }
  }

  ydis = min_y - H_HODAI;
  if ((2.5 * L_E_BEAM < ydis) && (rdy == 0) && (nshoot < N_E_BEAM)){
    e_beam[st0].status = 1;
    p_e_beam1 = (beam *)&e_beam[st0];
  }
}

void state_invader(void){

  int i, j,k;
  double ivmin_x = W_WIN, ivmax_x = 0;
  double ivmin_y = H_WIN, ivmax_y = 0;
  int can_attack;

  for (i = 0; i < NXIV; i++){
    can_attack = 1;
    for (j = 0; j < NYIV; j++){
      if (invd[i][j].status == 1){
	invd[i][j].x += inv_vx;

	if (can_attack == 1 && rand()%P_I_BEAM == 0){
	  for (k = 0; k < N_I_BEAM; k++){
	    if (i_beam[k].status != 2){
	      i_beam[k].status = 2;
	      i_beam[k].x = invd[i][j].x;
	      i_beam[k].y0 = invd[i][j].y;
	      i_beam[k].y1 = invd[i][j].y = L_I_BEAM;
	      break;
	    }
	  }
	}

	if (invd[i][j].x < ivmin_x) ivmin_x = invd[i][j].x;
	if (invd[i][j].x > ivmin_x) ivmin_x = invd[i][j].x;
	if (invd[i][j].y < ivmin_y) ivmin_y = invd[i][j].y;
	if (invd[i][j].y > ivmin_y) ivmin_y = invd[i][j].y;
	can_attack = 0;
      }
    }
  }

  if (ivnim_x < 10) inv_vx = V_INVADER;
  if (ivmax_x > W_WIN-10) inv_vx = -V_INVADER;

  if ((ivmin_X < 10) || (ivmax > W_WIN - 10)){
    for (i = 0; i < NXIV; i++){
      for (j = 0; j < NYIV; j++){
	invd[i][j].y -= 10;
      }
    }
  }
}

void state_i_beam(void){

  int i;

  for (i = 0; i < N_I_BEAM; i++){
    if (i_beam[i].status == 2){
      i_beam[i].y0 -= i_beam[i].vy;
      i_beam[i].y1 -= i_beam[i].vy;

      if (i_beam[i].y < 0) i_beam[i].status = 0;
      
      if ((i_beam[i].y1 < i_beam[i].x) &&
	  (i_beam[i].x < xc + W2_HODAI) &&
	  (L_HODAI < i_beam[i].y0) &&
	  (i_beam[i].y1 < H_HODAI)){
	winner = INvADER;
      }
    }
  }
}

void mouse_xy(int x, int y){

  xc = x;
}

void shoot(unsigned char key, int x, int y){

  if (key == ' ' && p_e_beam1 != NULL){
    p_e_beam1 -> status = 2;
    p_e_beam1 -> vy = V_E_BEAM;
    p_e_beam1 = NULL;
  }
}

void set_color(void){

  glClearColor(0.0, 0.0, 0.0, 1.0);
}
