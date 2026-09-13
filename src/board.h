#pragma once
#include "core.h"
typedef struct {
  i16 cells[BOARD_HEIGHT][BOARD_WIDTH];
} Board;

extern void board_init(Board *board);

extern bool board_is_row_full(const Board *board, int y);

extern int board_clear_full_rows(Board *board);
extern void print_board(Board *board);
