use std::{env, io::{stdin, stdout, Write}, path::Path, process::{Child, Command}};

fn main() {
  loop {
    print!("> ");
    let _ = stdout().flush();

    let mut input = String::new();
    stdin().read_line(& mut input).unwrap();

    let mut parts = input.trim().split_whitespace();
    let command = match parts.next() {
      Some(command) => command,
      None => continue,
    };
    let args = parts;

    match command {
      "cd" => {
        let new_dir = args.peekable().peek().map_or("/", |x| *x);
        let root = Path::new(new_dir);
        if let Err(e) = env::set_current_dir(&root) {
          eprintln!("{}", e);
        }
      },
      "exit" => return,
      command => {
        let mut child = Command::new(command);
        args.for_each(|arg| {
          child.arg(arg);
          ()
        });

        match child.spawn() {
          Ok(mut child) => { child.wait(); }
          Err(e) => eprint!("{}", e),
        }
      }
    }
    }
}
