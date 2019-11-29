use std::io;

enum Stone {
    White,
    Black,
    Space
}

impl Stone {
    fn to_char(self) -> char {
        match self {
            Stone::White => 'O',
            Stone::Black => 'X',
            Stone::Space => ' '
        }
    }
}

fn main() {
    const WIDTH:  usize = 9;
    const HEIGHT: usize = 9;
    let mut board = [[0; WIDTH]; HEIGHT];

    println!("Input x");
    let mut x = String::new();
    io::stdin().read_line(&mut x)
              .expect("Failed to read_line.");
    let x: usize = x.trim()
                  .parse()
                  .expect("Prease type a number.");

    println!("Input y");
    let mut y = String::new();
    io::stdin().read_line(&mut y)
              .expect("Failed to read_line.");
    let y: usize = y.trim()
                  .parse()
                  .expect("Prease type a number.");

    println!("x = {}, y = {}", x, y);

    board[y][x] = 1;

    for row in board.iter() {
        for elem in row.iter() {
            print!("{} ", elem);
        }
        println!();
    }
}
