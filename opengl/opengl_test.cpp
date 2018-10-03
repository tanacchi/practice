#include <GL/glut.h>

int main(int argc,char *argv[])
{
  /*初期化*/
  glutInit(&argc,argv);
  /*ウィンドウ作成*/
  glutCreateWindow(argv[0]);
  /*メインループ*/
  glutMainLoop();
  return 0;
}
