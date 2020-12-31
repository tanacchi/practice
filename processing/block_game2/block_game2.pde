void settings()
{
  size(800, 800);
}

Bar bar;
BallArray balls;
BlockArray blocks;
ArrayList<Item> items;

void setup()
{
  ellipseMode(CORNER);
  
  bar = new Bar(color(255), new PVector(mouseX, 700), new PVector(100, 10));
  
  PVector block_nums = new PVector(12, 6);
  PVector block_size = new PVector(50, 30);
  PVector block_offset = new PVector(15, 20);
  blocks = new BlockArray(block_nums, block_size, block_offset, color(255));


  balls = new BallArray(color(255),
                        new PVector(300, 500),
                        new PVector(10, 10),
                        new PVector(3, 3));
  items = new ArrayList<Item>();
}

void draw()
{
  background(0);
  println(balls.count());
  
  bar.update();
  balls.update();
  for (Ball ball : balls.clone())
  {
    Item new_item = blocks.update(ball);
    if (new_item != null) items.add(new_item);
  }
  for (int i = 0; i < items.size(); ++i)
  {
    HitPattern pattern = detect_hit_pattern(bar.pos, bar.size, items.get(i).pos, items.get(i).size);
    if (pattern == HitPattern.Absolute)
    {
      balls.multiply(2);
      items.remove(i);
      break;
    }
    if (items.get(i).pos.y >= height)
    {
      items.remove(i);
      continue;
    }
  }

  for (Ball ball : balls.clone())
      ball.hit(bar);

  for (Item item : items)
  {
    item.update();
    item.draw();  
  }
  bar.draw();
  balls.draw();
  blocks.draw();
}
