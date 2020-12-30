class Item extends Base
{
  PVector vec;
  Item(PVector p, PVector s)
  {
    super(color(0, 0, 255), p, s);
    vec = new PVector(0, 1);
  }
  
  void update()
  {
    pos.y += vec.y;
  }
  
  void draw()
  {
    fill(col);
    rect(pos.x, pos.y, size.x, size.y, 5);
    fill(0);
  }
}
