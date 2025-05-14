#include "./tetris_destroy_test.h"

void tetris_destroy_test() {
  struct Tetris* tetris = tetris_init();

  for (size_t index_column = 0; index_column < GRID_WIDTH - 2; index_column += 1) {
    tetris->grid[GRID_HEIGHT - 1][index_column]->type = TETROMINO_SQUARE;
    tetris->grid[GRID_HEIGHT - 1][index_column]->occurence = 1;
    tetris->last_occurence += 1;

    tetris->grid[GRID_HEIGHT - 2][index_column]->type = TETROMINO_SQUARE;
    tetris->grid[GRID_HEIGHT - 2][index_column]->occurence = 1;
    tetris->last_occurence += 1;
  }

  assert(tetris->score == 0);

  tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);

  assert(tetris_destroy_line(tetris) == 0);
  assert(tetris->score == 0);

  while (tetris_last_tetromino_step_down(tetris)) {
  }

  assert(tetris_destroy_line(tetris) == 2);
  assert(tetris->score == 100);

  tetris_free(tetris);
  printf("tetris_destroy_test\n");
}
