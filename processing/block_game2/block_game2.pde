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
  
  blocks = new BlockArray(x_list,
                          y_list,
                          size,
                          color(255));
  items = new ArrayList<Item>();
}

void draw()
{
  background(0);
  
  bar.update();
  ball.update();
  Item new_item = blocks.update(ball);
  if (new_item != null)
    items.add(new_item);
  ball.hit(bar);
  for (Item item : items)
  {
    item.update();
    item.draw();
  }

  
  bar.draw();
  ball.draw();
  blocks.draw();
}
