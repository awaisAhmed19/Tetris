#pragma once
#include "board.h"
#include "piece_queue.h"
#include "tetrominos.h"
#include "types.h"
typedef struct {
  bool running;

  i16 score;
  i16 speed;
  i16 lines;
  Board board;
  Piece curr;
  Piece hold;
  // enum TT_tetrominos prev_type; IDEA: to reduce the likely hood of too many
  // repeating types
  Piece_Queue piece_preview;
  bool game_over;
} Game;
extern void game_init(Game *g);
extern void game_update(Game *g);
extern void game_move_left(Game *g);
extern void game_move_right(Game *g);
extern void game_move_down(Game *g);
extern void game_hard_drop(Game *g);
extern void game_rotate(Game *g);
extern void game_cc_rotate(Game *g);
extern void game_hold(Game *g);
