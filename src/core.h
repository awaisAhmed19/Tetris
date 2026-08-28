#pragma once
#include <stdint.h>
#include <tetrominos.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

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

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

typedef enum { CELL_EMPTY = 0, CELL_FILLED = 1 } cell_state;
