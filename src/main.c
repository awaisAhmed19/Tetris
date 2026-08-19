#include "colors.h"
#include "core.h"
// #include "tetrominos.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const Uint64 FALL_INTERVAL = 300;

void draw_rect(SDL_Renderer *rend, SDL_FRect *rect, Color c) {
  SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
  SDL_RenderFillRect(rend, rect);
}

void init_board(Game *g) {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      g->board[i][j] = CELL_EMPTY;
    }
  }
}

void draw_board(Game *g, SDL_Renderer *rend) {
  Color c;
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      c = (g->board[i][j]) ? Piece_colors[g->curr.type] : base_color;
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
  for (int i = 0; i < CELL_SIZE; ++i) {
    for (int j = 0; j < CELL_SIZE; ++j) {

      if (p->cells[i][j] == 0)
        continue;

      int board_x = p->pos.x + j;
      int board_y = p->pos.y + i;

      SDL_FRect rect = {.x = CELL_W * board_x + BOARD_X,
                        .y = CELL_H * board_y + BOARD_Y,
                        .w = CELL_W,
                        .h = CELL_H};

      draw_rect(rend, &rect, Piece_colors[p->type]);
    }
  }
}
Pos get_piece_pos(const Piece *p) {
  for (int i = 0; i < CELL_SIZE; ++i) {
    for (int j = 0; j < CELL_SIZE; ++j) {
      if (p->cells[i][j] == 0)
        continue;

      return (Pos){.x = p->pos.x + j, .y = p->pos.y + i};
    }
  }

  return (Pos){.x = -1, .y = -1};
}
void print_TT(Piece *p) {
  for (int i = 0; i < CELL_SIZE; i++) {
    for (int j = 0; j < CELL_SIZE; j++) {
      printf("%d ", p->cells[i][j]);
    }
    printf("\n");
  }
}
bool check_piece_valid(Game *g) {
  Piece *p = &g->curr;
  for (int i = 0; i < CELL_SIZE; i++) {
    for (int j = 0; j < CELL_SIZE; j++) {

      if (p->cells[i][j] == 0)
        continue;

      int board_x = p->pos.x + j;
      int board_y = p->pos.y + i;

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
  for (int i = 0; i < CELL_SIZE; ++i) {
    for (int j = 0; j < CELL_SIZE; ++j) {
      if (g->curr.cells[i][j] == 0)
        continue;
      g->board[g->curr.pos.y][g->curr.pos.x] = g->curr.type;
    }
  }
}

int get_type() { return rand() % TT_NUMS; }
void update(Game *g) {

  Piece *candidate = &g->curr;
  candidate->pos.y += 1;
  if (check_piece_valid(g)) {
    g->curr = *candidate;
  } else {
    lock_piece(g);
    g->curr = make_piece(get_type());
    //   spawn_piece(p);
    //   // }
  }
}
int main() {
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
  int type = get_type();
  printf("type generate: %d", type);
  game.curr = make_piece(type);

  init_board(&game);
  game.running = 1;
  u64 last_fall = SDL_GetTicks();
  while (game.running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_EVENT_QUIT:
        game.running = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        if ((e.key.mod & SDL_KMOD_CTRL) && e.key.key == SDLK_Z) {
          rotate_count_clockwise(game.curr.cells);
        }
        if (e.key.key == SDLK_X) {
          rotate_clockwise(game.curr.cells);
        }

        if (e.key.key == SDLK_LEFT) {
          Piece candidate = game.curr;
          candidate.pos.x--;

          if (check_piece_valid(&game)) {
            game.curr = candidate;
          }
        }

        if (e.key.key == SDLK_RIGHT) {
          Piece candidate = game.curr;
          candidate.pos.x++;

          if (check_piece_valid(&game)) {
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
    // SDL_Delay(1500);
  }
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
