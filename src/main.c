#include "colors.h"
#include "core.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <tetrominos.h>
#include <time.h>
const Uint64 FALL_INTERVAL = 900;
int board[BOARD_HEIGHT][BOARD_WIDTH];

void draw_rect(SDL_Renderer *rend, SDL_FRect *rect, Color c) {
  SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
  SDL_RenderFillRect(rend, rect);
}

void init_board() {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      board[i][j] = 0;
    }
  }
}

void draw_board(SDL_Renderer *rend) {
  Color c;
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      c = (board[i][j]) ? Piece_colors[board[i][j] - 1] : base_color;
      SDL_FRect rect = {.x = CELL_W * j + BOARD_X,
                        .y = CELL_H * i + BOARD_Y,
                        .w = CELL_W,
                        .h = CELL_H};
      draw_rect(rend, &rect, c);
    }
  }
}

void draw_piece(SDL_Renderer *rend, Piece *p) {
  switch (p->type) {
  case TT_I:
    for (int i = 0; i < 4; i++) {
      int x = p->cell.x + (p->rotation ? I_rot1[i].x : I_rot0[i].x);
      int y = p->cell.y + (p->rotation ? I_rot1[i].y : I_rot0[i].y);
      SDL_FRect rect = {.x = CELL_W * x + BOARD_X,
                        .y = CELL_H * y + BOARD_Y,
                        .w = CELL_W,
                        .h = CELL_H};
      draw_rect(rend, &rect, Piece_colors[p->type - 1]);
    }
    break;
  case TT_O:
    break;
  case TT_T:
    break;
  case TT_S:
    break;
  case TT_Z:
    break;
  case TT_J:
    break;
  case TT_L:
    break;
  }
}

// void update() { board; }

void draw_hold_window(SDL_Renderer *rend) {
  SDL_FRect rect = {.x = HOLD_X, .y = HOLD_Y, .w = HOLD_W, .h = HOLD_H};
  SDL_SetRenderDrawColor(rend, base_color.r, base_color.g, base_color.b,
                         base_color.a);
  SDL_RenderFillRect(rend, &rect);
}

bool check_bounds(Piece *p) {
  switch (p->type) {
  case TT_I:
    return p->cell.x >= 0 && p->cell.x <= BOARD_WIDTH;
    break;
  case TT_O:
    break;
  case TT_T:
    break;
  case TT_S:
    break;
  case TT_Z:
    break;
  case TT_J:
    break;
  case TT_L:
    break;
  }
  return false;
}
bool check_piece_valid(Piece *c) { return true; }
void update(Piece *p) {

  Piece candidate = *p;
  candidate.cell.y++;
  *p = candidate;
  // if (check_piece_valid(&candidate)) {
  //   *p = candidate;
  // } else {
  //   // eventually:
  //   // lock_piece(p);
  //   // spawn_piece(p);
  // }
}
int main() {
  srand((unsigned)time(0));
  srand(2020);
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

  Piece p = {
      .cell.x = 0,
      .cell.y = 0,
      .type = 1,
      .rotation = 1,
  };

  init_board();
  // draw_piece(board, p);
  bool running = true;
  u64 last_fall = SDL_GetTicks();
  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_EVENT_QUIT:
        running = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (e.key.key == SDLK_A || e.key.key == SDLK_LEFT) {
          if (p.cell.x <= 0) {
            p.cell.x = 0;
          } else {
            p.cell.x--;
          }
          printf("P->x--: %d\n", p.cell.x);
        }
        if (e.key.key == SDLK_D || e.key.key == SDLK_RIGHT) {
          if (p.cell.x >= BOARD_WIDTH - 1 ||
              (p.rotation == 0 && p.cell.x >= BOARD_WIDTH - 4)) {
            p.cell.x = p.rotation ? BOARD_WIDTH - 1 : BOARD_WIDTH - 4;

          } else {
            p.cell.x++;
          }
          printf("P->x++: %d\n", p.cell.x);
        }
        if (e.key.key == SDLK_SPACE) {
          p.rotation = !(p.rotation);
        }
        printf("Key pressed: %d\n", e.key.key);
        break;
      }
    }
    u64 now = SDL_GetTicks();
    if (now - last_fall > FALL_INTERVAL) {
      update(&p);
      last_fall = now;
    }
    SDL_SetRenderDrawColor(rend, black.r, black.g, black.b, black.a);
    SDL_RenderClear(rend);
    draw_board(rend);
    draw_hold_window(rend);
    draw_piece(rend, &p);
    SDL_RenderPresent(rend);
    // SDL_Delay(1500);
  }
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
