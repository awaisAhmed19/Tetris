#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Game.h"

using namespace std;
Game* gg = 0;

class Grid {
   public:
    const size_t cols = 10, rows = 22;
    vector<vector<int>> grid;
    const size_t celldims = 50;

    Grid() { grid.resize(rows, vector<int>(cols, 0)); }
};

class tetminoes {
   public:
    vector<vector<int>> L{
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 1},
    };
    vector<vector<int>> I{
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
    };
    vector<vector<int>> O{
        {1, 1},
        {1, 1},
    };
    vector<vector<int>> T{
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0},
    };
    vector<vector<int>> S{
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0},
    };
    vector<vector<int>> Z{
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0},
    };
    vector<vector<int>> J{
        {0, 1, 0},
        {0, 1, 0},
        {1, 1, 0},
    };
};

void swap(int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

vector<vector<int>> Rotate(vector<vector<int>>& t) {
    // TODO: roatate right =>transpose the matrix and reverseby rows;
    // TODO: roatate left =>reverse by col and transpose the matrix ;

    for (size_t i = 0; i < t.size(); i++) {
        for (size_t j = i; j < t[i].size(); j++) {
            swap(t[i][j], t[j][i]);
        }
    }

    for (size_t i = 0; i < t.size(); i++) {
        reverse(t[i].begin(), t[i].end());
    }

    return t;
}

ostream& operator<<(ostream& os, vector<vector<int>> t) {
    for (size_t i = 0; i < t.size(); i++) {
        for (size_t j = 0; j < t.size(); j++) {
            os << t[i][j] << setw(2);
        }
        os << "\n";
    }
    return os;
}

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

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL init failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Hidden tiny window so SDL sends events

    SDL_Window* window =
        SDL_CreateWindow("Keyboard Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,
                         480,              // a normal small window
                         SDL_WINDOW_SHOWN  // <-- must be SHOWN to capture keys
        );

    Grid grid;
    bool KEYS[322];  // 322 is the number of SDLK_DOWN events

    for (int i = 0; i < 322; i++) {  // init them all to false
        KEYS[i] = false;
    }
    // SDL_EnableKeyRepeat(0, 0);
    // cout << grid;
    bool quit = false;
    SDL_Event ev;
    tetminoes t;
    while (!quit) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                quit = true;
            } else if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                    case SDLK_LEFT:
                        // cout << "left" << endl;
                        cout << Rotate(t.J);
                        cout << "\n";
                        break;
                    case SDLK_RIGHT:
                        cout << "right" << endl;
                        cout << Rotate(t.O);
                        cout << "\n";
                        break;
                    case SDLK_UP:
                        cout << "up" << endl;
                        break;
                    case SDLK_DOWN:
                        cout << "down" << endl;
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    /* gg = new Game();

   gg->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 650, 650, false);
   while (gg->running()) {
   gg->handleEvents();
   gg->update();
   gg->render();
   }

   gg->clean();
   */
}
