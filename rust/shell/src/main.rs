use std::{env, io::{stdin, stdout, Write}, path::Path, process::{Child, Command, Stdio}};

fn main() {
  loop {
    print!("> ");
    let _ = stdout().flush();

    let mut input = String::new();
    stdin().read_line(& mut input).unwrap();

    let mut commands = input.trim().split("|").peekable();
    let mut previous_command = None;

    while let Some(command) = commands.next() {
      let mut parts = command.trim().split_whitespace();
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
          previous_command = None;
        },
        "exit" => return,
        command => {
          let stdin = previous_command
            .map_or(
              Stdio::inherit(),
              |output: Child| Stdio::from(output.stdout.unwrap())
            );

          let stdout = if commands.peek().is_some() {
            Stdio::piped()
          } else {
            Stdio::inherit()
          };

          let output = Command::new(command)
            .args(args)
            .stdin(stdin)
            .stdout(stdout)
            .spawn();

          match output {
            Ok(child) => { previous_command = Some(child); }
            Err(e) => {
              previous_command = None;
              eprint!("{}", e);
            },
          }
        }
      }
    }

    if let Some(mut final_command) = previous_command {
      final_command.wait();
    }
  }
}
