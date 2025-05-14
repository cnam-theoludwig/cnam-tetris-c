#include "./tetris_struct_test.h"

void tetris_struct_test() {
  tetris_init_test();
  tetris_get_level_test();
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

void tetris_get_level_test() {
  struct Tetris* tetris = tetris_init();
  assert(tetris_get_level(tetris) == 0);

  tetris->destroyed_lines_count = 15;
  assert(tetris_get_level(tetris) == 1);

  tetris->destroyed_lines_count = 112;
  assert(tetris_get_level(tetris) == 11);

  tetris->destroyed_lines_count = 150;
  assert(tetris_get_level(tetris) == 15);

  tetris_free(tetris);
  printf("tetris_get_level_test\n");
}
