#pragma once
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
class tetrominos {
   public:
    enum class type { I, O, T, S, Z, J, L };

    void Rotate(vector<vector<int>>& t);
    vector<vector<int>> getShape(type t);
    friend ostream& operator<<(ostream& os, vector<vector<int>> t) {
        for (size_t i = 0; i < t.size(); i++) {
            for (size_t j = 0; j < t.size(); j++) {
                os << t[i][j] << setw(2);
            }
            os << "\n";
        }
        return os;
    }
};
