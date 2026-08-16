#pragma once
#include <stdint.h>
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
  const i16 x;
  const i16 y;

  i16 w;
  i16 h;

  i8 state[BOARD_WIDTH][BOARD_HEIGHT];
} game_board;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

typedef enum { CELL_EMPTY = 0, CELL_FILLED = 1 } cell_state;
