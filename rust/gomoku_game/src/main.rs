mod stone;
mod input;

use stone::Stone;

use crate::input::get_hand;

const WIDTH:  usize = 9;
const HEIGHT: usize = 9;

fn show_board(board: &[Stone; WIDTH*HEIGHT]) {
    // chunks can be useful.
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

fn is_game_finished(board: &[Stone; WIDTH*HEIGHT], active_stone: &Stone) -> bool {
    fn extract_partial_line(board: &[Stone; WIDTH*HEIGHT], start_i: usize, step: usize) -> [&Stone; 5] {
        let target_line = board[start_i..].iter()
                                          .step_by(step)
                                          .collect::<Vec<_>>();
        // subvector can be useful.
        if target_line.len() >= 5 {
            let mut result_array = [&Stone::Space; 5];
            result_array.clone_from_slice(&target_line[..5]);
            result_array
        } else {
            [&Stone::Space; 5]
        }
    }

    for i in 0..board.len() {
        let horizontal_line = extract_partial_line(&board, i, 1);
        let vertival_line   = extract_partial_line(&board, i, WIDTH);
        let fall_left_line  = extract_partial_line(&board, i, WIDTH-1);
        let fall_right_line = extract_partial_line(&board, i, WIDTH+1);

        let is_finished = if horizontal_line.iter().all(|&stone| stone == active_stone) {
            println!("horizontal_line completed.");
            true
        } else if vertival_line.iter().all(|&stone| stone == active_stone) {
            println!("vertival_line completed.");
            true
        } else if fall_left_line.iter().all(|&stone| stone == active_stone) {
            println!("fall_left_line completed.");
            true
        } else if fall_right_line.iter().all(|&stone| stone == active_stone) {
            println!("fall_right_line completed.");
            true
        } else {
            false
        };
        if is_finished { return true };
    }
    false
}

fn main() {
    let mut board = [Stone::Space; WIDTH*HEIGHT];
    let mut active_stone = Stone::White;

    loop {
        let x = get_hand("Input x: ");
        let y = get_hand("Input y: ");
        println!("x = {}, y = {}", x, y);

        insert_stone(&mut board, (x, y), active_stone);
        show_board(&board);

        if is_game_finished(&board, &active_stone) {
            return
        }
        active_stone = match active_stone {
            Stone::White => Stone::Black,
            Stone::Black => Stone::White,
            Stone::Space => Stone::Space
        }
    }
}
