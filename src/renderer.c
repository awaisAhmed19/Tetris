
#include "renderer.h"

void draw_rect(SDL_Renderer *rend, SDL_FRect *rect, Color c) {
  SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
  SDL_RenderFillRect(rend, rect);
}

void draw_board(Game *g, SDL_Renderer *rend) {
  Color c;
  for (i16 i = 0; i < BOARD_HEIGHT; ++i) {
    for (i16 j = 0; j < BOARD_WIDTH; ++j) {

      c = base_color;

      if (g->board.cells[i][j] != CELL_EMPTY) {
        c = Piece_Color[g->board.cells[i][j]];
      }
      SDL_FRect rect = {.x = CELL_W * j + BOARD_X,
                        .y = CELL_H * i + BOARD_Y,
                        .w = CELL_W,
                        .h = CELL_H};
      draw_rect(rend, &rect, c);
    }
  }
}

void draw_hold_window(SDL_Renderer *rend) {
  SDL_FRect rect = {.x = HOLD_X, .y = HOLD_Y, .w = HOLD_W, .h = HOLD_H};
  SDL_SetRenderDrawColor(rend, base_color.r, base_color.g, base_color.b,
                         base_color.a);
  SDL_RenderFillRect(rend, &rect);
}
void draw_preview_window(SDL_Renderer *rend) {
  SDL_FRect rect = {
      .x = PREVIEW_X, .y = PREVIEW_Y, .w = PREVIEW_W, .h = PREVIEW_H};
  SDL_SetRenderDrawColor(rend, base_color.r, base_color.g, base_color.b,
                         base_color.a);
  SDL_RenderFillRect(rend, &rect);
}
void draw_piece(SDL_Renderer *rend, const Piece *p) {
  for (i16 i = 0; i < CELL_SIZE; ++i) {
    for (i16 j = 0; j < CELL_SIZE; ++j) {

      if (p->cells[i][j] == 0)
        continue;

      i16 board_x = p->pos.x + j;
      i16 board_y = p->pos.y + i;

      SDL_FRect rect = {.x = CELL_W * board_x + BOARD_X,
                        .y = CELL_H * board_y + BOARD_Y,
                        .w = CELL_W,
                        .h = CELL_H};

      draw_rect(rend, &rect, p->color);
    }
  }
}
void draw_hold_piece(SDL_Renderer *rend, Game *g) {
  if (g->hold.type == 0) {
    return;
  }
  for (i16 i = 0; i < CELL_SIZE; ++i) {
    for (i16 j = 0; j < CELL_SIZE; ++j) {

      if (g->hold.cells[i][j] == 0)
        continue;

      SDL_FRect rect = {.x = CELL_W * j + HOLD_X,
                        .y = CELL_H * i + HOLD_Y,
                        .w = CELL_W,
                        .h = CELL_H};

      draw_rect(rend, &rect, g->hold.color);
    }
  }
  // printf("hold type: %d color: {%d,%d,%d,%d}\n", g->hold.type,
  // g->hold.color.r,
  //        g->hold.color.g, g->hold.color.b, g->hold.color.a);
}
void draw_preview_piece(SDL_Renderer *rend, Game *g) {
  for (int p = 0; p < g->piece_preview.size; ++p) {
    Piece *piece = &g->piece_preview.items[p];

    for (i16 i = 0; i < CELL_SIZE; ++i) {
      for (i16 j = 0; j < CELL_SIZE; ++j) {

        if (piece->cells[i][j] == 0)
          continue;

        SDL_FRect rect = {.x = CELL_W * j + PREVIEW_X,
                          .y = CELL_H * i + PREVIEW_Y + (p * HOLD_H),
                          .w = CELL_W,
                          .h = CELL_H};

        draw_rect(rend, &rect, piece->color);
      }
    }
  }
}

void render_game(SDL_Renderer *rend, Game *g) {
  draw_board(g, rend);
  draw_hold_window(rend);
  draw_preview_window(rend);
  draw_hold_piece(rend, g);
  draw_preview_piece(rend, g);
  draw_piece(rend, &g->curr);
}
