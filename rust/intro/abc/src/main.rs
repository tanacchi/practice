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

fn main() {
    loop {
        let a = read::<u32>();
        println!("{}", a);
    }
}
