#include "core.h"
#include "types.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const u64 FALL_INTERVAL = 300;

void draw_rect(SDL_Renderer *rend, SDL_FRect *rect, Color c) {
  SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
  SDL_RenderFillRect(rend, rect);
}

void init_board(Game *g) {
  for (i16 i = 0; i < BOARD_HEIGHT; ++i) {
    for (i16 j = 0; j < BOARD_WIDTH; ++j) {
      g->board[i][j] = CELL_EMPTY;
    }
  }
}

void draw_board(Game *g, SDL_Renderer *rend) {
  Color c;
  for (i16 i = 0; i < BOARD_HEIGHT; ++i) {
    for (i16 j = 0; j < BOARD_WIDTH; ++j) {
      c = (g->board[i][j]) ? g->curr.color : base_color;
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

Pos get_piece_pos(const Piece *p) {
  for (i16 i = 0; i < CELL_SIZE; ++i) {
    for (i16 j = 0; j < CELL_SIZE; ++j) {
      if (p->cells[i][j] == 0)
        continue;
      return (Pos){.x = p->pos.x + j, .y = p->pos.y + i};
    }
  }

  return (Pos){.x = -1, .y = -1};
}

bool is_row_full(const Game *g, int y) {
  for (int x = 0; x < BOARD_WIDTH; x++) {
    if (g->board[y][x] == CELL_EMPTY) {
      return false;
    }
  }
  return true;
}

int shift_row_below(Game *g) {
  int w_y = BOARD_HEIGHT - 1;
  int lines_cleared = 0;

  for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {

    if (is_row_full(g, y)) {
      lines_cleared++;
      continue;
    }

    for (int x = 0; x < BOARD_WIDTH; x++) {
      g->board[w_y][x] = g->board[y][x];
    }

    w_y--;
  }

  for (int y = w_y; y >= 0; y--) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
      g->board[y][x] = CELL_EMPTY;
    }
  }

  return lines_cleared;
}

void print_board(Game *g) {
  for (i16 i = 0; i < BOARD_HEIGHT; i++) {
    printf("##");
    for (i16 j = 0; j < BOARD_WIDTH; j++) {
      printf(" %d ", g->board[i][j]);
    }
    printf("##");
    printf("\n");
  }
  printf("##################################\n");
  printf("##################################\n");
  printf("\n");
}
void print_TT(Piece *p) {
  for (i16 i = 0; i < CELL_SIZE; i++) {
    for (i16 j = 0; j < CELL_SIZE; j++) {
      printf("%d ", p->cells[i][j]);
    }
    printf("\n");
  }
}
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

      if (g->board[board_y][board_x] != CELL_EMPTY)
        return false;
    }
  }

  return true;
}
void lock_piece(Game *g) {
  for (i16 i = 0; i < CELL_SIZE; ++i) {
    for (i16 j = 0; j < CELL_SIZE; ++j) {
      i16 board_x = g->curr.pos.x + j;
      i16 board_y = g->curr.pos.y + i;

      if (g->curr.cells[i][j] == 1 && board_x >= 0 && board_x < BOARD_WIDTH &&
          board_y >= 0 && board_y < BOARD_HEIGHT) {
        g->board[board_y][board_x] = g->curr.type;
        print_board(g);
      }
    }
  }
}
i16 get_type() {
  i16 type = rand() % TT_NUMS;
  while (type == 0) {
    type = rand() % TT_NUMS;
  }
  return type;
}

void spawn_piece(Game *g) { g->curr = make_piece(get_type()); }

void update(Game *g) {
  Piece candidate = g->curr;
  candidate.pos.y += 1;
  if (check_piece_valid(g, &candidate)) {
    g->curr = candidate;
  } else {
    lock_piece(g);
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
      if (is_row_full(g, y)) {
        g->lines = shift_row_below(g);
      }
    }
    spawn_piece(g);
  }
}

i16 main() {
  srand((unsigned)time(0));
  SDL_Window *win = NULL;
  SDL_Renderer *rend = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  win = SDL_CreateWindow("Tetris", SCREENWIDTH, SCREENHEIGHT, 0);
  rend = SDL_CreateRenderer(win, 0);
  if (!win) {
    SDL_Log("window not created correctly");
    return 1;
  }

  if (!rend) {
    SDL_Log("Renderer not created correctly");
    return 1;
  }
  Game game = {0};
  i16 type = get_type();
  printf("type generate: %d\n", type);
  game.curr = make_piece(type);

  init_board(&game);
  game.running = 1;
  u64 last_fall = SDL_GetTicks();
  print_board(&game);
  while (game.running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_EVENT_QUIT:
        game.running = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        if ((e.key.mod & SDL_KMOD_CTRL) && e.key.key == SDLK_Z) {
          Piece candidate = game.curr;
          rotate_count_clockwise(candidate.cells);
          if (check_piece_valid(&game, &candidate)) {
            game.curr = candidate;
          }
        }
        if (e.key.key == SDLK_SPACE) {
          Piece candidate = game.curr;
          while (candidate.pos.y < BOARD_HEIGHT - 1) {
            candidate.pos.y++;
            if (check_piece_valid(&game, &candidate))
              game.curr = candidate;
          }
        }
        if (e.key.key == SDLK_X) {
          Piece candidate = game.curr;
          rotate_clockwise(game.curr.cells);
          if (check_piece_valid(&game, &candidate)) {
            game.curr = candidate;
          }
        }

        if (e.key.key == SDLK_LEFT) {
          Piece candidate = game.curr;
          candidate.pos.x--;

          if (check_piece_valid(&game, &candidate)) {
            game.curr = candidate;
          }
        }

        if (e.key.key == SDLK_RIGHT) {
          Piece candidate = game.curr;
          candidate.pos.x++;

          if (check_piece_valid(&game, &candidate)) {
            game.curr = candidate;
          }
        }
        break;
      }
    }
    u64 now = SDL_GetTicks();
    if (now - last_fall > FALL_INTERVAL) {
      update(&game);
      last_fall = now;
    }
    SDL_SetRenderDrawColor(rend, black.r, black.g, black.b, black.a);
    SDL_RenderClear(rend);
    draw_board(&game, rend);
    draw_hold_window(rend);
    draw_piece(rend, &game.curr);

    SDL_RenderPresent(rend);
  }
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
