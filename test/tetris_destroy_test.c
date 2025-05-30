#include "./tetris_destroy_test.h"

void fill_row(struct Tetris* tetris, size_t row, byte_t type) {
  for (size_t col = 0; col < GRID_WIDTH; ++col) {
    tetris->grid[row][col]->type = type;
    tetris->grid[row][col]->occurence = 1;
  }
}

bool is_row_empty(struct Tetris* tetris, size_t row) {
  for (size_t col = 0; col < GRID_WIDTH; ++col) {
    if (tetris->grid[row][col]->type != TETROMINO_EMPTY) {
      return false;
    }
  }
  return true;
}

void tetris_destroy_test() {
  printf("tetris_destroy_line_empty_grid_test\n");
  struct Tetris* tetris = tetris_init();
  assert(tetris != NULL);
  assert(tetris->score == 0);
  assert(tetris->destroyed_lines_count == 0);

  size_t lines_destroyed = tetris_destroy_line(tetris);
  assert(lines_destroyed == 0);
  assert(tetris->score == 0);
  assert(tetris->destroyed_lines_count == 0);
  tetris_free(tetris);

  printf("tetris_destroy_line_partial_line_test\n");
  tetris = tetris_init();

  tetris->grid[GRID_HEIGHT - 1][0]->type = TETROMINO_LINE;
  tetris->grid[GRID_HEIGHT - 1][1]->type = TETROMINO_LINE;
  lines_destroyed = tetris_destroy_line(tetris);
  assert(lines_destroyed == 0);
  assert(tetris->score == 0);
  assert(tetris->destroyed_lines_count == 0);
  tetris_free(tetris);

  printf("tetris_destroy_line_single_complete_line_test\n");
  tetris = tetris_init();

  fill_row(tetris, GRID_HEIGHT - 1, TETROMINO_SQUARE);
  tetris->grid[GRID_HEIGHT - 2][0]->type = TETROMINO_L;
  tetris->grid[GRID_HEIGHT - 2][1]->type = TETROMINO_L;

  lines_destroyed = tetris_destroy_line(tetris);
  assert(lines_destroyed == 1);
  assert(tetris->score == (tetris_get_level(tetris) + 1) * SCORE_SINGLE);
  assert(tetris->destroyed_lines_count == 1);
  assert(is_row_empty(tetris, 0));
  assert(tetris->grid[GRID_HEIGHT - 1][0]->type == TETROMINO_L);
  assert(tetris->grid[GRID_HEIGHT - 1][1]->type == TETROMINO_L);
  for (size_t col = 2; col < GRID_WIDTH; ++col) {
    assert(tetris->grid[GRID_HEIGHT - 1][col]->type == TETROMINO_EMPTY);
  }
  tetris_free(tetris);

  printf("tetris_destroy_line_two_complete_lines_test\n");
  tetris = tetris_init();
  fill_row(tetris, GRID_HEIGHT - 1, TETROMINO_T);
  fill_row(tetris, GRID_HEIGHT - 2, TETROMINO_J);

  tetris->grid[GRID_HEIGHT - 3][0]->type = TETROMINO_Z;
  tetris->grid[GRID_HEIGHT - 3][1]->type = TETROMINO_Z;

  lines_destroyed = tetris_destroy_line(tetris);
  assert(lines_destroyed == 2);
  assert(tetris->score == (tetris_get_level(tetris) + 1) * SCORE_DOUBLE);
  assert(tetris->destroyed_lines_count == 2);
  assert(is_row_empty(tetris, 0));
  assert(is_row_empty(tetris, 1));

  assert(tetris->grid[GRID_HEIGHT - 1][0]->type == TETROMINO_Z);
  assert(tetris->grid[GRID_HEIGHT - 1][1]->type == TETROMINO_Z);
  for (size_t col = 2; col < GRID_WIDTH; ++col) {
    assert(tetris->grid[GRID_HEIGHT - 1][col]->type == TETROMINO_EMPTY);
  }
  tetris_free(tetris);

  printf("tetris_free_basic_test\n");
  tetris = tetris_init();
  tetris_free(tetris);

  printf("tetris_destroy_line_original_scenario_simplified_test\n");
  tetris = tetris_init();

  for (size_t c = 3; c <= 6; ++c) {
    tetris->grid[0][c]->type = TETROMINO_LINE;
    tetris->grid[0][c]->occurence = 1;
  }

  for (size_t c = 0; c < 3; ++c) {
    tetris->grid[0][c]->type = TETROMINO_EMPTY;
    tetris->grid[0][c]->occurence = 0;
  }
  for (size_t c = 7; c < GRID_WIDTH; ++c) {
    tetris->grid[0][c]->type = TETROMINO_EMPTY;
    tetris->grid[0][c]->occurence = 0;
  }

  lines_destroyed = tetris_destroy_line(tetris);
  assert(lines_destroyed == 0);
  assert(tetris->score == 0);
  tetris_free(tetris);

  printf("tetris_destroy_test passed (all scenarios)\n");
}
