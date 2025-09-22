#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "./src/game/Grid.h"
#include "./src/game/tetrominos.h"
#include "ftxui/dom/canvas.hpp"
#include "ftxui/dom/direction.hpp"
#include "ftxui/dom/flexbox_config.hpp"
#include "ftxui/dom/linear_gradient.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/box.hpp"
#include "ftxui/screen/terminal.hpp"
#include "ftxui/util/ref.hpp"
using namespace std;
Grid grid;
tetrominos t;
void print(vector<vector<int>> t) {
    for (size_t i = 0; i < t.size(); i++) {
        for (size_t j = 0; j < t[i].size(); j++) {
            cout << t[i][j] << setw(2);
        }
        cout << "\n";
    }
}

void test() {
    using namespace ftxui;
    char a;
    cin >> a;
    vector<vector<int>> shape = t.getShape(t.charToPieces(a));
    std::srand(std::time(nullptr));
    std::vector<Element> rows;
    for (size_t i = 0; i < shape.size(); i++) {
        std::vector<Element> cols;
        for (size_t j = 0; j < shape[i].size(); j++) {
            cols.push_back(text(shape[i][j] ? "[]" : "  "));
        }

        rows.push_back(hbox(std::move(cols)));
    }

    auto document_element = vbox(std::move(rows)) | border;
    auto document = Renderer([&] { return document_element; });

    auto screen = ScreenInteractive::TerminalOutput();

    screen.Loop(document);
}
int main(int argc, char* argv[]) {
    test();

    Grid grid;

    bool quit = false;
    // vector<vector<int>> tetro = t.getshape(t.type::S);
    char a;
    while (!quit) {
        cin >> a;
        switch (a) {
            case 'd':
                // cout << "left" << endl;
                cout << "\n";
                break;
            case 'r':
                // cout << "left" << endl;
                // t.Rotate(shape);
                // push_backrint(shape);
                cout << "\n";
                break;
            case 'a':
                cout << "right" << endl;
                // t.Rotate(shape);
                // print(shape);
                cout << "\n";
            case 'w':
                cout << "up" << endl;
                break;
            case 's':
                cout << "down" << endl;
                break;
            case 'q':
                quit = true;
                break;
            default:
                break;
        }
    }

    return 0;
}
