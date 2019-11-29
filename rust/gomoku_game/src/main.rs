use std::io;

const WIDTH:  usize = 9;
const HEIGHT: usize = 9;

enum Stone {
    White,
    Black,
    Space
}

impl Stone {
    fn to_char(&self) -> char {
        match self {
            Stone::White => 'O',
            Stone::Black => 'X',
            Stone::Space => ' '
        }
    }
}

fn get_hand(msg: &str) -> usize {
    println!("{}", msg);
    let mut hand = String::new();
    io::stdin().read_line(&mut hand)
               .expect("Failed to read_line.");
    hand.trim()
        .parse::<usize>()
        .expect("Prease type a number.")
}

fn show_board(board: &[[Stone; WIDTH]; HEIGHT]) {
    for row in board.iter() {
        for elem in row.iter() {
            print!("{} ", elem.to_char());
        }
        println!();
    }
}

fn main() {
    let mut board = [[Stone::White; WIDTH]; HEIGHT];

    loop {
        let x = get_hand("Input x: ");
        let y = get_hand("Input y: ");
        println!("x = {}, y = {}", x, y);

        // board[y][x] = 1;
        board[y][x] = Stone::Black;
        show_board(&board)
    }
}
