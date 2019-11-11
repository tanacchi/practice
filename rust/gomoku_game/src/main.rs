use std::io;

fn main() {
    let mut board = [[0, 0], [0, 0]];

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

    for row in &board {
        for i in 0..row.len() {
            print!("{} ", row[i]);
        }
        println!();
    }
}
