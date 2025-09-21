#include "Game.h"

#include <iostream>

int scc(int code) {
    if (code < 0) {
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
    return code;
}

void* scp(void* code) {
    if (code == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
    return code;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    scc(SDL_Init(SDL_INIT_VIDEO));

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    } else {
        flags = SDL_WINDOW_SHOWN;
    }

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    scp(m_pWindow);

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    scp(m_pRenderer);

    m_brunning = true;
    return true;
}

void Game::update() {}
void Game::render() {
    SDL_RenderClear(m_pRenderer);
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_brunning = false;
                break;
            default:
                break;
        }
    }
}
