#include "tetris_1v1.h"

size_t tetris_1v1_handle_lines_and_attack(struct Tetris* self, struct Tetris* opponent) {
  size_t garbage = tetris_destroy_line(self);
  if (garbage > 0) {
    tetris_1v1_receive_garbage(opponent, garbage);
  }
  return garbage;
}

void tetris_1v1_receive_garbage(struct Tetris* tetris, size_t lines) {
  for (size_t line = 0; line < lines; ++line) {
    for (size_t row = 0; row < GRID_HEIGHT - 1; ++row) {
      for (size_t column = 0; column < GRID_WIDTH; ++column) {
        tetris->grid[row][column]->type = tetris->grid[row + 1][column]->type;
        tetris->grid[row][column]->occurence = tetris->grid[row + 1][column]->occurence;
      }
    }
    size_t last = GRID_HEIGHT - 1;
    for (size_t column = 0; column < GRID_WIDTH; ++column) {
      tetris->grid[last][column]->type = TETROMINO_GARBAGE;
      tetris->grid[last][column]->occurence = 0;
    }
  }
}
