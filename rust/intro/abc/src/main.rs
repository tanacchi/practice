use std::io::*;
use std::str::FromStr;

fn read<T: FromStr>() -> T {
    let stdin = stdin();
    let s = stdin.bytes()
                 .map(|c| c.unwrap() as char)
                 .skip_while(|c| c.is_whitespace())
                 .take_while(|c| !c.is_whitespace())
                 .collect::<String>();
    s.parse::<T>().ok().unwrap()
}

fn q0() {
    let abc_sum = (0..3).fold(0, |acc, _| acc + read::<u32>());
    let s = read::<String>();
    println!("{} {}", abc_sum, s);
}

fn main() {
    q0();
}
