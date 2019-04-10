class Ball extends GameObject
{
  Ball(color c, PVector p, float radius)
  {
    super(c, p, new PVector(radius, radius));
  }
  
  void update()
  {
    pos.add(vel);
    if (pos.x < 0) 
    {
      pos.x = 0;
      vel.x = abs(vel.x);
    }
    else if (pos.x > width)
    {
      pos.x = width;
      vel.x = -abs(vel.x);
    }
    if (pos.y < 0)
    {
      pos.y = 0;
      vel.y = abs(vel.y);
    }
    else if (pos.y > height)
    {
      pos.y = height;
      vel.y = -abs(vel.y);
    }
  }
  
  void draw()
  {
    fill(object_color);
    ellipse(pos.x, pos.y, size.x, size.y);
    fill(0);
  }
}

class Bar extends GameObject
{
  Bar(color c, PVector s, int under_offset)
  {
    super(c, new PVector(mouseX, height-under_offset), s);
  }
  
  void draw()
  {
    fill(object_color);
    rect(pos.x, pos.y, size.x, size.y);
    fill(0);
  }
  
  void update()
  {
    pos.x = mouseX - size.x/2;
    pos.y = mouseY - size.y/2;
  }
}
