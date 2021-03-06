class Block extends Base
{
  Item item;
  Block(color c, PVector p, PVector s, boolean has_item)
  {
    super(c, p, s);
    item = has_item ? new Item(p, s) : null;
  }
  
  void update()
  {
  }
  
  void draw()
  {
    fill(col);
    rect(pos.x, pos.y, size.x, size.y);
    fill(0);
  }
}

class BlockArray
{
  ArrayList<Block> blocks;
  BlockArray(PVector nums, PVector size, PVector offset, color col)
  {
    blocks = new ArrayList<Block>();
    for (int i = 0; i < nums.x; ++i)
    {
      for (int j = 0; j < nums.y; ++j)
      {
        float x = (i + 1) * offset.x + i * size.x;
        float y = (j + 1) * offset.y + j * size.y;
        blocks.add(new Block(col, new PVector(x, y), size, random(1) >= 0.5));
      }
    }
  }
  
  Item update(Ball ball)
  {
    boolean hit_detected = false;
    for (int i = 0; i < blocks.size(); ++i)
    {
      hit_detected = ball.hit(blocks.get(i));
      if (hit_detected)
      {
        Item item = blocks.get(i).item; 
        blocks.remove(i);
        return item;
      }
    }
    return null;
  }
  
  void draw()
  {
    for (Block b : blocks)
    {
      b.draw();
    }
  }
}
