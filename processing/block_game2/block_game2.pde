void settings()
{
  size(800, 800);
}

Bar bar = new Bar(color(255),
                  new PVector(mouseX, 700),
                  new PVector(100, 10));
Ball ball = new Ball(color(255),
                     new PVector(300, 500),
                     new PVector(10, 10),
                     new PVector(3, 3));
ArrayList<Ball> balls;

FloatList x_list;
FloatList y_list;
BlockArray blocks;
ArrayList<Item> items;

void setup()
{
  ellipseMode(CORNER);
  PVector size = new PVector(50, 30);
  PVector offset = new PVector(15, 20);
  
  x_list = new FloatList();
  y_list = new FloatList();
  for (int i = 0; i < 6; ++i) y_list.append((i + 1) * offset.y + i * size.y);
  for (int i = 0; i < 12; ++i) x_list.append((i + 1) * offset.x + i * size.x);
  
  balls = new ArrayList<Ball>();
  balls.add(ball);
  blocks = new BlockArray(x_list,
                          y_list,
                          size,
                          color(255));
  items = new ArrayList<Item>();
}

void draw()
{
  background(0);
  ArrayList<Ball> new_balls = new ArrayList<Ball>();
  
  bar.update();
  for (Ball ball : balls)
  {
    ball.update();
    Item new_item = blocks.update(ball);
    if (new_item != null)
      items.add(new_item);
    ball.hit(bar);
    for (int i = 0; i < items.size(); ++i)
    {
      HitPattern pattern = detect_hit_pattern(bar.pos, bar.size, items.get(i).pos, items.get(i).size);
      if (pattern == HitPattern.Absolute)
      {
        for (int j = 0; j < 5; ++j)
        {
          Ball new_ball = new Ball(ball);
          float theta = random(3.14);
          new_ball.vec.x *= cos(theta);
          new_ball.vec.y *= sin(theta);
          new_balls.add(new_ball);
        }
        items.remove(i);
        continue;
      }
      if (items.get(i).pos.y >= height)
      {
        items.remove(i);
        continue;
      }
    }
  }
  balls.addAll(new_balls);

  for (Item item : items)
  {
    item.update();
    item.draw();  
  }
  bar.draw();
  for (Ball ball : balls)
    ball.draw();
  blocks.draw();
}
