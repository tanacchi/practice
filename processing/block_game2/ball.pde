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
