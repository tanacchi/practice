use std::{io::{stdin, stdout, Write}, process::Command, str::SplitWhitespace};

fn main() {
  loop {
    print!("> ");
    let _ = stdout().flush();

    let mut input = String::new();
    stdin().read_line(& mut input).unwrap();

    let mut parts = input.trim().split_whitespace();
    let command = parts.next().unwrap();
    let args = parts;

    let mut child = Command::new(command);
    args.for_each(|arg| {
      child.arg(arg);
      ()
    });
    let mut child = child.spawn()
      .unwrap();

    let _ = child.wait();
    }
}
