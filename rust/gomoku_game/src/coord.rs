pub struct Coord {
  pub x: i32,
  pub y: i32,
}

impl From<Directions> for Coord {
    fn from(dir: Directions) -> Self {
        match dir {
          Directions::Up => Coord { x: 0, y: -1 },
          Directions::UpRight => Coord { x: 1, y: -1 },
          Directions::Right => Coord { x: 1, y: 0 },
          Directions::DownRight => Coord { x: 1, y: 1 },
          Directions::Down => Coord { x: 0, y: 1 },
          Directions::DownLeft => Coord { x: -1, y: 1 },
          Directions::Left => Coord { x: -1, y: 0 },
          Directions::UpLeft => Coord { x: -1, y: -1 },
        }
    }
}

#[derive(Clone)]
pub enum Directions {
  Up,
  UpRight,
  Right,
  DownRight,
  Down,
  DownLeft,
  Left,
  UpLeft,
}

impl Directions {

  pub fn iter() -> impl Iterator<Item = Directions> {
    [
      Directions::Up,
      Directions::UpRight,
      Directions::Right,
      Directions::DownRight,
      Directions::Down,
      Directions::DownLeft,
      Directions::Left,
      Directions::UpLeft,
    ]
    .iter()
    .cloned()
  }
}

#[cfg(test)]
mod tests {
    use crate::coord::Coord;
    use crate::coord::Directions;
    use pretty_assertions::assert_eq;
    use rstest::rstest;

    #[rstest]
    #[case()]
    fn test_all_directions_to_coords() {
      let coords = Directions::iter().map(|d| Coord::from(d));
      assert_eq!(coords.count(), 8);
    }
}
