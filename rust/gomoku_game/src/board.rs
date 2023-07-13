use crate::stone::Stone;
use crate::coord::Coord;

pub struct Board {
  stones: Vec<Vec<Stone>>,
}

impl Board {
  pub fn new(width: usize, height: usize) -> Self {
    Self {
      stones: vec![vec![Stone::Space; width]; height]
     }
  }
}

pub trait GomokuBoard {
}
