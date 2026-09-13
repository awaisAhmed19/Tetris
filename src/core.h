#pragma once
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FALL_INTERVAL 300
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

#define SCREENWIDTH 600
#define SCREENHEIGHT 680

#define CELL_W 28
#define CELL_H 28

#define HOLD_W (CELL_W * 4)
#define HOLD_H (CELL_W * 4)

#define BOARD_X ((SCREENWIDTH - (BOARD_WIDTH * CELL_W)) * 0.5)
#define BOARD_Y ((SCREENHEIGHT - (BOARD_HEIGHT * CELL_H)) * 0.5)

#define HOLD_X (BOARD_X + (BOARD_WIDTH * CELL_H) + 10)
#define HOLD_Y ((SCREENHEIGHT - (BOARD_HEIGHT * CELL_H)) * 0.5)

#define PREVIEW_W HOLD_W
#define PREVIEW_H HOLD_H * 3

#define PREVIEW_X 40 //(BOARD_X - (BOARD_WIDTH * CELL_H) - 10)
#define PREVIEW_Y HOLD_Y

#define SPAWN_X BOARD_WIDTH / 2 - CELL_SIZE / 2
#define SPAWN_Y 0
