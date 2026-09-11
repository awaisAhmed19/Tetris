# 🎮 Tetris Development Roadmap

This project is a Tetris clone written in **C (C23)** using **SDL3** (not C++/SDL2 — the
README currently describes the wrong stack, see `DOCS-001`). Core piece
movement, rotation (partially), locking, and line-clearing already work. This
file is the complete backlog for taking it from its current state to a
polished, stable, locally-playable Version 1.0, based on a full read-through
of `src/main.c`, `src/tetrominos.c`, `src/tetrominos.h`, `src/core.h`,
`src/colors.c`, `src/colors.h`, `src/types.h`, `CMakeLists.txt`, `build.sh`,
and `README.md`. No runtime testing was performed (no SDL3 environment was
available during this analysis) — anything that could only be confirmed by
running the game is explicitly marked as such below.

---

## 🔥 Currently Recommended Next Tasks

1. **[BUG-001] Fix clockwise rotation (X key) — it currently does nothing** 
   - Why now: One of the two rotation controls is non-functional. This is the single most impactful gameplay bug and is a small, self-contained fix.
2. **[BUG-002] Fix locked-piece color mismatch (L piece turns invisible)** 
   - Why now: Visually breaks the game the moment any piece other than I/O locks onto the board; small, isolated fix in `Piece_Color`.
3. **[BUG-003] Fix hard drop skipping through locked blocks** 
   - Why now: Can corrupt board state (pieces overlapping/passing through stacked blocks) and needs to be fixed before line-clearing and scoring work can be trusted.
4. **[CORE-001] Implement game-over detection** 
   - Why now: Right now the game cannot end. Every other gameplay-loop feature (scoring, restart, game-over screen) depends on this existing.
5. **[BUG-004] Fix lines-cleared counter (overwritten instead of accumulated)** 
   - Why now: `game.lines` is wrong today and `CORE-002` (scoring) will need a correct line count to compute points.

---

## 📊 Current Project Status

| System Status Notes               |                    |                                                                                                                                                                                                |
| --------------------------------- | ------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Build system (CMake + build.sh)   | 🟢 Complete        | Solid Debug/Release/RelWithDebInfo setup, ASan/UBSan in Debug. Some vestigial commented-out blocks from another project. See `BUILD-002`.                                                      |
| Board representation              | 🟢 Complete        | Simple `i16[20][10]` grid, correctly cleared/read.                                                                                                                                             |
| Tetromino shapes & spawning       | 🟢 Complete        | All 7 shapes correctly defined as 4x4 matrices, spawn position is centered.                                                                                                                    |
| Movement (left/right)             | 🟢 Complete        | Copy-validate-commit pattern used correctly.                                                                                                                                                   |
| Movement (soft drop)              | 🔴 Not implemented | No Down-arrow handler exists at all, despite README claiming it.                                                                                                                               |
| Movement (hard drop)              | 🟠 Buggy           | Space key works in the common case but can skip through blocks under overhangs. `BUG-003`.                                                                                                     |
| Rotation (CCW / Ctrl+Z)           | 🟢 Complete        | Correctly validates a copy before committing.                                                                                                                                                  |
| Rotation (CW / X)                 | 🔴 Buggy (broken)  | Mutates the live piece before validation; net effect is the rotation is silently reverted almost every time. `BUG-001`.                                                                        |
| Collision detection               | 🟢 Complete        | Handles left/right/bottom bounds, overlap, and above-board spawn correctly.                                                                                                                    |
| Piece locking                     | 🟡 Partial         | Works, but calls a full `print_board()` debug dump on every locked cell. `ARCH-001`.                                                                                                           |
| Line-clear detection & compaction | 🟢 Complete        | Correctly compacts the board even for multiple simultaneous full rows.                                                                                                                         |
| Lines-cleared counter             | 🟠 Buggy           | Overwritten, not accumulated, each clear event. `BUG-004`.                                                                                                                                     |
| Scoring                           | 🔴 Not implemented | `Game.score` field exists and is never written to.                                                                                                                                             |
| Level / speed progression         | 🔴 Not implemented | `Game.speed` field exists and is never written to; fall speed is a hardcoded constant.                                                                                                         |
| Hold piece                        | 🔴 Not implemented | An empty hold box is drawn; `Game.hold` is never set and there's no key binding.                                                                                                               |
| Next-piece preview                | 🔴 Not implemented | No queue, no preview UI.                                                                                                                                                                       |
| Ghost piece                       | 🔴 Not implemented | A `ghost` color constant exists but is unused.                                                                                                                                                 |
| Game-over detection               | 🔴 Not implemented | Nothing checks whether a freshly spawned piece already overlaps the stack.                                                                                                                     |
| Pause                             | 🔴 Not implemented | No key binding, no paused state.                                                                                                                                                               |
| Menus (main/pause/game-over)      | 🔴 Not implemented | Game boots directly into gameplay; there is no other screen.                                                                                                                                   |
| HUD text (score/level/lines)      | 🔴 Not implemented | `SDL3_ttf` is linked but never called anywhere in the code.                                                                                                                                    |
| Rendering pipeline (board/piece)  | 🟢 Complete        | Straightforward immediate-mode rectangle rendering; functional.                                                                                                                                |
| Audio                             | 🔴 Not implemented | No audio code, and no audio library is linked.                                                                                                                                                 |
| Automated tests                   | 🔴 Not implemented | No test files or framework anywhere in the repo.                                                                                                                                               |
| Documentation (README)            | 🟠 Inaccurate      | Describes C++/SDL2 (actual: C23/SDL3), lists controls that don't exist (Down arrow, Escape) and omits ones that do (Ctrl+Z, X), links a screenshot that doesn't exist in the repo. `DOCS-001`. |

---

## 🧭 Dependency Roadmap

```text
Board representation (done)
        ↓
Collision detection (done)
        ↓
Piece movement (done — left/right)   Rotation fixes (BUG-001)
        ↓                                     ↓
Hard-drop correctness (BUG-003)     Ghost piece (GAMEPLAY-005)
        ↓
Piece locking / line clearing (done)
        ↓
Lines counter fix (BUG-004) ──────────────┐
        ↓                                 ↓
Scoring (CORE-002)              Level/speed progression (GAMEPLAY-004)
        ↓                                 ↓
HUD text rendering (UI-001) ←─────────────┘
        ↓
Game-over detection (CORE-001) → Game-over screen (UI-002) → Restart (UI-004)
        ↓
Pause (INPUT-001) → Pause overlay (UI-003)
        ↓
Main menu (UI-005, optional) → Release prep (Phase 6)

```

Soft drop (`GAMEPLAY-001`), hold (`GAMEPLAY-002`), and next-piece preview
(`GAMEPLAY-003`) don't block anything above and can be done in parallel with
this chain whenever convenient.

---

# 🚨 Phase 0 — Critical Bugs and Technical Debt

### [X] BUG-001 — Fix clockwise rotation (X key) doing nothing

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 30–60 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

Pressing `X` (clockwise rotation) has no visible effect on the falling piece.

#### Current State

In `main.c`, the `SDLK_X` handler is:

```c
Piece candidate = game.curr;
rotate_clockwise(game.curr.cells);
if (check_piece_valid(&game, &candidate)) {
  game.curr = candidate;
}

```

`rotate_clockwise()` is called on `game.curr.cells` directly — the *live*
piece — instead of on `candidate.cells`. `candidate` was copied *before* the
mutation, so it still holds the un-rotated shape. `check_piece_valid` then
validates that unchanged, already-valid `candidate`, which almost always
passes, and `game.curr = candidate` overwrites the just-rotated `game.curr`
back to its un-rotated state. Net effect: the piece is rotated and then
immediately reverted every time, so `X` appears to do nothing. (Contrast
with the `Ctrl+Z` / `rotate_count_clockwise` handler a few lines above it,
which uses the correct copy → mutate copy → validate copy → commit pattern.)

#### Required Work

- [X] Change the `SDLK_X` handler to call `rotate_clockwise(candidate.cells)` instead of `rotate_clockwise(game.curr.cells)`, mirroring the `Ctrl+Z` handler's pattern.
- [X] Manually verify (run the game) that `X` visibly rotates the piece 90° clockwise when there is room to do so.
- [X] Manually verify that rotating against a wall or the stack is correctly rejected and leaves the piece unchanged.

#### Acceptance Criteria

- [X] Pressing `X` rotates the current piece 90° clockwise when the destination cells are free.
- [X] Pressing `X` next to a wall, the floor, or locked blocks leaves the piece in its original position and orientation (no crash, no out-of-bounds write).
- [X] `game.curr.cells` is never mutated in place before validation anywhere in the input-handling code.

#### Notes

This is the same class of bug the `Ctrl+Z` handler avoids — use it as the
reference implementation. This is a one-line fix but is high priority
because it's the most visible functional bug in the game.

---

### [X] BUG-002 — Fix locked-piece color mismatch (L piece becomes invisible)

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 30–60 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

Most tetromino types visibly change color the instant they lock onto the
board, and the `L` piece becomes nearly invisible (renders in the `ghost`
color, which has `alpha = 1`).

#### Current State

`make_piece()` in `tetrominos.c` assigns colors as: `TT_I`→cyan, `TT_O`→blue,
`TT_T`→green, `TT_S`→purple, `TT_Z`→yellow, `TT_J`→orange, `TT_L`→red.

`draw_board()` in `main.c` instead looks up the locked cell's color via
`Piece_Color[g->board[i][j]]`, indexed by the raw `enum TT_tetrominos` value.
`Piece_Color` is defined in `colors.c` as:

```c
const Color Piece_Color[8] = {base_color, cyan,  blue,   orange,
                              yellow,     green, purple, ghost};

```

i.e. index 1 (`TT_I`) → cyan ✅, index 2 (`TT_O`) → blue ✅, but index 3
(`TT_T`) → orange (should be green ❌), index 4 (`TT_S`) → yellow (should be
purple ❌), index 5 (`TT_Z`) → green (should be yellow ❌), index 6 (`TT_J`)
→ purple (should be orange ❌), and index 7 (`TT_L`) → `ghost`
(`{180,180,180,1}` — alpha of 1 out of 255, effectively invisible; should be
red ❌).

So the falling piece and the same piece once it locks show different colors
for every shape except `I` and `O`, and locked `L` pieces are nearly
invisible against the background.

#### Required Work

- [X] Reorder (or rebuild) the `Piece_Color` array in `colors.c` so that `Piece_Color[type]` matches the color `make_piece()` assigns for that `type` exactly: `Piece_Color[TT_I]=cyan`, `Piece_Color[TT_O]=blue`, `Piece_Color[TT_T]=green`, `Piece_Color[TT_S]=purple`, `Piece_Color[TT_Z]=yellow`, `Piece_Color[TT_J]=orange`, `Piece_Color[TT_L]=red`.
- [X] Consider indexing the array with the `enum TT_tetrominos` constants instead of positional literals (e.g. `[TT_I] = cyan`) so this can't silently drift out of sync again.
- [X] Manually verify (run the game) that every piece keeps the same color before and after locking.

#### Acceptance Criteria

- [ ] Every tetromino type shows the identical color while falling and after it locks onto the board.
- [ ] No locked piece renders using the `ghost` color.

#### Notes

Once this is fixed, also see `POLISH-006`, which cleans up the misleading
`// I` / `// J` / etc. comments next to the color definitions in `colors.c`
that don't match how the colors are actually used — leaving those in place
after this fix will make the next person re-introduce the same bug.

---

### [ ] BUG-003 — Fix hard drop skipping through locked blocks

**Priority:** P1 — High
**Difficulty:** 🟡 Medium
**Estimated effort:** 1–2 hours
**Dependencies:** None
**Status:** Not Started

#### Problem

Hard drop (`Space`) can, under certain stack shapes, move the piece past a
blocking cell into a lower position instead of stopping at the first
collision — i.e. the piece can appear to pass through part of the stack.

#### Current State

The `SDLK_SPACE` handler in `main.c`:

```c
Piece candidate = game.curr;
while (candidate.pos.y < BOARD_HEIGHT - 1) {
  candidate.pos.y++;
  if (check_piece_valid(&game, &candidate))
    game.curr = candidate;
}

```

This loop always runs until `candidate.pos.y` reaches `BOARD_HEIGHT - 1`,
regardless of whether `check_piece_valid` returned false partway through.
Because it never `break`s on the first invalid position, and `game.curr` is
only updated when a given `y` happens to be valid, a candidate position
below an overhang or blocking cell can still be recorded as the final
position if it happens to pass validation — the piece isn't guaranteed to
stop at the first row where it would collide.

**This has not been confirmed by running the game** — it is a logical read
of the loop, and would need a specific board layout (an overhang/gap
scenario) reproduced in-game to observe visually. It should still be fixed
regardless, since the current logic is not a correct "drop to first
collision" algorithm.

#### Required Work

- [ ] Rewrite the hard-drop logic to advance one row at a time and `break` immediately the first time a candidate position is invalid, keeping the last known-valid position as the final drop location.
- [ ] Add a bounds guard so the loop cannot run past `BOARD_HEIGHT - 1` regardless of validity.
- [ ] Manually test hard-dropping a piece onto a stack shaped so that a gap exists directly below an overhang, and confirm the piece stops on top of the overhang rather than falling into the gap beneath it.

#### Acceptance Criteria

- [ ] Hard drop always stops at the first row (from the piece's current position, moving downward) where the next position down would be invalid.
- [ ] Hard-dropping onto a flat surface still lands correctly (no regression).
- [ ] Hard-dropping under an overhang cannot place any part of the piece below a blocking cell that is directly above it.

#### Notes

This should be fixed before `CORE-002` (scoring) and `CORE-001` (game over)
are relied upon for correctness, since a corrupted board state from a bad
hard drop would make those systems behave unpredictably too.

---

### [ ] BUG-004 — Fix lines-cleared counter being overwritten instead of accumulated

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 30–60 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

`Game.lines` does not track the total number of lines cleared over the
course of the game — it only ever holds the count from the most recent
clear event.

#### Current State

In `update()` in `main.c`:

```c
for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
  if (is_row_full(g, y)) {
    g->lines = shift_row_below(g);
  }
}

```

`shift_row_below()` scans the *entire* board and returns the number of full
rows it just cleared in that single call. `g->lines` is *assigned* this
value (`=`), not added to it, so any lines cleared on a previous piece are
discarded the next time a line is cleared. There is also no display for
`lines` anywhere yet, so this hasn't been visibly noticed.

Separately (lower severity, note only): the surrounding `for` loop calls
`shift_row_below(g)` once per full row it encounters in its scan, but
`shift_row_below` already rescans and compacts *all* full rows on the board
in a single call. In practice this doesn't produce wrong results today (once
called, the board is already compacted so later iterations of the outer
loop won't find more full rows), but the loop is redundant and slightly
confusing — worth simplifying while this ticket is being worked.

#### Required Work

- [ ] Change `g->lines = shift_row_below(g);` to accumulate: `g->lines += shift_row_below(g);`.
- [ ] Simplify the surrounding loop so `shift_row_below(g)` is called at most once per `update()` (e.g. call it unconditionally once per tick and only add to `g->lines` if it returns a non-zero count), removing the redundant per-row rescanning.
- [ ] Manually verify (run the game, or via `print_board`) that clearing lines across multiple separate pieces produces a correctly increasing total.

#### Acceptance Criteria

- [ ] `Game.lines` reflects the cumulative total of lines cleared since the game started, not just the most recent clear.
- [ ] Clearing 1, 2, 3, then 4 lines (Tetris) in separate events each adds the correct amount to the running total.
- [ ] `shift_row_below()` is called at most once per game-loop `update()`.

#### Notes

`CORE-002` (scoring) will need this fixed first, since points typically
scale with how many lines were cleared in a single clear event *and* the
correct running total is useful for display purposes (`UI-001`).

---

### [ ] ARCH-001 — Remove debug board-dump from the piece-locking hot path

**Priority:** P2 — Medium
**Difficulty:** 🟢 Easy
**Estimated effort:** 15–30 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

`lock_piece()` prints the entire board to the console via `print_board(g)`
every time a single occupied cell is locked, meaning a 4-cell piece can
trigger up to 4 full board dumps per lock, every lock, for the entire game.

#### Current State

```c
void lock_piece(Game *g) {
  for (i16 i = 0; i < CELL_SIZE; ++i) {
    for (i16 j = 0; j < CELL_SIZE; ++j) {
      ...
      if (g->curr.cells[i][j] == 1 && ...) {
        g->board[board_y][board_x] = g->curr.type;
        print_board(g);
      }
    }
  }
}

```

This is clearly leftover debugging output from development (see the git
history: `"slam functionality complete line breaking done too"`), not
something intended for the shipped game loop.

#### Required Work

- [ ] Remove the `print_board(g);` call from inside `lock_piece()`.
- [ ] Decide whether `print_board()` and the one remaining call site (at startup, in `main()`) are still wanted for debugging, and if so, gate them behind a `#ifdef DEBUG_TETRIS` (or similar) compile-time flag instead of leaving unconditional `printf` calls in shipped code.

#### Acceptance Criteria

- [ ] Locking a piece no longer prints anything to the console during normal (non-debug) builds.
- [ ] The game's console output during normal play is silent (or limited to genuinely intentional debug output guarded by a build flag).

#### Notes

Small, quick win — pairs well with `BUG-001`/`BUG-002` as an easy first
session on this project.

---

### [ ] BUILD-001 — Remove stray scratch file `src/buff.txt`

**Priority:** P2 — Medium
**Difficulty:** 🟢 Easy
**Estimated effort:** 15 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

`src/buff.txt` is a `.txt` file containing an older, now-superseded draft of
`main.c` (it still uses the old `int board[BOARD_HEIGHT][BOARD_WIDTH]`
global-array design and an uninitialized `Piece *p` pointer, predating the
current `Game` struct). It is not picked up by the build (`CMakeLists.txt`
globs only `src/*.c`), but it sits in the source tree unexplained and isn't
excluded by `.gitignore`.

#### Current State

File exists at `src/buff.txt`, tracked or untracked (verify with
`git status`), 2.7 KB, not referenced by any build rule or other source
file.

#### Required Work

- [ ] Decide whether any part of `buff.txt` is still useful reference material; if not, delete it (`git rm src/buff.txt` if tracked).
- [ ] If it's worth keeping as historical reference, move it out of `src/` (e.g. into a `notes/` or `scratch/` directory) and add that directory to `.gitignore`.

#### Acceptance Criteria

- [ ] `src/` contains only files that are either part of the build or clearly-named documentation/assets.
- [ ] No stray draft/scratch files remain uncommented-on in `src/`.

#### Notes

Trivial cleanup; safe to batch with any other Phase 0 ticket.

---

# 🧱 Phase 1 — Core Game Completion

### [ ] CORE-001 — Implement game-over detection

**Priority:** P1 — High
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–4 hours
**Dependencies:** BUG-003 (fix hard drop first so the board state feeding
into this is trustworthy)
**Status:** Not Started

#### Problem

The game has no way to end. A new piece is always spawned via
`spawn_piece()` regardless of whether the spawn location is already
occupied by locked blocks, and nothing checks for a "topped out" board.

#### Current State

```c
void spawn_piece(Game *g) { g->curr = make_piece(get_type()); }

```

This directly assigns the new piece with no call to `check_piece_valid()`.
If the stack has risen high enough that the spawn area overlaps locked
cells, the new piece will simply be given an already-invalid position; the
very next `update()` tick will find any downward movement invalid too
(since the current position already overlaps), locking it again
immediately, and the loop repeats forever with no indication to the player
that the game has ended.

#### Required Work

- [ ] Add a `game_over` flag (or a `GameState` enum with at least `PLAYING` / `GAME_OVER` values) to the `Game` struct in `core.h`.
- [ ] In `spawn_piece()` (or immediately after calling it), check the new piece's position with `check_piece_valid()`; if invalid, set the game to the game-over state instead of continuing play.
- [ ] Stop advancing gameplay (piece falling, input-driven movement) once the game-over state is set, while still allowing the render loop to keep running (so a game-over screen — `UI-002` — can be shown).
- [ ] Manually verify (run the game, deliberately stack pieces to the top) that the game correctly detects and stops at the top-out condition.

#### Acceptance Criteria

- [ ] When a newly spawned piece would immediately overlap a locked cell, the game enters a game-over state instead of silently re-locking forever.
- [ ] No further piece movement, rotation, or falling occurs once the game is over.
- [ ] The game does not crash or corrupt the board when top-out occurs.

#### Notes

This unlocks `UI-002` (game-over screen) and `UI-004` (restart), and is a
prerequisite for treating this as a real, finishable game rather than an
endless simulation.

---

### [ ] CORE-002 — Implement a scoring system

**Priority:** P1 — High
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–4 hours
**Dependencies:** BUG-004 (correct lines-cleared count feeds scoring)
**Status:** Not Started

#### Problem

`Game.score` is declared in `core.h` but is never written to anywhere in
the codebase — there is currently no scoring at all.

#### Current State

```c
typedef struct {
  ...
  i16 score;
  ...
} Game;

```

No function reads or writes `score`. Line clears, drops, and locks award no
points.

#### Required Work

- [ ] Decide on a scoring table (a simple, standard-ish scheme is fine for v1, e.g. points-per-line-clear that scale with lines cleared at once: 1 line / 2 lines / 3 lines / 4 lines award increasing amounts).
- [ ] Award points when `shift_row_below()` reports lines cleared (from the fixed `update()` logic in `BUG-004`).
- [ ] Optionally award small points for soft drop / hard drop distance (only once `GAMEPLAY-001` soft drop exists).
- [ ] Consider whether `i16` (max 32,767) is a wide enough type for `score` given the chosen scoring table and expected play sessions — widen to `i32`/`u32` in `core.h` if there's a realistic risk of overflow.
- [ ] Manually verify (run the game) that clearing lines increases the score by the expected amount.

#### Acceptance Criteria

- [ ] Clearing lines increases `Game.score` by a well-defined, documented amount.
- [ ] Score never decreases during play and doesn't wrap/overflow under normal play session lengths.
- [ ] The scoring rule is written down somewhere (a comment near the table, or in `README.md`) so it isn't a mystery later.

#### Notes

Depends on `BUG-004` being fixed first so the per-clear line count passed
into the scoring calculation is correct. Feeds directly into `UI-001` (HUD
display).

---

# 🎮 Phase 2 — Complete Gameplay

### [ ] GAMEPLAY-001 — Implement soft drop

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 1–2 hours
**Dependencies:** None
**Status:** Not Started

#### Problem

The README advertises Down Arrow as "soft drop," but no `SDLK_DOWN` case
exists anywhere in the input handling in `main.c`.

#### Current State

The `SDL_EVENT_KEY_DOWN` switch handles `Ctrl+Z`, `Space`, `X`, `Left`, and
`Right` only. There is no case for `SDLK_DOWN`.

#### Required Work

- [ ] Add an `SDLK_DOWN` case that moves the current piece down by one row (same copy-validate-commit pattern used by left/right), and locks it immediately via the normal `update()` path if that move is invalid.
- [ ] Decide whether soft drop should be a discrete per-keypress nudge or a continuous fast-fall while the key is held (the latter needs the key to be tracked as "currently down" across frames, not just on the `SDL_EVENT_KEY_DOWN` event, since that event fires once per press unless OS key-repeat is relied on).
- [ ] Manually verify (run the game) that Down Arrow drops the piece faster than the normal fall rate and stops correctly at the first collision.

#### Acceptance Criteria

- [ ] Holding or pressing Down Arrow moves the piece downward faster than the normal automatic fall.
- [ ] Soft drop respects collision the same way normal falling does (no passing through blocks).
- [ ] README's controls table (once corrected in `DOCS-001`) accurately describes the final soft-drop behavior.

#### Notes

If you want soft-drop to award small points per cell dropped, note that
dependency in `CORE-002` when you get there.

---

### [ ] GAMEPLAY-002 — Implement hold-piece mechanic

**Priority:** P2 — Medium
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–4 hours
**Dependencies:** None (can be done independently, but pairs naturally with
`GAMEPLAY-003` since both touch piece-queue-adjacent state)
**Status:** Not Started

#### Problem

A hold box is drawn (`draw_hold_window()`) but there is no way to actually
hold a piece — `Game.hold` is never assigned, and there's no key binding for
it.

#### Current State

```c
void draw_hold_window(SDL_Renderer *rend) {
  SDL_FRect rect = {.x = HOLD_X, .y = HOLD_Y, .w = HOLD_W, .h = HOLD_H};
  SDL_SetRenderDrawColor(rend, base_color.r, base_color.g, base_color.b,
                         base_color.a);
  SDL_RenderFillRect(rend, &rect);
}

```

This only ever paints an empty rectangle; `Game.hold` (declared in
`core.h`) is unused everywhere else in the code.

#### Required Work

- [ ] Pick a key binding for hold (e.g. `C` or `Shift`, and update the README controls table in `DOCS-001` to match).
- [ ] On hold: if `Game.hold` is empty, move the current piece into hold and spawn a new piece; if `Game.hold` already has a piece, swap it with the current piece (re-spawned at the top, not at its old position).
- [ ] Add a "used hold this piece" flag so the player can't hold repeatedly with the same piece to stall indefinitely (standard Tetris hold rule: one hold per piece, reset when a piece locks).
- [ ] Render the held piece's shape inside the hold box (reuse/extend `draw_piece()` or a small variant of it that draws at a fixed position instead of `p->pos`).
- [ ] Manually verify (run the game) hold/swap/re-spawn behavior, including that hold can't be spammed within a single piece's lifetime.

#### Acceptance Criteria

- [ ] Pressing the hold key with an empty hold slot stores the current piece and spawns the next piece.
- [ ] Pressing the hold key with a filled hold slot swaps the current piece with the held piece.
- [ ] The hold slot visually displays the held piece's shape and color.
- [ ] Hold cannot be used more than once per spawned piece.

#### Notes

This is "Recommended before v1.0," not strictly required — the game is
playable without it, but it's a well-understood, self-contained feature
that meaningfully improves the feel of the game.

---

### [ ] GAMEPLAY-003 — Implement next-piece preview

**Priority:** P2 — Medium
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–4 hours
**Dependencies:** None
**Status:** Not Started

#### Problem

There is no way for the player to see what piece is coming next; pieces are
generated one at a time, on demand, with no queue.

#### Current State

`spawn_piece()` calls `make_piece(get_type())` at the moment a piece is
needed — there's no lookahead buffer of any kind.

#### Required Work

- [ ] Introduce a small piece queue (even a single-item lookahead is a reasonable v1 scope; a queue of 3 is a common standard if you want to go further).
- [ ] Generate the "next" piece(s) ahead of time and have `spawn_piece()` pull from the front of the queue instead of generating on demand.
- [ ] Reserve a preview UI area (similar to `draw_hold_window`) and draw the next piece's shape and color there.
- [ ] Manually verify (run the game) that the piece shown in the preview always matches the piece that spawns next.

#### Acceptance Criteria

- [ ] A preview box on screen always shows at least the next piece to spawn.
- [ ] The previewed shape/color always matches what actually spawns.

#### Notes

If you implement `POLISH-002` (7-bag randomizer) around the same time,
build the queue on top of the bag generator rather than pure `rand()`, since
both features touch the same piece-generation code path.

---

### [ ] GAMEPLAY-004 — Implement level/speed progression

**Priority:** P1 — High
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–3 hours
**Dependencies:** BUG-004 (needs a correct cumulative lines count)
**Status:** Not Started

#### Problem

The game never speeds up. `Game.speed` is declared but unused, and
`FALL_INTERVAL` is a single `const u64` that never changes over the course
of a game.

#### Current State

```c
const u64 FALL_INTERVAL = 300;
...
if (now - last_fall > FALL_INTERVAL) {
  update(&game);
  last_fall = now;
}

```

There's no notion of "level," and the fall interval is fixed for the entire
session.

#### Required Work

- [ ] Define a level-up rule (e.g. one level per N lines cleared — 10 is a common choice).
- [ ] Compute the current level from `Game.lines` (once `BUG-004` makes that value trustworthy) and store it, or derive it on the fly.
- [ ] Replace the constant `FALL_INTERVAL` with a value derived from the current level (decreasing interval = faster fall), and use that value in place of the hardcoded `300` in the main loop's timing check.
- [ ] Put a reasonable floor on how fast the fall interval can get so it never becomes literally unplayable or causes timing issues at very high levels.
- [ ] Manually verify (run the game) that clearing enough lines visibly speeds up the fall rate.

#### Acceptance Criteria

- [ ] The piece fall speed increases as more lines are cleared, following a documented level rule.
- [ ] There is a defined minimum fall interval that speed progression will never go below.
- [ ] `Game.speed` (or an equivalent field) reflects the current level/speed and is available for display in `UI-001`.

#### Notes

Depends on `BUG-004` for a correct lines total to base leveling on.

---

### [ ] GAMEPLAY-005 — Implement ghost piece (landing-position preview)

**Priority:** P2 — Medium
**Difficulty:** 🟢 Easy
**Estimated effort:** 1–2 hours
**Dependencies:** BUG-003 (needs correct drop-to-bottom logic)
**Status:** Not Started

#### Problem

There's no visual indicator of where the current piece will land, which
makes hard drops (and planning in general) harder than necessary. A `ghost`
color constant already exists in `colors.c` but is currently unused for
its evident intended purpose (it's presently misused as a board-index
color in the `BUG-002` bug).

#### Current State

`extern const Color ghost;` is declared and defined but never referenced by
any drawing function.

#### Required Work

- [ ] Compute the landing position of the current piece (essentially the same "drop to first collision" logic being corrected in `BUG-003`, but without committing the move).
- [ ] Draw the piece's shape at that landing position using the `ghost` color, before drawing the actual falling piece on top of it.
- [ ] Manually verify (run the game) that the ghost outline always matches where a hard drop would actually place the piece.

#### Acceptance Criteria

- [ ] A ghost outline is rendered at the piece's eventual landing position at all times during play.
- [ ] The ghost outline always matches where a hard drop (`Space`) would actually place the piece.
- [ ] The ghost piece does not interfere with collision detection for the real, active piece.

#### Notes

Share the drop-position calculation with `BUG-003`'s fix rather than
writing a second, separate implementation — factor it into a small
`get_drop_position()`-style helper used by both.

---

### [ ] INPUT-001 — Add pause functionality

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 1–2 hours
**Dependencies:** None
**Status:** Not Started

#### Problem

There is no way to pause the game. Once started, the only way to stop
playing is to quit.

#### Current State

No paused state exists anywhere in `Game` or the main loop.

#### Required Work

- [ ] Add a `paused` flag (or extend a `GameState` enum, sharing it with the `game_over` state added in `CORE-001` if that's convenient) to `Game`.
- [ ] Bind a key (e.g. `P` or `Escape`, coordinate with `INPUT-002`) to toggle pause.
- [ ] While paused, skip the fall-timer update and piece-movement input, but keep rendering (so `UI-003`'s pause overlay can be shown, and so Escape/quit still works while paused).
- [ ] Manually verify (run the game) that pausing freezes the falling piece and that unpausing resumes exactly where it left off (falling timer should not "jump" — reset `last_fall` on unpause).

#### Acceptance Criteria

- [ ] Pressing the pause key stops the piece from falling or responding to movement/rotation input.
- [ ] Pressing the pause key again resumes play without an unintended immediate fall-tick or piece jump.
- [ ] The game cannot be paused after game-over (or pausing there is a no-op).

#### Notes

Feeds `UI-003` (pause overlay). Keep this ticket scoped to the state/logic
only — the overlay UI is a separate ticket.

---

### [ ] INPUT-002 — Add missing controls and fix README/actual mismatch

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 1–2 hours
**Dependencies:** None
**Status:** Not Started

#### Problem

The current control scheme doesn't match the README at all, and some
expected basics (quit-via-keyboard) are missing.

#### Current State

Actual bound keys today: `Ctrl+Z` (rotate CCW), `X` (rotate CW, currently
broken — see `BUG-001`), `Space` (hard drop), `Left`/`Right` (move). The
README instead documents Up Arrow (rotate), Down Arrow (soft drop), and
Escape (quit) — none of which exist in the code. There is no way to quit
via a keyboard key at all right now (only the window's close button, via
`SDL_EVENT_QUIT`).

#### Required Work

- [ ] Decide on a final control scheme (this ticket is a good place to settle it, since `GAMEPLAY-001` (soft drop), `GAMEPLAY-002` (hold), and `INPUT-001` (pause) all need key bindings too).
- [ ] Add an `SDLK_ESCAPE` handler that quits the game (or opens a pause menu first, if you'd rather it not be an instant-quit).
- [ ] Consider adding basic key-repeat/DAS (delayed auto-shift) for left/right movement so holding the key moves the piece continuously instead of one cell per keypress (tracked separately as `POLISH-001` if you want to scope it out of this ticket).
- [ ] Update `README.md`'s controls table to match whatever the final scheme ends up being (tracked in `DOCS-001`, but do it here too if it's faster to keep in sync as you go).

#### Acceptance Criteria

- [ ] Every control mentioned in the README actually works exactly as described, and every working control is mentioned in the README.
- [ ] There is a keyboard-only way to quit the game.

#### Notes

Do this after `GAMEPLAY-001`/`GAMEPLAY-002`/`INPUT-001` are far enough along
that you know the full final key list, so you're not updating the README
table twice.

---

# 🖥️ Phase 3 — User Interface and Experience

### [ ] UI-001 — Implement HUD text rendering for score, level, and lines

**Priority:** P1 — High
**Difficulty:** 🟠 Hard
**Estimated effort:** 4–8 hours
**Dependencies:** CORE-002 (scoring), GAMEPLAY-004 (level/speed)
**Status:** Not Started

#### Problem

There is no on-screen display of score, level, or lines cleared, and no
text rendering of any kind happens anywhere in the game, despite `SDL3_ttf`
already being linked as a dependency in `CMakeLists.txt`.

#### Current State

`grep`-ing the source for `TTF`/`ttf` turns up no matches — the dependency
is present in the build but completely unused.

#### Required Work

- [ ] Add a `.ttf` font file to the project (a permissively-licensed font; note there is no `assets/` directory in the repo currently, so decide where fonts should live and how they'll be located at runtime — see `BUILD-002` regarding the currently-vestigial `LX_ASSET_DIR` setup).
- [ ] Initialize `SDL3_ttf`, load the font once at startup, and clean it up on shutdown alongside the existing window/renderer teardown.
- [ ] Render current score, level, and lines-cleared as text in the UI area next to the board (there's existing unused screen space to the right of the board, near the hold box).
- [ ] Update these values' rendered text only when they change (or simply re-render every frame if performance isn't a concern at this scale — call this out as a decision in the PR/commit, not something to silently pick).
- [ ] Manually verify (run the game) that displayed values track the real score/level/lines state as the game progresses.

#### Acceptance Criteria

- [ ] Score, level, and lines-cleared are all visible on screen at all times during play.
- [ ] Displayed values update correctly and immediately when they change.
- [ ] Font loading failure is handled gracefully (a clear error message, not a silent crash) rather than an unchecked null-pointer dereference.

#### Notes

This is the largest single ticket in the backlog difficulty-wise, mostly
because it's the first time text rendering is introduced into the project
at all — everything after this point that needs text (game-over screen,
pause overlay, main menu) becomes much cheaper once the font-loading and
text-drawing groundwork exists here.

---

### [ ] UI-002 — Implement game-over screen

**Priority:** P1 — High
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–4 hours
**Dependencies:** CORE-001 (game-over detection), UI-001 (text rendering)
**Status:** Not Started

#### Problem

There is no visual indication that the game has ended.

#### Current State

No game-over rendering path exists; see `CORE-001` for the missing
detection logic this depends on.

#### Required Work

- [ ] When `Game`'s game-over state (added in `CORE-001`) is set, render an overlay (e.g. a semi-transparent panel over the board) showing "Game Over," the final score, and a prompt to restart.
- [ ] Stop rendering the falling piece and hold/next previews while this overlay is shown (or leave the frozen final board visible underneath it — a purely visual choice, either is fine for v1).
- [ ] Manually verify (run the game, top out deliberately) that the overlay appears immediately and displays the correct final score.

#### Acceptance Criteria

- [ ] A clear "Game Over" state is visibly shown the moment `CORE-001`'s detection triggers.
- [ ] The final score is displayed on this screen.
- [ ] The board underneath stops updating (no further pieces spawn or fall) while this screen is shown.

#### Notes

Depends on `UI-001` for the text-rendering plumbing to already exist.

---

### [ ] UI-003 — Implement pause overlay

**Priority:** P2 — Medium
**Difficulty:** 🟢 Easy
**Estimated effort:** 1–2 hours
**Dependencies:** INPUT-001 (pause state), UI-001 (text rendering)
**Status:** Not Started

#### Problem

Once `INPUT-001` adds a pause state, there's currently no visual indication
that the game is paused versus just not receiving input.

#### Current State

N/A — depends on `INPUT-001` existing first.

#### Required Work

- [ ] When paused, render a simple overlay (e.g. "Paused — press P to resume") over the frozen board.
- [ ] Manually verify (run the game) that the overlay appears exactly when paused and disappears exactly when resumed.

#### Acceptance Criteria

- [ ] A visible indicator distinguishes "paused" from normal play at all times while paused.
- [ ] The overlay disappears immediately on resume.

#### Notes

Small ticket once `UI-001`'s text rendering exists — mostly reuses that
plumbing.

---

### [ ] UI-004 — Implement restart functionality

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 1–2 hours
**Dependencies:** CORE-001 (game-over state), UI-002 (game-over screen)
**Status:** Not Started

#### Problem

Once a game ends, the only way to play again is to relaunch the
application.

#### Current State

No reset path exists for `Game` state after game-over.

#### Required Work

- [ ] Add a "reset game" function that re-initializes the board, score, lines, level, hold slot, and spawns a fresh piece — essentially redoing the relevant parts of the existing startup sequence in `main()` without recreating the SDL window/renderer.
- [ ] Bind a key on the game-over screen (e.g. `Enter` or `R`) to trigger this reset.
- [ ] Manually verify (run the game) that restarting after game-over produces a genuinely fresh game (empty board, zero score, level 1) and not a game that inherits leftover state.

#### Acceptance Criteria

- [ ] Pressing the restart key from the game-over screen returns to normal gameplay with a fully reset board, score, lines, and level.
- [ ] No state from the previous game (locked cells, old score, etc.) leaks into the new game.

#### Notes

Depends on `UI-002` existing so there's a screen to trigger the restart
from.

---

### [ ] UI-005 — Implement a basic main menu / start screen

**Priority:** P3 — Low (Recommended, not required)
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–4 hours
**Dependencies:** UI-001 (text rendering)
**Status:** Not Started

#### Problem

The game currently launches directly into active gameplay with no start
screen.

#### Current State

`main()` initializes SDL, the board, and the first piece, then immediately
enters the game loop — there is no intermediate menu state.

#### Required Work

- [ ] Add a simple "press any key / Enter to start" screen shown before the first piece spawns.
- [ ] Optionally show basic controls or a title graphic on this screen.
- [ ] Manually verify (run the game) that the menu appears on launch and transitions cleanly into gameplay.

#### Acceptance Criteria

- [ ] The game shows a start screen before gameplay begins on launch.
- [ ] Starting from this screen behaves identically to how gameplay starts today (no regressions to initialization).

#### Notes

This is explicitly optional for v1.0 — a locally playable, complete Tetris
game doesn't strictly need a title screen, but it's a natural, low-risk
polish item once the text-rendering and screen/overlay patterns already
exist from `UI-001`–`UI-003`.

---

# ✨ Phase 4 — Polish

### [ ] POLISH-001 — Add key-repeat / DAS for left/right movement

**Priority:** P2 — Medium
**Difficulty:** 🟡 Medium
**Estimated effort:** 2–3 hours
**Dependencies:** None
**Status:** Not Started

#### Problem

Left/right movement only responds to the discrete `SDL_EVENT_KEY_DOWN`
event, so moving multiple cells requires repeatedly pressing the key rather
than holding it.

#### Current State

Movement handlers live entirely inside the `SDL_EVENT_KEY_DOWN` case of the
event-polling switch, which fires once per physical key press (subject to
OS-level key-repeat settings, which aren't something this game controls).

#### Required Work

- [ ] Track left/right key-held state across frames (e.g. via `SDL_GetKeyboardState`) rather than relying solely on discrete key-down events.
- [ ] Implement a short initial delay before repeat starts, then a faster repeat rate, matching the standard "DAS" (delayed auto-shift) feel players expect from Tetris games.
- [ ] Manually verify (run the game) that holding left/right feels responsive and doesn't move the piece too fast to control precisely.

#### Acceptance Criteria

- [ ] Holding Left or Right continuously moves the piece after a short initial delay, without needing repeated key presses.
- [ ] The repeat rate is tunable via a small number of named constants (not magic numbers scattered through the input code).

#### Notes

Purely a feel/quality improvement — the game is fully playable without it.

---

### [ ] POLISH-002 — Add 7-bag randomizer for piece generation

**Priority:** P3 — Low
**Difficulty:** 🟡 Medium
**Estimated effort:** 1–2 hours
**Dependencies:** None
**Status:** Not Started

#### Problem

Piece generation uses uniform `rand()` with rejection sampling to avoid
`CELL_EMPTY`, which can produce long unlucky streaks without a particular
piece (or long lucky streaks of the same piece) purely by chance.

#### Current State

```c
i16 get_type() {
  i16 type = rand() % TT_NUMS;
  while (type == 0) {
    type = rand() % TT_NUMS;
  }
  return type;
}

```

#### Required Work

- [ ] Implement a "bag" randomizer: shuffle all 7 piece types together, hand them out one at a time, and reshuffle a fresh bag once it's empty (this is the standard modern Tetris piece-generation approach and guarantees every piece appears exactly once per 7 spawns).
- [ ] Integrate this with `GAMEPLAY-003`'s next-piece queue if that's been implemented by this point, since both touch the same generation path.
- [ ] Manually verify (run the game, or add a temporary debug print) that each of the 7 piece types appears exactly once before any repeats.

#### Acceptance Criteria

- [ ] Every 7 consecutive pieces generated contain each of the 7 tetromino types exactly once.
- [ ] The bag reshuffles automatically and transparently once exhausted.

#### Notes

Purely a fairness/feel improvement; not required for a functionally
complete v1.0.

---

### [ ] POLISH-003 — Fix resource leak on renderer-creation failure

**Priority:** P3 — Low
**Difficulty:** 🟢 Easy
**Estimated effort:** 15–30 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

If window creation succeeds but renderer creation fails, `main()` returns
without destroying the already-created window.

#### Current State

```c
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

```

In the `!rend` branch, `win` is non-null but is never passed to
`SDL_DestroyWindow` before returning.

#### Required Work

- [ ] Call `SDL_DestroyWindow(win)` (and `SDL_Quit()`) before returning in the `!rend` failure branch.

#### Acceptance Criteria

- [ ] All SDL resources that were successfully created are properly destroyed on every exit path, including early-failure paths.

#### Notes

Low real-world impact (the process is about to exit anyway and the OS will
reclaim the resources), but cheap and correct to fix, and good practice for
when this code inevitably gets refactored into a longer-lived structure.

---

### [ ] POLISH-004 — Fix `main()`'s non-standard return type

**Priority:** P3 — Low
**Difficulty:** 🟢 Easy
**Estimated effort:** 15 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

`main()` is declared as `i16 main()` (i.e. `int16_t`) instead of the
standard `int main(void)` (or `int main(int argc, char **argv)`).

#### Current State

```c
i16 main() {
  ...
  return 0;
}

```

`CMakeLists.txt` compiles with `-Wall -Wextra -Wpedantic`, which is likely
to emit a "return type of 'main' is not 'int'" warning on GCC/Clang given
this signature (**not confirmed by an actual build in this analysis** — no
SDL3 installation was available to compile the project during inspection).
Even where a compiler tolerates it, returning anything other than `int`
from `main` is technically undefined behavior at the point the C runtime
reads the process exit code.

#### Required Work

- [ ] Change the signature to `int main(void)` (the program doesn't currently use `argc`/`argv`).
- [ ] Rebuild and confirm no new warnings are introduced by this change and that all existing warnings-as-info remain otherwise unchanged.

#### Acceptance Criteria

- [ ] `main` is declared with a standard `int` return type.
- [ ] The project builds cleanly with the project's existing `-Wall -Wextra -Wpedantic` flags with no new warnings introduced by this change.

#### Notes

Trivial, but worth doing before tagging a v1.0 release for portability and
standards-compliance.

---

### [ ] POLISH-005 — Remove or wire up dead code (`get_piece_pos`, `print_TT`)

**Priority:** P3 — Low
**Difficulty:** 🟢 Easy
**Estimated effort:** 15–30 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

`get_piece_pos()` and `print_TT()` are both fully defined in `main.c` but
are never called anywhere in the codebase.

#### Current State

Confirmed via search: both function names appear only at their own
definitions in `main.c`, with no call sites anywhere in `src/`.

#### Required Work

- [ ] Either remove both functions if they're no longer useful, or find a genuine use for them (e.g. `print_TT` could be wired into a debug flag alongside `ARCH-001`'s `print_board` gating, for dumping a piece's current rotation matrix during development).
- [ ] If kept for debugging purposes, gate them the same way as `ARCH-001`'s `print_board`/`printf` debug output, so they don't ship as unconditional dead weight either way.

#### Acceptance Criteria

- [ ] No unused, uncalled functions remain in the codebase without an explicit reason (a comment or a debug-flag gate) for keeping them.

#### Notes

Purely a housekeeping item; safe to batch with `ARCH-001` in the same
session.

---

### [ ] POLISH-006 — Fix scrambled color-name comments in `colors.c`

**Priority:** P3 — Low
**Difficulty:** 🟢 Easy
**Estimated effort:** 15 minutes
**Dependencies:** BUG-002 (fix the actual color-mapping bug first)
**Status:** Not Started

#### Problem

The inline comments next to each `Color` constant in `colors.c` (e.g.
`// I`, `// J`, `// L`, `// O`, `// S`, `// T`, `// Z`) don't match how those
colors are actually used for each tetromino type in `tetrominos.c`'s
`make_piece()`.

#### Current State

For example, `blue` is commented `// J` in `colors.c`, but `make_piece()`
actually assigns `blue` to `TT_O`. Similar mismatches exist for most of the
other colors (see `BUG-002`'s investigation for the full list of what's
actually assigned where).

#### Required Work

- [ ] Once `BUG-002` is fixed and the final color-to-tetromino mapping is settled, update each comment in `colors.c` to name the tetromino type it's actually used for.

#### Acceptance Criteria

- [ ] Every color constant's inline comment in `colors.c` correctly identifies the tetromino type it's used for in `make_piece()`.

#### Notes

Do this immediately after `BUG-002`, while the correct mapping is fresh, to
avoid the comments drifting out of sync again.

---

# 🧪 Phase 5 — Testing and Stability

### [ ] TEST-001 — Write a manual smoke-test checklist

**Priority:** P2 — Medium
**Difficulty:** 🟢 Easy
**Estimated effort:** 1 hour
**Dependencies:** None
**Status:** Not Started

#### Problem

There is currently no repeatable procedure for manually verifying that core
mechanics still work after a change — every bug fix and feature in this
backlog has had to be reasoned about from source alone rather than
confirmed by running the game, since no test procedure or automated test
exists.

#### Current State

No test documentation of any kind exists in the repository.

#### Required Work

- [ ] Write a short `TESTING.md` (or a section in `README.md`) listing the manual checks worth running before considering a build "good": each piece spawns and rotates both directions correctly, left/right/soft/ hard drop all behave correctly near walls and the stack, single and multi-line clears compact the board correctly, game-over triggers at top-out, pause/resume doesn't desync timing, restart fully resets state.
- [ ] Re-run this checklist after every ticket in Phases 0–3 that touches gameplay logic, since none of it can currently be verified any other way.

#### Acceptance Criteria

- [ ] A written checklist exists covering every core mechanic in the game.
- [ ] The checklist is specific enough that a future you (with no memory of this codebase) could follow it without re-deriving what to test.

#### Notes

This is cheap insurance against regressions given there's no automated
testing yet, and it's genuinely necessary here since several fixes in this
backlog (`BUG-001` through `BUG-004`, `CORE-001`) could not be confirmed by
static inspection alone.

---

### [ ] TEST-002 — Add unit tests for pure-logic functions

**Priority:** P3 — Low
**Difficulty:** 🟠 Hard
**Estimated effort:** 6–10 hours
**Dependencies:** BUG-001 through BUG-004 (test the fixed, correct behavior,
not the current buggy behavior)
**Status:** Not Started

#### Problem

Several core functions are pure logic with no SDL/rendering dependency —
`rotate_clockwise`/`rotate_count_clockwise`, `is_row_full`,
`shift_row_below`, and `check_piece_valid` — and could be tested headlessly,
but nothing currently does so.

#### Current State

No test framework, test files, or test build target exists anywhere in the
repository or `CMakeLists.txt`.

#### Required Work

- [ ] Choose a lightweight approach appropriate for a small hobby C project — either a minimal single-header test framework (e.g. Unity, or a hand-rolled set of `assert()`-based test functions with a small runner `main()`) or a separate CMake test executable target that links only `tetrominos.c`/the relevant board-logic functions (i.e. not the SDL-dependent parts of `main.c`), so tests can run without an SDL3 environment.
- [ ] You will likely need to extract the board-logic functions currently defined directly in `main.c` (`is_row_full`, `shift_row_below`, `check_piece_valid`) into their own translation unit (e.g. `board.c`/ `board.h`) so they can be linked into a test binary independently of `main()` and SDL. This is a small, mechanical refactor, not a redesign.
- [ ] Write tests for: each rotation matrix producing the expected 90° rotation of a known input; `is_row_full` correctly identifying full vs. partially-full rows; `shift_row_below` correctly compacting the board for single and multiple simultaneous full rows; and `check_piece_valid` correctly rejecting out-of-bounds and overlapping placements while accepting valid ones.
- [ ] Wire the test target into `build.sh` or document how to run it separately.

#### Acceptance Criteria

- [ ] A test binary can be built and run independently of the SDL3-based game executable.
- [ ] Rotation, line-full-detection, line-compaction, and collision- validity logic each have passing tests covering both normal and edge cases (e.g. rotating at a board edge, a row with exactly one empty cell, clearing the bottom row vs. clearing multiple non-adjacent rows).

#### Notes

This is the most structurally invasive ticket in the backlog (it requires
extracting logic out of `main.c`), which is why it's scoped as Recommended
rather than Required — the game can absolutely ship a v1.0 without it, but
it will make every future change to this repository safer and faster to
verify. Do it after the Phase 0/1 bug fixes so you're writing tests against
correct behavior instead of encoding the current bugs as "expected."

---

# 🚀 Phase 6 — Release Preparation

### [ ] DOCS-001 — Rewrite README to match the actual project

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 1–2 hours
**Dependencies:** INPUT-002 (final control scheme should be settled first)
**Status:** Not Started

#### Problem

`README.md` describes a different technology stack than what the project
actually uses, documents controls that don't exist, omits controls that do
exist, and links to a screenshot file that isn't in the repository.

#### Current State

- README says: "written in **C++** using the **SDL2 library**." Actual: written in C (`c_std_23` per `CMakeLists.txt`) using SDL3 (`find_package(SDL3 REQUIRED ...)`).
- README's controls table lists Up Arrow (rotate), Down Arrow (soft drop), and Escape (quit) — none of which are bound in the code today. It omits `Ctrl+Z`/`X` (the actual rotation keys) and `Space` (hard drop, the only drop control that currently exists).
- README embeds `![Tetris Gameplay](./src/tetris.png)`, but no `src/tetris.png` (or any `.png`) file exists anywhere in the repository.
- The Requirements section still lists "C++17 or newer" and SDL2 install instructions (`libsdl2-dev`, `pacman -S sdl2`) rather than SDL3.

#### Required Work

- [ ] Correct the language/library description to C23 + SDL3 (and SDL3 install instructions for the platforms already listed: Ubuntu/Debian `libsdl3-dev`-equivalent packages, Arch `sdl3`).
- [ ] Rewrite the controls table to match whatever `INPUT-002` settles on as the final key bindings.
- [ ] Either add a real screenshot at `src/tetris.png` (or wherever makes more sense, e.g. a top-level `docs/` or `screenshots/` folder) or remove the broken image reference until one exists.
- [ ] Review the rest of the README (build instructions, features list) for any other stale claims once the above are fixed, and correct them.

#### Acceptance Criteria

- [ ] The README's described language, library, and version requirements match `CMakeLists.txt` exactly.
- [ ] The README's controls table exactly matches the game's actual key bindings.
- [ ] Every image referenced in the README exists in the repository at the path referenced.

#### Notes

Do this after `INPUT-002` so the controls table only needs to be written
once, against the final key scheme.

---

### [ ] BUILD-002 — Clean up vestigial commented-out CMake blocks

**Priority:** P2 — Medium
**Difficulty:** 🟢 Easy
**Estimated effort:** 30–60 minutes
**Dependencies:** None
**Status:** Not Started

#### Problem

`CMakeLists.txt` contains several large commented-out blocks that don't
appear to apply to this project as it currently exists: a commented-out
ImGui integration (`IMGUI_DIR`, `IMGUI_SOURCES`, an `imgui` library target),
and a commented-out asset-installation setup (`install(DIRECTORY ...)`, a
desktop-entry/icon install block) referencing an `assets/` directory that
does not exist anywhere in this repository. There's also an active
`LX_ASSET_DIR` compile definition and an explanatory comment about an
"AssetManager" that searches multiple runtime locations for assets — but no
`AssetManager` code exists anywhere in `src/`.

#### Current State

These blocks appear to have been copied in from a different project (the
`LX_`-prefixed naming and "AssetManager" concept suggest they originate
from unrelated tooling) rather than written for this Tetris project
specifically, and none of them are currently exercised by anything in
`src/`.

#### Required Work

- [ ] Decide, for each vestigial block, whether it's (a) genuinely planned for this project soon (e.g. if `UI-001`'s font-loading work will actually use an `assets/` directory and the `LX_ASSET_DIR` define), in which case keep it and write a real comment saying so and finish wiring it up, or (b) not applicable here, in which case remove it.
- [ ] If `LX_ASSET_DIR` ends up genuinely useful for `UI-001` (locating a font file at runtime), keep it, but update its explanatory comment so it accurately describes this project rather than referencing an AssetManager class that doesn't exist in this codebase.
- [ ] Remove the commented-out ImGui block entirely unless there's a concrete near-term plan to add ImGui to this project (nothing in this backlog currently calls for it).

#### Acceptance Criteria

- [ ] `CMakeLists.txt` contains no large commented-out blocks that don't correspond to something either already implemented or concretely planned in this backlog.
- [ ] Any comments that remain accurately describe this project's own code, not a different project's architecture.

#### Notes

This is purely a maintainability/clarity cleanup — none of these blocks
currently affect the build output either way since they're inert
(commented out) or unused (`LX_ASSET_DIR` with no consumer yet).

---

### [ ] BUILD-003 — Verify a clean build from scratch before tagging v1.0

**Priority:** P1 — High
**Difficulty:** 🟢 Easy
**Estimated effort:** 30–60 minutes
**Dependencies:** All Phase 0–3 tickets (this should be the last thing done
before release)
**Status:** Not Started

#### Problem

There is no confirmed record of a fully clean build (from a fresh clone,
with no prior `build/` directory or cached CMake state) as part of this
analysis — the existing `build/debug/` directory in the repository was
generated by a previous, different snapshot of the source (its
`.ninja_log` references a `/home/awais/DEV/Tetris` path from an earlier
session), and a fresh build was not attempted here since no SDL3
installation was available in this environment.

#### Current State

An existing `build/debug/tetris` binary and object files are present in the
uploaded project, but they predate the current source state in ways that
can't be fully verified from static inspection alone (e.g. it's unclear
whether they were built from a `main.c` matching what's in `src/` today
versus an intermediate version).

#### Required Work

- [ ] Run `./build.sh clean` followed by `./build.sh debug` (and separately `./build.sh release`) from a completely fresh state and confirm both complete with zero errors.
- [ ] Confirm the build produces no new warnings beyond what's expected given the project's `-Wall -Wextra -Wpedantic -Wshadow` flags (ideally zero warnings by v1.0).
- [ ] Run `./build.sh run` and confirm the game launches and is playable end-to-end (start → play → game over → restart, once those features exist) with no crashes, paying particular attention to the Debug build's AddressSanitizer/UndefinedBehaviorSanitizer output, since those are enabled in `CMakeLists.txt`'s Debug configuration and would catch memory issues that static review can't.

#### Acceptance Criteria

- [ ] A completely fresh clone builds successfully in both Debug and Release configurations with `./build.sh`.
- [ ] The Debug build's ASan/UBSan instrumentation reports no errors during a full playthrough (start, movement, rotation, line clears, game over, restart).
- [ ] The build produces no compiler warnings.

#### Notes

This should be the final gate before declaring v1.0 done — everything else
in this backlog should be verified through this checklist at least once
before release.

---

## 🌌 Post-Version 1.0 Backlog

These are reasonable, interesting extensions to consider once v1.0 is
genuinely done and stable. None of them should be started before the
Required section of this backlog is complete.

- **Wall kicks / SRS-style rotation.** The current rotation simply rejects a rotation if the naively-rotated position collides, with no attempt to "kick" the piece into a nearby valid position (as most modern Tetris implementations do near walls and the stack). Worth revisiting once basic rotation (`BUG-001`) is solid and players have a chance to notice it feels restrictive.
- **Sound effects** (`AUDIO`). Line clear, piece lock, rotation, and game-over sounds. No audio library is currently linked in `CMakeLists.txt` (SDL3 has its own audio subsystem, or `SDL3_mixer` could be added), so this also involves a new build dependency.
- **Settings/options menu.** Key rebinding, volume (once audio exists), maybe a toggle for the ghost piece.
- **Replay system.** Recording and replaying input sequences — a substantial feature that would benefit from the game's core logic being more decoupled from rendering/input first (see `TEST-002`'s note about extracting board logic).
- **Online leaderboards / multiplayer.** Out of scope for the project's current architecture (no networking code or dependencies exist at all today); would be a significant scope and architecture expansion.
- **Custom themes / skins.** Alternate color palettes or block skins, built on top of whatever `Piece_Color`-style system exists after `BUG-002` is fixed.
- **AI opponent / bot mode.** Not a natural fit for single-board Tetris without a versus/multiplayer mode to pair it with; would follow multiplayer support, not precede it.
- **Advanced particle effects for line clears.** Purely cosmetic polish on top of an already-working line-clear system.
