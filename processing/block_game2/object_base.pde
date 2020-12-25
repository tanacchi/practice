public class Base
{
  color col;
  PVector pos;
  PVector size;

  Base(color c, PVector p, PVector s)
  {
    col = c;
    pos = p.copy();
    size = s.copy();
  }
  
  void update()
  {
    println("Base::update called.");
  }
  
  void draw()
  {
    println("Base::draw called.");  
  }
}

public enum HitPattern
{
  None,
  Horizontal,
  Vertical,
  Absolute,
}


//        |         |
//        |    V    |
//        |         |    
// -------           -------
//    H   [ Absolute]   H
// -------           -------
//        |         |
//        |    V    |
//        |         |


HitPattern detect_hit_pattern(Base lhs, Base rhs)
{
  boolean x_judge = lhs.pos.x-rhs.size.x <= rhs.pos.x && rhs.pos.x <= lhs.pos.x+lhs.size.x;
  boolean y_judge = lhs.pos.y-rhs.size.y <= rhs.pos.y && rhs.pos.y <= lhs.pos.y+lhs.size.y;
  if (x_judge)
  {
    if (y_judge)
    {
      return HitPattern.Absolute; 
    }
    else
    {
      return HitPattern.Vertical; 
    }
  }
  else
  {
    if (y_judge)
    {
      return HitPattern.Horizontal; 
    }
    else
    {
      return HitPattern.None; 
    }
  }
}
