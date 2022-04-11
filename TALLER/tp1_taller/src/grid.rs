/// This struct receives the number of columns in the grid (length_x),
/// the number of rows (length_y) and a initial grid. After create the grid
/// you must use initialize_grid.

pub struct Grid {
    pub length_x: usize,
    pub length_y: usize,
    pub vector: Vec<Vec<u8>>,
}

impl Grid {
    /// This function generates a grid, it is composed by Vec of Vec of u8.
    pub fn initialize_grid(&mut self) {
        let vector1: Vec<Vec<u8>> = vec![vec![0; self.length_y]; self.length_x];
        self.vector = vector1;
    }

    /// This function returns the item in the row "row" and column "col".
    /// If it is an invalid index, it will return error.
    pub fn get(&mut self, row: usize, col: usize) -> u8 {
        self.vector[row][col]
    }

    /// This function puts the item "elem" in the row "row" and column "col".
    /// If it is an invalid index, it will return error.
    pub fn put(&mut self, elem: u8, row: usize, col: usize) {
        self.vector[row][col] = elem
    }
}
