#pragma once

#define TT_NUMS 7
#define CELL_SIZE 4

enum TT_tetrominos {
  TT_I = 0,
  TT_O,
  TT_T,
  TT_S,
  TT_Z,
  TT_J,
  TT_L,
};

typedef struct {
  int x;
  int y;
} Pos;

typedef struct {
  int cells[CELL_SIZE][CELL_SIZE];
  enum TT_tetrominos type;
  Pos pos;
} Piece;

extern const int Mat_I[CELL_SIZE][CELL_SIZE];
extern const int Mat_O[CELL_SIZE][CELL_SIZE];
extern const int Mat_T[CELL_SIZE][CELL_SIZE];
extern const int Mat_S[CELL_SIZE][CELL_SIZE];
extern const int Mat_Z[CELL_SIZE][CELL_SIZE];
extern const int Mat_J[CELL_SIZE][CELL_SIZE];
extern const int Mat_L[CELL_SIZE][CELL_SIZE];

void copy_matrix(const int src[CELL_SIZE][CELL_SIZE],
                 int dest[CELL_SIZE][CELL_SIZE]);

Piece make_piece(enum TT_tetrominos type);

void rotate_count_clockwise(int cells[CELL_SIZE][CELL_SIZE]);
void rotate_clockwise(int cells[CELL_SIZE][CELL_SIZE]);
