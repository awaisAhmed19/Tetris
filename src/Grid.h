#pragma once

class Grid {
    const size_t pm_Cols = 10, pm_Rows = 22;

   public:
    vector<vector<int>> grid;
    Grid() { grid.resize(pm_Rows, vector<int>(pm_Cols, 0)); }
    const size_t celldims = 50;
};
