#include "piece_queue.h"
#include "SDL3/SDL.h"
#include "stdio.h"

void init_piece_queue(Piece_Queue *q) { q->size = 0; }

bool is_empty(Piece_Queue *q) { return (q->size == 0); }
bool is_full(Piece_Queue *q) { return q->size == MAX_PREVIEW_SIZE; }

void enqueue(Piece_Queue *q, int type) {
  if (is_full(q)) {
    SDL_Log("Piece_Queue is Full");
    return;
  }
  q->items[q->size] = make_piece(type);
  q->size++;
}
void dequeue(Piece_Queue *q) {
  if (is_empty(q)) {
    printf("Queue is empty\n");
    return;
  }
  for (int i = 0; i < q->size - 1; i++) {
    q->items[i] = q->items[i + 1];
  }
  q->size--;
}
Piece peek(Piece_Queue *q) {
  if (is_empty(q)) {
    printf("Queue is empty\n");
    return (Piece){0}; // return some default value or handle
                       // error differently
  }
  return q->items[0];
}
