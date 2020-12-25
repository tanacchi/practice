void settings()
{
  size(800, 800);
}

Bar bar = new Bar(color(255),
                  new PVector(mouseX, 700),
                  new PVector(100, 10));
Ball ball = new Ball(color(255),
                     new PVector(300, 500),
                     new PVector(10, 10),
                     new PVector(3, 3));

FloatList x_list;
FloatList y_list;;
BlockArray blocks;

void setup()
{
  ellipseMode(CORNER);
  float[] ahi = {20.0, 60.0, 100.0, 140.0};
  x_list = new FloatList(ahi);
  y_list = x_list.copy();
  blocks = new BlockArray(x_list,
                          y_list,
                          new PVector(30, 20),
                          color(255));
}

void draw()
{
  background(0);
  
  bar.update();
  ball.update();
  blocks.update(ball);
  
  ball.hit(bar);
  
  bar.draw();
  ball.draw();
  blocks.draw();
}
