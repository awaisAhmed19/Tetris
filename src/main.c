#include <SDL3/SDL.h>
#include <stdio.h>

#define SCREENWIDTH 600
#define SCREENHEIGHT 680
int main(int argc [[maybe_unused]], char *argv[]) {
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
  bool running = true;
  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }
    SDL_RenderClear(rend);
    SDL_RenderPresent(rend);
  }
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);

  // Clean up
  SDL_Quit();
  return 0;
}
