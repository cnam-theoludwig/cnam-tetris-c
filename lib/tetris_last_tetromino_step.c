#include "./tetris_last_tetromino_step.h"

bool tetris_last_tetromino_step_down(struct Tetris* tetris) {
  bool can_move = true;

  for (size_t row = GRID_HEIGHT - 1; row != SIZE_MAX; row--) {
    for (size_t column = GRID_WIDTH - 1; column != SIZE_MAX; column--) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (row + 1 >= GRID_HEIGHT || (tetris->grid[row + 1][column]->type != TETROMINO_EMPTY && tetris->grid[row + 1][column]->occurence != tetris->last_occurence)) {
          can_move = false;
          break;
        }
      }
    }
  }

  if (!can_move) {
    return false;
  }

  for (size_t row = GRID_HEIGHT - 1; row != SIZE_MAX; row--) {
    for (size_t column = GRID_WIDTH - 1; column != SIZE_MAX; column--) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        tetris->grid[row + 1][column]->type = tetris->grid[row][column]->type;
        tetris->grid[row + 1][column]->occurence = tetris->grid[row][column]->occurence;

        tetris->grid[row][column]->type = TETROMINO_EMPTY;
        tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  return true;
}

void tetris_last_tetromino_step_left(struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (column == 0 || (tetris->grid[row][column - 1]->type != TETROMINO_EMPTY && tetris->grid[row][column - 1]->occurence != tetris->last_occurence)) {
          return;
        }
      }
    }
  }

  struct Tetris* copy_tetris = tetris_copy(tetris);

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (copy_tetris->grid[row][column]->occurence == copy_tetris->last_occurence) {
        copy_tetris->grid[row][column - 1]->type = copy_tetris->grid[row][column]->type;
        copy_tetris->grid[row][column - 1]->occurence = copy_tetris->grid[row][column]->occurence;

        copy_tetris->grid[row][column]->type = TETROMINO_EMPTY;
        copy_tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      tetris->grid[row][column]->type = copy_tetris->grid[row][column]->type;
      tetris->grid[row][column]->occurence = copy_tetris->grid[row][column]->occurence;
    }
  }
  tetris_free(copy_tetris);
}

void tetris_last_tetromino_step_right(struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (column == GRID_WIDTH - 1 || (tetris->grid[row][column + 1]->type != TETROMINO_EMPTY && tetris->grid[row][column + 1]->occurence != tetris->last_occurence)) {
          return;
        }
      }
    }
  }

  struct Tetris* copy_tetris = tetris_copy(tetris);

  for (size_t row = GRID_HEIGHT - 1; row != SIZE_MAX; row--) {
    for (size_t column = GRID_WIDTH - 1; column != SIZE_MAX; column--) {
      if (copy_tetris->grid[row][column]->occurence == copy_tetris->last_occurence) {
        copy_tetris->grid[row][column + 1]->type = copy_tetris->grid[row][column]->type;
        copy_tetris->grid[row][column + 1]->occurence = copy_tetris->grid[row][column]->occurence;

        copy_tetris->grid[row][column]->type = TETROMINO_EMPTY;
        copy_tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      tetris->grid[row][column]->type = copy_tetris->grid[row][column]->type;
      tetris->grid[row][column]->occurence = copy_tetris->grid[row][column]->occurence;
    }
  }
  tetris_free(copy_tetris);
}
