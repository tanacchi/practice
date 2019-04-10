class Ball extends GameObject
{
  Ball(color c, PVector p, float radius)
  {
    super(c, p, new PVector(radius, radius));
  }
  
  void update()
  {
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
    fill(object_color);
    rect(pos.x, pos.y, size.x, size.y);
    fill(0);
  }
  
  void update()
  {
    if (!is_active)
    {
      object_color = color(background_color);
    }
  }
}

void draw_blocks(Block[] blocks)
{
  for (Block block : blocks)
  {
    draw_objects(block);
  }
}

void update_blocks(Block[] blocks)
{
  for (Block block : blocks)
  {
    update_objects(block);
  }
}
