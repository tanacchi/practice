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
    println("Invalid function call on GameObject.draw !");
  }
  
  void update()
  {
    println("Invalid function call on GameObject.update !");
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
  boolean x_judge = lhs.pos.x-rhs.size.x <= rhs.pos.x && rhs.pos.x <= lhs.pos.x+lhs.size.x;
  boolean y_judge = lhs.pos.y-rhs.size.y <= rhs.pos.y && rhs.pos.y <= lhs.pos.y+lhs.size.y;
  return x_judge && y_judge;
}
