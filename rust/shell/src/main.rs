use std::{env, io::{stdin, stdout, Write}, path::Path, process::Command};

fn main() {
  loop {
    print!("> ");
    let _ = stdout().flush();

    let mut input = String::new();
    stdin().read_line(& mut input).unwrap();

    let mut parts = input.trim().split_whitespace();
    let command = parts.next().unwrap();
    let args = parts;

    match command {
      "cd" => {
        let new_dir = args.peekable().peek().map_or("/", |x| *x);
        let root = Path::new(new_dir);
        if let Err(e) = env::set_current_dir(&root) {
          eprintln!("{}", e);
        }
      },
      command => {
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
    }
}
