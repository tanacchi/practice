color background_color;

Ball ball;
Bar  bar;
Block blocks[];

void setup()
{
  size(800, 800);
  ellipseMode(CORNER);

  background_color = color(0);
  ball   = new Ball(color(255, 255, 0), new PVector(width/2-100, height/2), 50.0);
  bar    = new Bar(color(0, 255, 255), new PVector(200, 20), 100);
  
  color   block_color  = color(255, 0, 0);
  PVector block_size   = new PVector(60, 40);
  PVector block_num    = new PVector(8, 5);
  
  blocks = new Block[int(block_num.x*block_num.y)];
  for (int col = 0; col < block_num.y; col++)
    for (int row = 0; row < block_num.x; row++)
    {
      Block buff = new Block(block_color,
                             new PVector((block_size.x+block_offset.x)*row+block_offset.x, (block_size.y+block_offset.y)*col), 
                             block_size);
      blocks[col*int(block_num.x)+row] = buff;
    }
  ball.vel = new PVector(-5, -5);
}

void draw()
{
  //
  //  Object draw & update
  //
  background(background_color);
  draw_objects(ball, bar);
  draw_blocks(blocks);
  update_objects(ball, bar);

  //
  //  Ball hit 
  //
  if (is_touching(ball, bar))
  {
    ball.pos.y = bar.pos.y - ball.size.y;
    ball.vel.y = -abs(ball.vel.y);
    //ball.vel.mult(1.1);
  }
  
  for (Block block : blocks)
  {
    if (!block.is_active)
      continue;
    if (is_touching(ball, block))
    {
      block.kill();
      if (!(   block.pos.x                < ball.get_old_center().x 
            && block.pos.x + block.size.x > ball.get_old_center().x))  // From out of x-range
      {
        ball.vel.x *= -1; 
      }
      else if (!(   block.pos.y                < ball.get_old_center().y 
                 && block.pos.y + block.size.y > ball.get_old_center().y))  // From out of y-range
      {
        ball.vel.y *= -1;
      }
      else {
        ball.vel.mult(-1);
      }
      break;
    }
  }
  
  
}
