use std::io;

pub fn get_hand(msg: &str) -> usize {
    println!("{}", msg);
    let mut hand: Option<usize> = None;
    while let None = hand {
        hand = {
            let mut hand = String::new();
            let _ = io::stdin().read_line(&mut hand);
            hand.trim().parse::<usize>().ok()
        };
    }
    hand.unwrap()
}
