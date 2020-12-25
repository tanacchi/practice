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


HitPattern detect_hit_pattern(PVector lhs_pos, PVector lhs_size, PVector rhs_pos, PVector rhs_size)
{
  boolean x_judge = lhs_pos.x-rhs_size.x <= rhs_pos.x && rhs_pos.x <= lhs_pos.x+lhs_size.x;
  boolean y_judge = lhs_pos.y-rhs_size.y <= rhs_pos.y && rhs_pos.y <= lhs_pos.y+lhs_size.y;
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
