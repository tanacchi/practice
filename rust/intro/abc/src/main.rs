use std::io;

fn main() {
    loop {
        let mut string_buffer = String::new();
        io::stdin().read_line(&mut string_buffer).ok();
        println!("{}", string_buffer);
    }
}
