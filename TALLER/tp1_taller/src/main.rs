use std::cmp;
use std::fs;
use std::io::Error;
mod grid;

fn main() {
    let vector1 = read_file_lines("src/example1.txt");
    if vector1.is_err() {
        println!("ERROR: {:?}", vector1.unwrap_err());
        return;
    }

    let vector2 = read_file_lines("src/example2.txt");
    if vector2.is_err() {
        println!("ERROR: {:?}", vector2.unwrap_err());
        return;
    }

    let vec1 = vector1.unwrap();
    let vec2 = vector2.unwrap();

    let grid = lcs(&vec1, &vec2);
    print_diff(grid, &vec1, &vec2, vec1.len(), vec2.len());
}

///  This function reads the file located in path and returns
///  a Result. On success it will return a vector containing each line of the file.
///  On error it will return the error.
fn read_file_lines(path: &str) -> Result<Vec<String>, Error> {
    let content = fs::read_to_string(path);
    match content {
        Ok(lines) => Ok(lines.lines().map(|x| x.to_string()).collect()),
        Err(error) => Err(error),
    }
}

/// This function calculates the difference between x and y.
/// x and y must be a Vec<String> containing each line of a file.
/// lcs returns a grid containing information about the difference,
/// to print it you can use print_diff().
fn lcs(x: &[String], y: &[String]) -> grid::Grid {
    let m = x.len();
    let n = y.len();
    let mut grid = grid::Grid {
        length_x: m + 1,
        length_y: n + 1,
        vector: Vec::new(),
    };
    grid.initialize_grid();

    for i in 0..m + 1 {
        grid.put(0, i, 0)
    }
    for j in 0..n + 1 {
        grid.put(0, 0, j)
    }
    for (i, item_x) in x.iter().enumerate().take(m) {
        for (j, item_y) in y.iter().enumerate().take(n) {
            if item_x == item_y {
                let value_aux = grid.get(i, j);
                grid.put(value_aux + 1, i + 1, j + 1)
            } else {
                let aux1 = grid.get(i + 1, j);
                let aux2 = grid.get(i, j + 1);
                grid.put(cmp::max(aux1, aux2), i + 1, j + 1)
            }
        }
    }
    grid
}

/// This function prints the different lines between x and y.
/// If y has a missing line, the function will print < "line".
/// And the new line will be printed like > "line".
/// If there is the same line, "line" will be printed.
/// grid is the computed by lcs().
/// x and y are the vectors of String.
/// i and j are the numbers to index the grid.
/// You must call this function with i = len(x) y j = len(y).
fn print_diff(mut grid: grid::Grid, x: &[String], y: &[String], i: usize, j: usize) {
    let mut aux1 = 0; // These variables won't be used without being initialized
    let mut aux2 = 0;
    let mut aux3 = 0;
    let mut aux4 = 0;

    // Initialiazing variables if i will need them.
    if j > 0 && i > 0 {
        aux1 = grid.get(i, j - 1);
        aux2 = grid.get(i - 1, j);
        aux3 = grid.get(i, j - 1);
        aux4 = grid.get(i - 1, j);
    }

    if i > 0 && j > 0 && x[i - 1] == y[j - 1] {
        print_diff(grid, x, y, i - 1, j - 1);
        println!("  {}", x[i - 1]);
    } else if j > 0 && (i == 0 || aux1 >= aux2) {
        print_diff(grid, x, y, i, j - 1);
        println!("> {}", y[j - 1]);
    } else if i > 0 && (j == 0 || aux3 < aux4) {
        print_diff(grid, x, y, i - 1, j);
        println!("< {}", x[i - 1]);
    } else {
        println!()
    }
}
