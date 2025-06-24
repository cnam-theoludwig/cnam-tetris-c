#include "tetris_destroy.h"

void tetris_destroy_single_line(struct Tetris* tetris, size_t row_size) {
  for (size_t row = row_size; row > 0; --row) {
    for (size_t column = 0; column < GRID_WIDTH; ++column) {
      byte_t above = tetris->grid[row - 1][column]->type;
      if (above == TETROMINO_GARBAGE) {
        tetris->grid[row][column]->type = TETROMINO_EMPTY;
        tetris->grid[row][column]->occurence = 0;
      } else {
        tetris->grid[row][column]->type = above;
        tetris->grid[row][column]->occurence = tetris->grid[row - 1][column]->occurence;
      }
    }
  }
  for (size_t column = 0; column < GRID_WIDTH; ++column) {
    tetris->grid[0][column]->type = TETROMINO_EMPTY;
    tetris->grid[0][column]->occurence = 0;
  }
}

size_t tetris_destroy_line(struct Tetris* tetris) {
  size_t count = 0;
  for (size_t row = 0; row < GRID_HEIGHT; ++row) {
    bool is_complete = true;
    for (size_t col = 0; col < GRID_WIDTH; ++col) {
      byte_t t = tetris->grid[row][col]->type;
      if (t == TETROMINO_EMPTY || t == TETROMINO_GARBAGE) {
        is_complete = false;
        break;
      }
    }
    if (is_complete) {
      count += 1;
      tetris_destroy_single_line(tetris, row);
      tetris->destroyed_lines_count++;
      row -= 1;
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
