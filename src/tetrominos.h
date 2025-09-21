#pragma once
class tetrominos {
   public:
    enum type { I, O, T, S, Z, J, L };

    void rotate(vector<vector<int>> t);
    vector<vector<int>> getshape(tetrominos type);
};
