Ball ball;
Bar  bar;

void setup()
{
  size(800, 800);
  ball = new Ball(color(255, 255, 0), new PVector(width/2, height/2), 50.0);
  bar  = new Bar(color(0, 255, 255), new PVector(200, 20), 100);
}

void draw()
{
  background(0);
  draw_objects(ball, bar); 
  update_objects(ball, bar); 

  if (is_touching(ball, bar))
  {
    ball.object_color = color(255, 0, 0);
  }
  else 
  {
    ball.object_color = color(0, 255, 0);
  }
}
