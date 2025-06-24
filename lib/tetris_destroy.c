#include "tetris_destroy.h"

void tetris_destroy_single_line(struct Tetris* tetris, size_t row) {
  for (size_t r = row; r > 0; --r) {
    for (size_t c = 0; c < GRID_WIDTH; ++c) {
      byte_t above = tetris->grid[r-1][c]->type;
      if (above == TETROMINO_GARBAGE) {
        tetris->grid[r][c]->type = TETROMINO_EMPTY;
        tetris->grid[r][c]->occurence = 0;
      } else {
        tetris->grid[r][c]->type = above;
        tetris->grid[r][c]->occurence = tetris->grid[r-1][c]->occurence;
      }
    }
  }
  // première ligne vide
  for (size_t c = 0; c < GRID_WIDTH; ++c) {
    tetris->grid[0][c]->type = TETROMINO_EMPTY;
    tetris->grid[0][c]->occurence = 0;
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
      ++count;
      tetris_destroy_single_line(tetris, row);
      tetris->destroyed_lines_count++;
      --row;
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
