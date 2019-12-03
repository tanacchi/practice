use std::io;

const WIDTH:  usize = 9;
const HEIGHT: usize = 9;

#[derive(Clone, Copy, PartialEq)]
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
        .expect("Prease type a number.") - 1
}

fn show_board(board: &[Stone; WIDTH*HEIGHT]) {
    println!("---------------------");
    for i in (0..board.len()).step_by(WIDTH) {
        print!("| ");
        for x in i..(i + WIDTH) {
            print!("{} ", board[x].to_char());
        }
        println!("|");
    }
    println!("---------------------");
}

fn calc_index(x: usize, y: usize) -> usize {
    y * WIDTH + x
}

fn insert_stone(board: &mut [Stone; WIDTH*HEIGHT], (x, y): (usize, usize), stone: Stone) {
    let index: usize = calc_index(x, y);
    if board[index] != Stone::Space {
        println!("Invalid position.");
    } else {
        board[index] = stone;
    }
}

fn is_game_finished(board: &[Stone; WIDTH*HEIGHT]) -> bool {
    true
}

fn main() {
    let mut board = [Stone::Space; WIDTH*HEIGHT];
    let mut active_stone = Stone::White;

    while is_game_finished(&board) {
        let x = get_hand("Input x: ");
        let y = get_hand("Input y: ");
        println!("x = {}, y = {}", x, y);

        insert_stone(&mut board, (x, y), active_stone);
        show_board(&board);

        active_stone = match active_stone {
            Stone::White => Stone::Black,
            Stone::Black => Stone::White,
            Stone::Space => Stone::Space
        }
    }
}
