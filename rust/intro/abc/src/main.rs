use std::io::*;

fn main() {
    let stdin = stdin();
    loop {
        let mut string_buffer = String::new();
        stdin.lock()
             .read_line(&mut string_buffer)
             .ok();
        println!("{}", string_buffer);
    }
}
