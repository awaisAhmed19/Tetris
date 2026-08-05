# Tetris in C + SDL3 + Vulkan

## Project Rules (Non-negotiable)

1.  **If Tetris doesn't need it, don't build it.**
2.  **No abstraction until the second duplication.**
3.  **No generic renderer.**
4.  **No ECS.**
5.  **No resource manager.**
6.  **No future-proofing.**
7.  **Ship ugly.**

------------------------------------------------------------------------

# Milestone 0 --- Build

## Goal

> Window opens.\
> Window closes.\
> Nothing else.

### Tasks

-   [X] CMake
-   [X] SDL3
-   [X] Vulkan SDK
-   [X] Compile shaders
-   [X] Run executable

**Done.**

------------------------------------------------------------------------

# Milestone 1 — First Pixel

## Goal

> Blue screen.

### Tasks

- [x] Initialize SDL
- [x] Create SDL window
- [x] Create SDL renderer
- [x] Set draw color to blue
- [x] Clear renderer
- [x] Present renderer
- [x] Handle quit event

**STOP. Commit.**

---

# Milestone 2 — Graphics Pipeline

## Goal

> Draw one white square.

### Tasks

- [ ] Understand the SDL render loop
- [ ] Create an `SDL_FRect` for a square
- [ ] Set draw color
- [ ] Draw filled rectangle
- [ ] Present frame every loop
- [ ] Clear screen every frame
- [ ] Maintain a fixed frame rate (or basic delta time)

**STOP. Commit.**

---

# Milestone 3 — Rendering Abstractions

## Goal

> Draw any square anywhere.

### Tasks

- [ ] Write `draw_rect(x, y, w, h, color)`
- [ ] Define a `Color` struct
- [ ] Draw multiple rectangles
- [ ] Verify drawing order

**STOP. Commit.**

---

# Milestone 4 — Grid Rendering

## Goal

> Render a 10 × 20 grid.

### Tasks

- [ ] Define cell size
- [ ] Convert grid coordinates → screen coordinates
- [ ] Write `draw_cell(x, y, color)`
- [ ] Render empty grid
- [ ] Render test cells

**STOP. Commit.**

---

# Milestone 5 — Board Rendering

## Goal

> Render the board array.

### Tasks

- [ ] Create `board[20][10]`
- [ ] Fill with test values
- [ ] Render every occupied cell
- [ ] Render active piece separately

**STOP. Commit.**
------------------------------------------------------------------------

# Milestone 2 --- Draw One Square

## Goal

> One square.\
> No board.\
> No game.

### Tasks

-   [ ] Vertex shader
-   [ ] Fragment shader
-   [ ] Graphics pipeline
-   [ ] Vertex buffer
-   [ ] Draw square

If one square appears, **commit immediately.**

------------------------------------------------------------------------

# Milestone 3 --- Move One Square

## Goal

> Arrow keys move square.

### Tasks

-   [ ] SDL input
-   [ ] Position variable
-   [ ] Delta time
-   [ ] Square moves

**Done.**

------------------------------------------------------------------------

# Milestone 4 --- Grid

## Goal

> 20 × 10 grid.

### Tasks

-   [ ] Cell size
-   [ ] `draw_cell()`
-   [ ] Draw grid
-   [ ] Draw test cells

Still **no Tetris.**

------------------------------------------------------------------------

# Milestone 5 --- Board

## Goal

``` c
int board[20][10];
```

### Tasks

-   [ ] Fill with random colors
-   [ ] Draw board

If it renders correctly, **commit.**

------------------------------------------------------------------------

# Milestone 6 --- One Tetromino

## Goal

Only implement the **I piece**.

### Tasks

-   [ ] Spawn
-   [ ] Move
-   [ ] Rotate

------------------------------------------------------------------------

# Milestone 7 --- Collision

### Tasks

-   [ ] Wall collision
-   [ ] Floor collision

Nothing else.

------------------------------------------------------------------------

# Milestone 8 --- Locking

### Tasks

-   [ ] Piece lands
-   [ ] Write into board

------------------------------------------------------------------------

# Milestone 9 --- Line Clear

### Tasks

-   [ ] Implement line clearing

One feature. Nothing else.

------------------------------------------------------------------------

# Milestone 10 --- Remaining Pieces

### Tasks

-   [ ] O
-   [ ] T
-   [ ] S
-   [ ] Z
-   [ ] L
-   [ ] J

------------------------------------------------------------------------

# Milestone 11 --- Rotation

### Tasks

-   [ ] Rotation
-   [ ] Wall kicks

------------------------------------------------------------------------

# Milestone 12 --- Gameplay

### Tasks

-   [ ] Gravity
-   [ ] Hard drop
-   [ ] Soft drop
-   [ ] Hold
-   [ ] Preview
-   [ ] Score
-   [ ] Levels
-   [ ] Game over

------------------------------------------------------------------------

# Milestone 13 --- Polish

### Tasks

-   [ ] Sound
-   [ ] Animation
-   [ ] Fonts
-   [ ] Pause
-   [ ] Settings

------------------------------------------------------------------------

# Golden Rule

> **If I stop forever after this milestone, I should still have
> something cool to show.**

Every milestone should leave the project in a demonstrable, working
state.
