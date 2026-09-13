#include "game.h"
#include "board.h"
bool check_piece_valid(const Game *g, const Piece *p) {
  for (i16 i = 0; i < CELL_SIZE; i++) {
    for (i16 j = 0; j < CELL_SIZE; j++) {

      if (p->cells[i][j] == 0)
        continue;

      i16 board_x = p->pos.x + j;
      i16 board_y = p->pos.y + i;

      if (board_x < 0 || board_x >= BOARD_WIDTH)
        return false;

      if (board_y >= BOARD_HEIGHT)
        return false;

      if (board_y < 0)
        continue;

      if (g->board.cells[board_y][board_x] != CELL_EMPTY)
        return false;
    }
  }

  return true;
}
void spawn_piece(Game *g) {
  Piece candidate = peek(&g->piece_preview);

  if (!check_piece_valid(g, &candidate)) {
    g->game_over = true;
    return;
  }

  g->curr = candidate;

  dequeue(&g->piece_preview);
  enqueue(&g->piece_preview, get_type());
}
void game_init(Game *g) {
  init_piece_queue(&g->piece_preview);
  board_init(&g->board);
  g->running = true;
  g->game_over = false;
  g->score = 0;
  g->lines = 0;
  g->hold = (Piece){0};

  for (int i = 0; i < MAX_PREVIEW_SIZE; i++) {
    enqueue(&g->piece_preview, get_type());
  }

  spawn_piece(g);
  printf("g->piece_preview.items[0].type = %d", g->piece_preview.items[0].type);
}

// init_game()
// update()

void lock_piece(Game *g) {
  for (i16 i = 0; i < CELL_SIZE; ++i) {
    for (i16 j = 0; j < CELL_SIZE; ++j) {
      i16 board_x = g->curr.pos.x + j;
      i16 board_y = g->curr.pos.y + i;

      if (g->curr.cells[i][j] == 1 && board_x >= 0 && board_x < BOARD_WIDTH &&
          board_y >= 0 && board_y < BOARD_HEIGHT) {
        g->board.cells[board_y][board_x] = g->curr.type;
      }
    }
  }
}

void game_update(Game *g) {
  Piece candidate = g->curr;
  candidate.pos.y += 1;
  int cleared = 0;
  if (check_piece_valid(g, &candidate)) {
    g->curr = candidate;
  } else {
    lock_piece(g);
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
      if (board_is_row_full(&g->board, y)) {
        cleared += board_clear_full_rows(&g->board);
      }
    }
    g->lines += cleared;
    g->score += cleared * 10;
    print_board(&g->board);
    spawn_piece(g);
  }
}
void game_move_left(Game *g) {
  Piece candidate = g->curr;
  candidate.pos.x--;

  if (check_piece_valid(g, &candidate)) {
    g->curr = candidate;
  }
}
void game_move_right(Game *g) {
  Piece candidate = g->curr;
  candidate.pos.x++;

  if (check_piece_valid(g, &candidate)) {
    g->curr = candidate;
  }
}
void game_move_down(Game *g) {
  Piece candidate = g->curr;
  candidate.pos.y++;
  if (check_piece_valid(g, &candidate)) {
    g->curr = candidate;
  } else {
    candidate.pos.y--;
    g->curr = candidate;
  }
}
void game_hard_drop(Game *g) {
  Piece candidate = g->curr;
  while (check_piece_valid(g, &candidate) &&
         candidate.pos.y < BOARD_HEIGHT - 1) {
    candidate.pos.y++;
    if (check_piece_valid(g, &candidate))
      g->curr = candidate;
  }
}
void game_rotate(Game *g) {
  Piece candidate = g->curr;
  rotate_clockwise(candidate.cells);
  if (check_piece_valid(g, &candidate)) {
    g->curr = candidate;
  }
}
void game_cc_rotate(Game *g) {
  Piece candidate = g->curr;
  rotate_count_clockwise(candidate.cells);
  if (check_piece_valid(g, &candidate)) {
    g->curr = candidate;
  }
}
void game_hold(Game *g) {
  Piece candidate = g->curr;
  printf("game->hold.type: %d\n", g->hold.type);
  if (g->hold.type == CELL_EMPTY) {
    spawn_piece(g);
    g->hold = candidate;
    g->hold.pos.x = SPAWN_X;
    g->hold.pos.y = SPAWN_Y;
  } else {
    g->curr = g->hold;
    g->hold = candidate;
    g->hold.pos.x = SPAWN_X;
    g->hold.pos.y = SPAWN_Y;
    candidate = (Piece){0};
  }
}

void debug_print(Game *g) {
  print_board(&g->board);
  printf("g->curr.type = %d\n", g->curr.type);
  printf("g->lines = %d\n", g->lines);
  printf("g->score = %d\n", g->score);
}
// spawn_piece()
// lock_piece()
// check_piece_valid()
