#include "tetrominos.h"
#include "core.h"

/*
("
..X.
..X.
..X.
..X.
");
*/
const int Mat_I[CELL_SIZE][CELL_SIZE] = {
    {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};

// ("
// ....
// .XX.
// .XX.
// ....
// ");
const int Mat_O[CELL_SIZE][CELL_SIZE] = {
    {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
// ("
// ..X.
// .XX.
// ..X.
// ....
// ");
const int Mat_T[CELL_SIZE][CELL_SIZE] = {
    {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};

// ("
// .X..
// .XX.
// ..X.
// ....
// ");
const int Mat_S[CELL_SIZE][CELL_SIZE] = {
    {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};

// ("
// ..X.
// .XX.
// .X..
// ....
// ");
const int Mat_Z[CELL_SIZE][CELL_SIZE] = {
    {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
/*
("
..X.
..X.
.XX.
....
");
*/
const int Mat_J[CELL_SIZE][CELL_SIZE] = {
    {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
// ("
// .X..
// .X..
// .XX.
// ....
// ");
const int Mat_L[CELL_SIZE][CELL_SIZE] = {
    {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};

void copy_matrix(const int src[CELL_SIZE][CELL_SIZE],
                 int dest[CELL_SIZE][CELL_SIZE]) {
  for (int i = 0; i < CELL_SIZE; ++i) {
    for (int j = 0; j < CELL_SIZE; ++j)
      dest[i][j] = src[i][j];
  }
}

Piece make_piece(enum TT_tetrominos type) {
  Piece p = {0};
  p.type = type;
  p.pos.x = BOARD_WIDTH / 2 - CELL_SIZE / 2;
  p.pos.y = 0;
  switch (type) {
  case TT_I:
    copy_matrix(Mat_I, p.cells);
    break;
  case TT_L:
    copy_matrix(Mat_L, p.cells);
    break;
  case TT_O:
    copy_matrix(Mat_O, p.cells);
    break;
  case TT_J:
    copy_matrix(Mat_J, p.cells);
    break;
  case TT_S:
    copy_matrix(Mat_S, p.cells);
    break;
  case TT_Z:
    copy_matrix(Mat_Z, p.cells);
    break;
  case TT_T:
    copy_matrix(Mat_T, p.cells);
    break;
  }
  return p;
}

void rotate_count_clockwise(int cells[CELL_SIZE][CELL_SIZE]) {
  int res[CELL_SIZE][CELL_SIZE];
  for (int i = 0; i < CELL_SIZE; ++i) {
    for (int j = 0; j < CELL_SIZE; ++j) {
      res[CELL_SIZE - j - 1][i] = cells[i][j];
    }
  }
  copy_matrix(res, cells);
}

/*
 * --#-
 * --#-
 * --#-
 * --#-
 *  */
void rotate_clockwise(int cells[CELL_SIZE][CELL_SIZE]) {
  int res[CELL_SIZE][CELL_SIZE];
  for (int i = 0; i < CELL_SIZE; ++i) {
    for (int j = 0; j < CELL_SIZE; ++j) {
      res[j][CELL_SIZE - i - 1] = cells[i][j];
    }
  }
  copy_matrix(res, cells);
}
