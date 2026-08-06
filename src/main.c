#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <stdlib.h>
#include <time.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

#define SCREENWIDTH 600
#define SCREENHEIGHT 680

#define CELL_W 28
#define CELL_H 28

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

#define HOLD_W 150
#define HOLD_H 150

#define HOLD_X 440
#define HOLD_Y 50
typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

typedef enum { CELL_EMPTY = 0, CELL_FILLED = 1 } cell_state;

const Color base_color = {.r = 28, .g = 28, .b = 28, .a = 255};
const Color teel = {.r = 51, .g = 196, .b = 175, .a = 255};
void draw_rect(SDL_Renderer *rend, SDL_FRect *rect, Color c) {
  SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
  SDL_RenderFillRect(rend, rect);
}

void init_board(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      board[i][j] = (i + j) % 2;
    }
  }
}

void draw_board(SDL_Renderer *rend, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
  const i16 paddingW = 150;
  const i16 paddingH = 50;
  Color c;
  for (int i = 0; i < BOARD_HEIGHT; ++i) {
    for (int j = 0; j < BOARD_WIDTH; ++j) {
      if (board[i][j]) {
        c = base_color;
      } else {
        c = (Color){.r = 200, .g = 200, .b = 200, .a = 255};
      }
      SDL_FRect rect = {.x = CELL_W * j + paddingW,
                        .y = CELL_H * i + paddingH,
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
  Color black = {.r = 0, .g = 0, .b = 0, .a = 0};
  int board[BOARD_HEIGHT][BOARD_WIDTH];
  init_board(board);
  bool running = true;
  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }
    SDL_SetRenderDrawColor(rend, black.r, black.g, black.b, black.a);
    SDL_RenderClear(rend);
    draw_board(rend, board);
    draw_hold_window(rend);
    SDL_RenderPresent(rend);
  }
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
