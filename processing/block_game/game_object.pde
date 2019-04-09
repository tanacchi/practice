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
