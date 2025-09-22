#include "tetrominos.h"
void swap(int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}
// Done: roatate transpose the matrix and reverseby rows;
void tetrominos::Rotate(vector<vector<int>>& t) {
    for (size_t i = 0; i < t.size(); i++) {
        for (size_t j = i; j < t[i].size(); j++) {
            swap(t[i][j], t[j][i]);
        }
    }

    for (size_t i = 0; i < t.size(); i++) {
        reverse(t[i].begin(), t[i].end());
    }
}

vector<vector<int>> tetrominos::getShape(type type) {
    vector<vector<int>> shape;
    switch (type) {
        case type::J:
            shape = {
                {1, 0, 0},
                {1, 1, 1},
                {0, 0, 0},
            };

            break;
        case type::I:
            shape = {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            };
            break;
        case type::O:
            shape = {
                {1, 1},
                {1, 1},
            };
            break;
        case type::T:
            shape = {
                {0, 1, 0},
                {1, 1, 1},
                {0, 0, 0},
            };
            break;
        case type::S:
            shape = {
                {0, 1, 1},
                {1, 1, 0},
                {0, 0, 0},
            };
            break;
        case type::Z:
            shape = {
                {1, 1, 0},
                {0, 1, 1},
                {0, 0, 0},
            };
            break;
        case type::L:
            shape = {
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 0},
            };
            break;
        default:
            cout << "undefined shape";
            break;
    }
    return shape;
}
