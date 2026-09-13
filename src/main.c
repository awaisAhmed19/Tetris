#include "core.h"
#include "game.h"
#include "renderer.h"
#include "types.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>

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
  game_init(&game);
  u64 last_fall = SDL_GetTicks();
  print_board(&game.board);
  while (game.running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_EVENT_QUIT:
        game.running = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        if ((e.key.mod & SDL_KMOD_CTRL) && e.key.key == SDLK_Z) {
          game_cc_rotate(&game);
        }
        if (e.key.key == SDLK_SPACE) {
          game_hard_drop(&game);
        }
        if (e.key.key == SDLK_DOWN) {
          game_move_down(&game);
        }
        if (e.key.key == SDLK_X) {
          game_rotate(&game);
        }

        if (e.key.key == SDLK_LEFT) {
          game_move_left(&game);
        }

        if (e.key.key == SDLK_RIGHT) {
          game_move_right(&game);
        }
        if (e.key.key == SDLK_C) {
          game_hold(&game);
        }
        break;
      }
    }
    u64 now = SDL_GetTicks();
    if (now - last_fall > FALL_INTERVAL) {
      game_update(&game);
      last_fall = now;
    }
    SDL_SetRenderDrawColor(rend, black.r, black.g, black.b, black.a);
    SDL_RenderClear(rend);
    render_game(rend, &game);
    SDL_RenderPresent(rend);
  }
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
