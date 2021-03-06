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

#[allow(unused)]
fn q0() {
    let abc_sum = (0..3).fold(0, |acc, _| acc + read::<u32>());
    let s = read::<String>();
    println!("{} {}", abc_sum, s);
}

#[allow(unused)]
fn q1<T>(num: u32, even_value: T, odd_value: T) -> T {
    if num & 0x1 == 0 {
        even_value
    } else {
        odd_value
    }
}

#[allow(unused)]
fn q2_1(input_str: &String) -> u32 {
    let mut count: u32 = 0;
    for c in input_str.chars() {
       if c == '1' {
           count = count + 1;
       }
    }
    count
}

#[allow(unused)]
fn q2_2(input_str: &String) -> usize
{
    input_str.chars().filter(|&c| c == '1').count()
}

#[allow(unused)]
fn q3_1() {
    fn devide_by_2(nums: &mut Vec<u32>) -> std::result::Result<(), usize> {
        for i in 0..nums.len() {
            if nums[i] & 0x1 == 0x1 {
                return Err(i);
            }
            nums[i] >>= 1;
        }
        Ok(())
    }

    let mut nums: Vec<u32> = vec![64, 32, 64, 16, 32];
    let mut count = 0;
    while devide_by_2(&mut nums).is_ok() {
        count += 1;
    }
    println!("{}", count);
}

fn main() {
    // q0()

    // let ans = q1(read::<u32>(), "Even", "Odd");
    // println!("{}", ans);
    
    // let s: String = read();
    // println!("{}", q2_1(&s));
    // println!("{}", q2_2(&s));

    q3_1();
}
