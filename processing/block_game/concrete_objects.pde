class Ball extends GameObject
{
  PVector old_pos;
  Ball(color c, PVector p, float radius)
  {
    super(c, p, new PVector(radius, radius));
    old_pos = new PVector();
  }
  
  void update()
  {
    old_pos = pos.copy();
    pos.add(vel);
    if (pos.x < 0) // Left-wall reflection
    {
      pos.x = 0;
      vel.x = abs(vel.x);
    }
    else if (pos.x+size.x > width) // Right-wall reflection
    {
      pos.x = width - size.x;
      vel.x = -abs(vel.x);
    }
    if (pos.y < 0) // Upper-wall reflection
    {
      pos.y = 0;
      vel.y = abs(vel.y);
    }
  }
  
  void draw()
  {
    fill(object_color);
    ellipse(pos.x, pos.y, size.x, size.y);
    fill(0);
  }
  
  PVector get_old_center()
  {
    return new PVector(pos.x + size.x/2, pos.y + size.y/2);
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
  }
}

class Block extends GameObject
{
  boolean is_active;
  Block(color c, PVector p, PVector s)
  {
    super(c, p, s);
    is_active = true;
  }
  
  void draw()
  {
    if (is_active)
    {
      fill(object_color);
      rect(pos.x, pos.y, size.x, size.y);
      fill(0);
    }
  }
  
  void update()
  {
  }
  
  void kill()
  {
    is_active = false;
  }
}

void draw_blocks(Block[] blocks)
{
  for (Block block : blocks)
  {
    draw_objects(block);
  }
}
