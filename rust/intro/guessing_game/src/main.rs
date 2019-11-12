extern crate rand;

use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    println!("Guess the number!");

    let answer = rand::thread_rng().gen_range(1, 101);
    println!("answer: {}", answer);

    loop {
        println!("Input the number.");

        let mut guess = String::new();
        io::stdin().read_line(&mut guess)
                   .expect("Failed to read line.");
        let guess : u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_)  => continue,
        };
        println!("You guessed: {}", guess);
        
        match guess.cmp(&answer) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            },
        }
    }
}
