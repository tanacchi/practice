class Ball extends Base
{
  PVector vec;
  PVector prev_pos;
  
  Ball(color c,
       PVector p,
       PVector s,
       PVector v)
  {
    super(c, p, s);
    vec = v.copy();
    prev_pos = p.copy();
  }
  
  Ball(Ball ball)
  {
    super(ball.col, ball.pos, ball.size);
    vec = ball.vec.copy();
    prev_pos = ball.prev_pos.copy();
  }
  
  void update()
  {
    if (pos.x <= 0 || width <= pos.x)
    {
      vec.x = - vec.x;
    }
    if (pos.y <= 0 || height <= pos.y)
    {
      vec.y = - vec.y;
    }
    prev_pos = pos.copy();
    pos.x += vec.x;
    pos.y += vec.y;
  }
  
  void draw()
  {
    fill(col);
    ellipse(pos.x, pos.y, size.x, size.y);
    fill(0);
  }
  
  boolean hit(Base obj)
  {
    if (detect_hit_pattern(pos, size, obj.pos, obj.size) != HitPattern.Absolute)
      return false;
    HitPattern pattern = detect_hit_pattern(prev_pos, size, obj.pos, obj.size);
    switch (pattern)
    {
      case Horizontal:
        vec.x = - vec.x;
        break;
      case Vertical:
        vec.y = - vec.y;
        break;
      case None:
        vec.x = - vec.x;
        vec.y = - vec.y;
        break;
      default:
        break;
    }
    return true;
  }
}

class BallArray
{
  color col;
  ArrayList<Ball> balls;
  BallArray(color c, PVector p, PVector s, PVector v)
  {
    balls = new ArrayList<Ball>();
    col = c;
    Ball first_ball = new Ball(c, p, s, v);
    balls.add(first_ball);
  }
 
  void update()
  {
    for (int i = 0; i < balls.size(); ++i)
    {
      balls.get(i).update();
      if (balls.get(i).pos.y >= height)
        balls.remove(i);
    }
  }
  
  void draw()
  {
    for (Ball ball : balls)
      ball.draw();
  }
  
  int count()
  {
    return balls.size();
  }
  
  ArrayList<Ball> clone()
  {
    return new ArrayList<Ball>(balls);
  }
  
  void multiply(int num)
  {
    ArrayList<Ball> new_balls = new ArrayList<Ball>();
    for (Ball ball : balls)
    {
      for (int i = 0; i < num; ++i)
      {
        Ball new_ball = new Ball(ball);
        float theta = random(PI*2);
        new_ball.vec.x *= cos(theta);
        new_ball.vec.y *= sin(theta);
        new_balls.add(new_ball);
      }
    }
    balls.addAll(new_balls);
  }
}
