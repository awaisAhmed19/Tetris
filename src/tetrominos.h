#pragma once
#include "colors.h"
#include "types.h"
#define TT_NUMS 8
#define CELL_SIZE 4

enum TT_tetrominos {
  CELL_EMPTY = 0,
  TT_I,
  TT_O,
  TT_T,
  TT_S,
  TT_Z,
  TT_J,
  TT_L,
};

typedef struct {
  i16 cells[CELL_SIZE][CELL_SIZE];
  enum TT_tetrominos type;
  Pos pos;
  Color color;
} Piece;

extern const i16 Mat_I[CELL_SIZE][CELL_SIZE];
extern const i16 Mat_O[CELL_SIZE][CELL_SIZE];
extern const i16 Mat_T[CELL_SIZE][CELL_SIZE];
extern const i16 Mat_S[CELL_SIZE][CELL_SIZE];
extern const i16 Mat_Z[CELL_SIZE][CELL_SIZE];
extern const i16 Mat_J[CELL_SIZE][CELL_SIZE];
extern const i16 Mat_L[CELL_SIZE][CELL_SIZE];

void copy_matrix(const i16 src[CELL_SIZE][CELL_SIZE],
                 i16 dest[CELL_SIZE][CELL_SIZE]);

Piece make_piece(enum TT_tetrominos type);

void rotate_count_clockwise(i16 cells[CELL_SIZE][CELL_SIZE]);
void rotate_clockwise(i16 cells[CELL_SIZE][CELL_SIZE]);
