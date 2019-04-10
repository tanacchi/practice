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
  PVector block_size   = new PVector(50, 30);
  PVector block_offset = new PVector(10, 10);
  PVector block_num    = new PVector(5, 3);
  
  blocks = new Block[int(block_num.x*block_num.y)];
  for (int col = 0; col < block_num.y; col++)
    for (int row = 0; row < block_num.x; row++)
    {
      Block buff = new Block(block_color, new PVector((block_size.x+block_offset.x)*row, (block_size.y+block_offset.y)*col), block_size);
      blocks[col*int(block_num.x)+row] = buff;
    }
  ball.vel = new PVector(-2, -2);
}

void draw()
{
  background(background_color);
  draw_objects(ball, bar);
  draw_blocks(blocks);
  
  update_objects(ball, bar);

  if (is_touching(ball, bar))
  {
    ball.object_color = color(255, 0, 0);
    ball.pos.y = bar.pos.y - ball.size.y;
    ball.vel.y = -abs(ball.vel.y);
  }
}
