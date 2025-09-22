#pragma once
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
class Grid {
    const size_t pm_Cols = 10, pm_Rows = 22;

   public:
    size_t getCols();
    size_t getRows();

    vector<vector<int>> grid;

    Grid() { grid.resize(pm_Rows, vector<int>(pm_Cols, 0)); }
    const size_t celldims = 50;

    friend ostream& operator<<(ostream& os, const Grid& grid) {
        for (size_t i = 0; i < grid.pm_Rows; i++) {
            os << setw(2) << grid.pm_Rows - i << "#" << setw(2);
            for (size_t j = 0; j < grid.pm_Cols; j++) {
                os << grid.grid[i][j] << setw(2);
            }
            os << "#" << setw(2) << endl;
        }
        os << setw(3);
        for (size_t j = 0; j < grid.pm_Cols + 2; j++) {
            os << "#" << setw(2);
        }
        os << endl;
        os << setw(5);
        for (size_t j = 0; j < grid.pm_Cols; j++) {
            os << j + 1 << setw(2);
        }
        os << endl;
        return os;
    }
};
