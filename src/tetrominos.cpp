#include "tetrominos.h"

// Done: roatate transpose the matrix and reverseby rows;
void tetrominos::rotate(vector<vector<int>>& t) {
    for (size_t i = 0; i < t.size(); i++) {
        for (size_t j = i; j < t[i].size(); j++) {
            swap(t[i][j], t[j][i]);
        }
    }

    for (size_t i = 0; i < t.size(); i++) {
        reverse(t[i].begin(), t[i].end());
    }
}

vector<vector<int>> tetrominos::getshape(tetrominos type) const {
    vector<vector<int>> shape;
    switch (type) {
        case tetrominos::L:
            shape = {
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 1},
            };

            break;
        case tetrominos::I:
            shape = {
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            };
            break;
        case tetrominos::O:
            shape = {
                {1, 1},
                {1, 1},
            };
            break;
        case tetrominos::T:
            shape = {
                {0, 1, 0},
                {1, 1, 1},
                {0, 0, 0},
            };
            break;
        case tetrominos::S:
            shape = {
                {0, 1, 1},
                {1, 1, 0},
                {0, 0, 0},
            };
            break;
        case tetrominos::Z:
            shape = {
                {1, 1, 0},
                {0, 1, 1},
                {0, 0, 0},
            };
            break;
        case tetrominos::J:
            shape = {
                {0, 1, 0},
                {0, 1, 0},
                {1, 1, 0},
            };
            break;
        default:
            cout << "undefined shape";
            break;
    }
    return shape;
}
