#include "board.h"

#include "tetrominos.h"
void board_init(Board *board) {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      board->cells[i][j] = CELL_EMPTY;
    }
  }
}

bool board_is_row_full(const Board *board, int y) {
  for (int x = 0; x < BOARD_WIDTH; x++) {
    if (board->cells[y][x] == CELL_EMPTY) {
      return false;
    }
  }
  return true;
}

int board_clear_full_rows(Board *board) {
  int w_y = BOARD_HEIGHT - 1;
  int lines_cleared = 0;

  for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {

    if (board_is_row_full(board, y)) {
      lines_cleared++;
      continue;
    }

    for (int x = 0; x < BOARD_WIDTH; x++) {
      board->cells[w_y][x] = board->cells[y][x];
    }

    w_y--;
  }

  for (int y = w_y; y >= 0; y--) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
      board->cells[y][x] = CELL_EMPTY;
    }
  }

  return lines_cleared;
}
void print_board(Board *board) {
  for (i16 i = 0; i < BOARD_HEIGHT; i++) {
    printf("##");
    for (i16 j = 0; j < BOARD_WIDTH; j++) {
      printf(" %d ", board->cells[i][j]);
    }
    printf("##");
    printf("\n");
  }
  printf("##################################\n");
  printf("##################################\n");
  printf("\n");
}
