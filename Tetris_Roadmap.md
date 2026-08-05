# Tetris in C + SDL — TODO

## Milestone 0: Build
- [X] Set up CMake or Makefile
- [X] Link SDL3
- [X] Compile and run
- [X] COMMIT

## Milestone 1: Blue Screen
- [X] SDL_Init
- [X] SDL_CreateWindow
- [X] SDL_CreateRenderer (software 2D)
- [X] SDL_SetRenderDrawColor (blue)
- [X] SDL_RenderClear + SDL_RenderPresent loop
- [X] Handle SDL_QUIT event
- [X] Handle ESC key to quit
- [X] COMMIT

## Milestone 2: Draw Rectangles
- [X] Define `struct Color { uint8_t r, g, b, a; }`
- [X] Write `draw_rect(SDL_Renderer* r, float x, float y, float w, float h, Color c)`
- [X] Test: draw 5 rectangles at different positions/colors each frame
- [X] Clear screen before drawing each frame
- [ ] COMMIT

## Milestone 3: Grid & Board State
- [ ] Define `#define BOARD_WIDTH 10` and `#define BOARD_HEIGHT 20`
- [ ] Define `#define CELL_SIZE 32`
- [ ] Declare `int board[BOARD_HEIGHT][BOARD_WIDTH]`
- [ ] Write `draw_board(SDL_Renderer* r, int board[BOARD_HEIGHT][BOARD_WIDTH])`
- [ ] Map color 0 → dark gray (empty)
- [ ] Map colors 1–7 → piece colors
- [ ] Fill board with test pattern (random or alternating)
- [ ] Render board every frame
- [ ] COMMIT

## Milestone 4: I-Piece Spawn & Move
- [ ] Define `struct Piece { int x, y; int rotation; }`
- [ ] Define I-piece cells for rotation 0 (horizontal)
- [ ] Define I-piece cells for rotation 1 (vertical)
- [ ] Initialize piece: `Piece piece = {3, 0, 0}`
- [ ] Handle Left arrow: `piece.x--`
- [ ] Handle Right arrow: `piece.x++`
- [ ] Implement wall collision: `piece.x >= 0 && piece.x + width <= BOARD_WIDTH`
- [ ] Write `draw_piece(SDL_Renderer* r, Piece p, Color c)`
- [ ] Render board + active piece each frame
- [ ] COMMIT

## Milestone 5: Gravity & Floor Collision
- [ ] Track time with `SDL_GetTicks()` or delta time
- [ ] Every ~500ms, increment `piece.y`
- [ ] Detect floor collision: `piece.y + piece_height >= BOARD_HEIGHT`
- [ ] Detect board collision: check if piece cell overlaps `board[y][x] != 0`
- [ ] Stop piece from falling on collision
- [ ] COMMIT

## Milestone 6: Piece Locking & Next Piece
- [ ] On collision, write piece color into `board[][]` for each occupied cell
- [ ] Clear active piece state
- [ ] Spawn next I-piece at `{3, 0, 0}`
- [ ] Detect spawn collision (game over)
- [ ] Handle game over state (show message, allow restart)
- [ ] COMMIT

## Milestone 7: Line Clear
- [ ] After locking: scan each row for full lines
- [ ] Mark rows to clear
- [ ] Shift rows above down by N positions
- [ ] Clear top rows to 0
- [ ] COMMIT

## Milestone 8: Rotation (I-Piece)
- [ ] Track rotation state per piece
- [ ] Handle Up arrow: toggle rotation
- [ ] Recalculate piece cells based on rotation
- [ ] Check collision after rotation
- [ ] Reject rotation if blocked (no wall kick yet)
- [ ] COMMIT

## Milestone 9: All 7 Tetromino Shapes
- [ ] Define I-piece shape table
- [ ] Define O-piece shape table (no rotation)
- [ ] Define T-piece shape table (4 rotations)
- [ ] Define S-piece shape table (2 rotations)
- [ ] Define Z-piece shape table (2 rotations)
- [ ] Define L-piece shape table (4 rotations)
- [ ] Define J-piece shape table (4 rotations)
- [ ] Implement random piece selection: `rand() % 7`
- [ ] All pieces spawn, move, lock, and clear using same logic
- [ ] Assign unique color to each piece type
- [ ] COMMIT

## Milestone 10: Gravity Levels
- [ ] Track score (100 per line, 10 per lock)
- [ ] Calculate drop speed from score: `max(100, 500 - score/100)`
- [ ] Update gravity timer based on level
- [ ] Display score on screen
- [ ] COMMIT

## Milestone 11: Hard Drop & Soft Drop
- [ ] Handle Space key: instant drop to floor
- [ ] Write lock on hard drop
- [ ] Add score bonus for hard drop (+20 per cell)
- [ ] Handle Down arrow: increase gravity speed while held
- [ ] Add soft drop score (+1 per cell)
- [ ] COMMIT

## Milestone 12: Hold Piece
- [ ] Declare `Piece held` (null state)
- [ ] Handle C key: swap active piece with held
- [ ] Reset swapped piece to spawn position
- [ ] Enforce "hold once per lock" rule
- [ ] Write `draw_held(SDL_Renderer* r, Piece held)` in corner
- [ ] COMMIT

## Milestone 13: Preview Queue
- [ ] Maintain `int next_pieces[3]`
- [ ] On spawn: shift queue, randomize tail
- [ ] Write `draw_preview(SDL_Renderer* r, int next[3])` in corner
- [ ] COMMIT

## Milestone 14: Game Over & Restart
- [ ] Detect spawn collision → game over
- [ ] Render "GAME OVER" text centered
- [ ] Display final score
- [ ] Handle R key: reset board, score, resume
- [ ] Handle ESC key: quit
- [ ] COMMIT

## Milestone 15: Polish
- [ ] Render score, level, held piece, preview on screen
- [ ] Ensure distinct colors for each piece
- [ ] Add Pause (P key)
- [ ] Optional: smooth landing animation
- [ ] Tune speeds for fun gameplay
- [ ] COMMIT & SHIP

---

**Progress:**
- [ ] Milestone 0
- [ ] Milestone 1
- [ ] Milestone 2
- [ ] Milestone 3
- [ ] Milestone 4
- [ ] Milestone 5
- [ ] Milestone 6
- [ ] Milestone 7
- [ ] Milestone 8
- [ ] Milestone 9
- [ ] Milestone 10
- [ ] Milestone 11
- [ ] Milestone 12
- [ ] Milestone 13
- [ ] Milestone 14
- [ ] Milestone 15
