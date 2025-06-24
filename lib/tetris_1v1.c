// tetris_1v1.c
#include "tetris_1v1.h"
#include "tetris_destroy.h"
#include <stdlib.h>
#include <stdio.h>

size_t tetris_1v1_handle_lines_and_attack(struct Tetris* self, struct Tetris* opponent) {
    size_t cleared = tetris_destroy_line(self);
    size_t garbage = 0;
    switch (cleared) {
        case 1: garbage = 1; break;
        case 2: garbage = 2; break;
        case 3: garbage = 3; break;
        case 4: garbage = 4; break;
    }
    if (garbage > 0) {
      tetris_1v1_receive_garbage(opponent,garbage);
        printf("[1v1] %zu lignes de garbage en attente pour l'adversaire\n", garbage);
    }
    return garbage;
}

void tetris_1v1_receive_garbage(struct Tetris* tetris, size_t lines) {
  for (size_t i = 0; i < lines; ++i) {
    for (size_t r = 0; r < GRID_HEIGHT-1; ++r) {
      for (size_t c = 0; c < GRID_WIDTH; ++c) {
        tetris->grid[r][c]->type = tetris->grid[r+1][c]->type;
        tetris->grid[r][c]->occurence = tetris->grid[r+1][c]->occurence;
      }
    }
    size_t last = GRID_HEIGHT-1;
    for (size_t c = 0; c < GRID_WIDTH; ++c) {
      tetris->grid[last][c]->type = TETROMINO_GARBAGE;
      tetris->grid[last][c]->occurence = 0;
    }
  }
}
