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

fn q1<T>(num: u32, even_value: T, odd_value: T) -> T {
    if num & 0x1 == 0 {
        even_value
    } else {
        odd_value
    }
}

fn q2_1(input_str: String) -> u32 {
    let mut count: u32 = 0;
    for c in input_str.chars() {
       if c == '1' {
           count = count + 1;
       }
    }
    count
}

fn main() {
    // q0()

    // let ans = q1(read::<u32>(), "Even", "Odd");
    // println!("{}", ans);
    
    let s: String = read();
    println!("{}", q2(s));
}
