#pragma once
#include "core.h"
#define TT_NUMS 7

enum TT_tetrominos {
  TT_I = 1,
  TT_O = 2,
  TT_T = 3,
  TT_S = 4,
  TT_Z = 5,
  TT_J = 6,
  TT_L = 7,
};

typedef struct {
  int x;
  int y;
} Cell;

typedef struct {
  Cell cell;
  int rotation;
  enum TT_tetrominos type;
} Piece;

Cell I_rot0[4] = {
    {0, 2},
    {1, 2},
    {2, 2},
    {3, 2},
};
Cell I_rot1[4] = {
    {2, 0},
    {2, 1},
    {2, 2},
    {2, 3},
};

Cell O[4] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

// Cell T[4] =
