#include "./tetris_destroy.h"

void tetris_destroy_single_line(struct Tetris* tetris, size_t row) {
  for (size_t r = row; r > 0; r--) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      tetris->grid[r][column]->type = tetris->grid[r - 1][column]->type;
      tetris->grid[r][column]->occurence = tetris->grid[r - 1][column]->occurence;
    }
  }

  for (size_t column = 0; column < GRID_WIDTH; column++) {
    tetris->grid[0][column]->type = TETROMINO_EMPTY;
    tetris->grid[0][column]->occurence = 0;
  }
}

size_t tetris_destroy_line(struct Tetris* tetris) {
  size_t count = 0;

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    bool is_complete = true;

    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->type == TETROMINO_EMPTY) {
        is_complete = false;
        break;
      }
    }
    if (is_complete) {
      count += 1;
      tetris_destroy_single_line(tetris, row);
      tetris->destroyed_lines_count++;
      row--;
    }
  }
  switch (count) {
    case 0:
      break;
    case 1:
      tetris->score += (tetris_get_level(tetris) + 1) * SCORE_SINGLE;
      break;
    case 2:
      tetris->score += (tetris_get_level(tetris) + 1) * SCORE_DOUBLE;
      break;
    case 3:
      tetris->score += (tetris_get_level(tetris) + 1) * SCORE_TRIPLE;
      break;
    default:
      tetris->score += (tetris_get_level(tetris) + 1) * SCORE_TETRIS;
      break;
  }

  return count;
}
