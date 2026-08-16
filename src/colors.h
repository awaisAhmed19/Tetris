#pragma once
#include "core.h"
#include "tetrominos.h"
const Color base_color = {.r = 28, .g = 28, .b = 28, .a = 255}; // Background

const Color cyan = {.r = 51, .g = 196, .b = 175, .a = 255};   // I
const Color blue = {.r = 41, .g = 128, .b = 255, .a = 255};   // J
const Color orange = {.r = 255, .g = 159, .b = 28, .a = 255}; // L
const Color yellow = {.r = 255, .g = 214, .b = 10, .a = 255}; // O
const Color green = {.r = 76, .g = 217, .b = 100, .a = 255};  // S
const Color purple = {.r = 170, .g = 82, .b = 255, .a = 255}; // T
const Color red = {.r = 255, .g = 69, .b = 58, .a = 255};     // Z

const Color white = {.r = 255, .g = 255, .b = 255, .a = 255};
const Color black = {.r = 0, .g = 0, .b = 0, .a = 255};

const Color gray = {.r = 128, .g = 128, .b = 128, .a = 255};
const Color light_gray = {.r = 200, .g = 200, .b = 200, .a = 255};
const Color dark_gray = {.r = 60, .g = 60, .b = 60, .a = 255};

const Color border = {.r = 45, .g = 45, .b = 45, .a = 255};
const Color ghost = {
    .r = 180, .g = 180, .b = 180, .a = 100}; // Transparent ghost piece

const Color Piece_colors[TT_NUMS] = {cyan,  blue,   orange, yellow,
                                     green, purple, red};
