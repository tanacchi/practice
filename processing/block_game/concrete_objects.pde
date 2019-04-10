class Ball extends GameObject
{
  Ball(color c, PVector p, float radius)
  {
    super(c, p, new PVector(radius, radius));
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
