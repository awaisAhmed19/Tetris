
// todo: make this into debugging grid and shape printers
//
/*
ostream& operator<<(ostream& os, vector<vector<int>> t) {
    for (size_t i = 0; i < t.size(); i++) {
        for (size_t j = 0; j < t.size(); j++) {
            os << t[i][j] << setw(2);
        }
        os << "\n";
    }
    return os;
}

// utility lib
ostream& operator<<(ostream& os, const Grid& grid) {
    for (size_t i = 0; i < grid.rows; i++) {
        os << setw(2) << grid.rows - i << "#" << setw(2);
        for (size_t j = 0; j < grid.cols; j++) {
            os << grid.grid[i][j] << setw(2);
        }
        os << "#" << setw(2) << endl;
    }
    os << setw(3);
    for (size_t j = 0; j < grid.cols + 2; j++) {
        os << "#" << setw(2);
    }
    os << endl;
    os << setw(5);
    for (size_t j = 0; j < grid.cols; j++) {
        os << j + 1 << setw(2);
    }
    os << endl;
    return os;
}
*/
