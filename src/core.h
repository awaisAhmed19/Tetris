#pragma once
#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

#define SCREENWIDTH 600
#define SCREENHEIGHT 680

#define CELL_W 28
#define CELL_H 28

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

#define HOLD_W 150
#define HOLD_H 150

#define HOLD_X 440
#define HOLD_Y 50

// #define SPAWN_X 5
// #define SPAWN_Y 0

const i16 paddingW = 150;
const i16 paddingH = 50;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

typedef enum { CELL_EMPTY = 0, CELL_FILLED = 1 } cell_state;
