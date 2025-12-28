use std::io::{self, BufRead};

fn parse_turn(line: &String) -> i32 {
    let mut turn = line.trim().to_string();
    if turn.starts_with("L") {
        turn = line.replace("L", "-");
    } else {
        turn = line.replace("R", "+");
    }
    turn.parse::<i32>().unwrap()
}

fn main() {
    let mut line = String::new();
    let mut current = 50;
    let mut count = 0;
    while io::stdin().lock().read_line(&mut line).unwrap() > 0 {
        let turn = parse_turn(&line);
        current += turn;
        if current % 100 == 0 {
            count += 1;
        }
        line.clear();
    }
    println!("{}", count);
}
