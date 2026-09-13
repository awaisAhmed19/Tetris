#pragma once
#include "tetrominos.h"

#define MAX_PREVIEW_SIZE 3
typedef struct {
  Piece items[3];
  i16 size;
} Piece_Queue;

extern void init_piece_queue(Piece_Queue *q);
extern bool is_empty(Piece_Queue *q);
extern bool is_full(Piece_Queue *q);
extern void enqueue(Piece_Queue *q, int type);
extern void dequeue(Piece_Queue *q);
extern Piece peek(Piece_Queue *q);
