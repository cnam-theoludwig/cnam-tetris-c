#include "./tetris_struct_test.h"

void tetris_struct_test() {
  tetris_init_test();
}

void tetris_init_test() {
  struct Tetris* tetris = tetris_init();
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      assert(tetris->grid[row][column]->type == TETROMINO_EMPTY);
      assert(tetris->grid[row][column]->occurence == 0);
    }
  }

  tetris_free(tetris);
  printf("tetris_init_test\n");
}
