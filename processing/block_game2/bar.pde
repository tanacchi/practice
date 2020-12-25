class Bar extends Base
{
  Bar(color c, PVector p, PVector s)
  {
    super(c, p, s);
  }
  
  void update()
  {
    pos.x = mouseX;
  }
  
  void draw()
  {
    fill(col);
    rect(pos.x, pos.y, size.x, size.y);
    fill(0);
  }
}
