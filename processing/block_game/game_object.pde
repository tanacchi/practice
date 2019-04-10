class GameObject
{
  color   object_color;
  PVector pos, vel;
  PVector size;
  
  GameObject(color c, PVector p, PVector s)
  {
    object_color = c;
    pos  = p;
    vel  = new PVector();
    size = s;
  }
  
  void draw()
  {
    println("Invalid function call !");
  }
  
  void update()
  {
    pos.x += vel.x;
    pos.y += vel.y;
  }
}

void update_objects(GameObject... objects)
{
  for (GameObject object : objects)
  {
    object.update();
  }
}

void draw_objects(GameObject... objects)
{
  for (GameObject object : objects)
  {
    object.draw();
  }
}

boolean is_touching(GameObject lhs, GameObject rhs)
{
  boolean x_judge = lhs.pos.x-lhs.size.x/2-rhs.size.x <= rhs.pos.x && rhs.pos.x <= lhs.pos.x+lhs.size.x/2;
  boolean y_judge = lhs.pos.y-lhs.size.y/2-rhs.size.y <= rhs.pos.y && rhs.pos.y <= lhs.pos.y+lhs.size.y/2;
  return x_judge && y_judge;
}
