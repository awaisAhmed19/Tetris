#pragma once
#include <tetrominos.h>

#define SCREENWIDTH 600
#define SCREENHEIGHT 680

#define CELL_W 28
#define CELL_H 28

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

#define HOLD_W (CELL_W * 4)
#define HOLD_H (CELL_W * 4)

#define BOARD_X ((SCREENWIDTH - (BOARD_WIDTH * CELL_W)) * 0.5)
#define BOARD_Y ((SCREENHEIGHT - (BOARD_HEIGHT * CELL_H)) * 0.5)

#define HOLD_X (BOARD_X + (BOARD_WIDTH * CELL_H) + 10)
#define HOLD_Y ((SCREENHEIGHT - (BOARD_HEIGHT * CELL_H)) * 0.5)

// #define SPAWN_X 5
// #define SPAWN_Y 0

typedef struct {
  i8 running;

  i16 score;
  i16 speed;
  i16 lines;

  Piece curr;
  Piece hold;

  i16 board[BOARD_HEIGHT][BOARD_WIDTH];
} Game;
