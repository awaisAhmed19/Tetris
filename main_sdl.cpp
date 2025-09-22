#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "./src/game/Game.h"
#include "./src/game/Grid.h"
#include "./src/game/tetrominos.h"
using namespace std;
Game* gg = 0;
void print(vector<vector<int>> t) {
    for (size_t i = 0; i < t.size(); i++) {
        for (size_t j = 0; j < t.size(); j++) {
            cout << t[i][j] << setw(2);
        }
        cout << "\n";
    }
}
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL init failed: " << SDL_GetError() << endl;
        return 1;
    }

    tetrominos t;

    SDL_Window* window = SDL_CreateWindow("Keyboard Test", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    Grid grid;
    bool KEYS[322];

    for (int i = 0; i < 322; i++) {  // init them all to false
        KEYS[i] = false;
    }
    // SDL_EnableKeyRepeat(0, 0);
    cout << grid;
    bool quit = false;
    SDL_Event ev;
    vector<vector<int>> shape = t.getShape(t.type::J);
    // vector<vector<int>> tetro = t.getshape(t.type::S);
    while (!quit) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                quit = true;
            } else if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                    case SDLK_s:
                        // cout << "left" << endl;
                        cout << "\n";
                        break;
                    case SDLK_LEFT:
                        // cout << "left" << endl;
                        t.Rotate(shape);
                        print(shape);
                        cout << "\n";
                        break;
                    case SDLK_RIGHT:
                        cout << "right" << endl;

                        t.Rotate(shape);
                        print(shape);
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
