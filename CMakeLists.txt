cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(ftxui REQUIRED)

# --- Source files ---
# Common code (logic, game rules, etc.)
file(GLOB COMMON_SRC src/game/*.cpp src/game/*.h)

# SDL-specific sources (put SDL code in src/sdl/)
file(GLOB SDL_SRC src/sdl/*.cpp src/sdl/*.h)

# FTXUI-specific sources (put terminal code in src/terminal/)
file(GLOB TERM_SRC src/terminal/*.cpp src/terminal/*.h)

# --- SDL Executable ---
add_executable(TetrisSDL main_sdl.cpp ${COMMON_SRC} ${SDL_SRC})
target_link_libraries(TetrisSDL PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
)

# --- Terminal Executable ---
add_executable(TetrisTerminal main_terminal.cpp ${COMMON_SRC} ${TERM_SRC})
target_link_libraries(TetrisTerminal PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)

# --- Run targets ---
add_custom_target(run_sdl
    COMMAND TetrisSDL
    DEPENDS TetrisSDL
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

add_custom_target(run_terminal
    COMMAND TetrisTerminal
    DEPENDS TetrisTerminal
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)


