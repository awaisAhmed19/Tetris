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

Pieces tetrominos::charToPieces(char c) {
    switch (c) {
        case 'I':
            return Pieces::I;
        case 'O':
            return Pieces::O;
        case 'T':
            return Pieces::T;
        case 'S':
            return Pieces::S;
        case 'Z':
            return Pieces::Z;
        case 'J':
            return Pieces::J;
        case 'L':
            return Pieces::L;
        default:
            throw std::invalid_argument("Invalid piece p");
    }
}

vector<vector<int>> tetrominos::getShape(Pieces p) {
    vector<vector<int>> shape;
    switch (p) {
        case Pieces::J:
            shape = {
                {1, 0, 0},
                {1, 1, 1},
                {0, 0, 0},
            };

            break;
        case Pieces::I:
            shape = {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            };
            break;
        case Pieces::O:
            shape = {
                {1, 1},
                {1, 1},
            };
            break;
        case Pieces::T:
            shape = {
                {0, 1, 0},
                {1, 1, 1},
                {0, 0, 0},
            };
            break;
        case Pieces::S:
            shape = {
                {0, 1, 1},
                {1, 1, 0},
                {0, 0, 0},
            };
            break;
        case Pieces::Z:
            shape = {
                {1, 1, 0},
                {0, 1, 1},
                {0, 0, 0},
            };
            break;
        case Pieces::L:
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
