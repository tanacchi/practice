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

void setup()
{
  ellipseMode(CORNER);
}

void draw()
{
  background(0);
  
  bar.update();
  ball.update();
  
  HitPattern pattern = detect_hit_pattern(ball, bar);
  if (pattern == HitPattern.Absolute)
  {
    Base prev_ball = new Base(ball.col, ball.prev_pos, ball.size);
    HitPattern prev_pattern = detect_hit_pattern(prev_ball, bar);
    ball.hit(prev_pattern);
  }
  
  bar.draw();
  ball.draw();
}
