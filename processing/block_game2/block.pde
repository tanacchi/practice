class Block extends Base
{
  Block(color c, PVector p, PVector s)
  {
    super(c, p, s);
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
  BlockArray(FloatList x_list, FloatList y_list, PVector size, color col)
  {
    blocks = new ArrayList<Block>();
    for (float x : x_list)
    {
      for (float y : y_list)
      {
        blocks.add(new Block(col, new PVector(x, y), size));
      }
    }
  }
  
  void update(Ball ball)
  {
    boolean hit_detected = false;
    for (int i = 0; i < blocks.size(); ++i)
    {
      hit_detected = ball.hit(blocks.get(i));
      if (hit_detected)
      {
        blocks.remove(i);
        break;
      }
    }
  }
  
  void draw()
  {
    for (Block b : blocks)
    {
      b.draw();
    }
  }
}
