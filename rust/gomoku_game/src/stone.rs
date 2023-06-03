#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Stone {
    White,
    Black,
    Space
}

impl Stone {
    pub fn to_char(&self) -> char {
        match self {
            Stone::White => 'O',
            Stone::Black => 'X',
            Stone::Space => ' '
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::stone::Stone;
    use pretty_assertions::assert_eq;
    use rstest::rstest;

    #[rstest]
    #[case(Stone::White, 'O')]
    #[case(Stone::Black, 'X')]
    #[case(Stone::Space, ' ')]
    fn test_conversion_stone_to_char(#[case] input: Stone, #[case] expected: char) {
      assert_eq!(input.to_char(), expected);
    }
}
