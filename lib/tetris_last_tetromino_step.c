#include "./tetris_last_tetromino_step.h"

bool tetris_last_tetromino_step_down(struct Tetris* tetris) {
  bool can_move = true;

  for (size_t row = GRID_HEIGHT - 1; row != SIZE_MAX; row--) {
    for (size_t column = GRID_WIDTH - 1; column != SIZE_MAX; column--) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (row + 1 >= GRID_HEIGHT ||
            (tetris->grid[row + 1][column]->type != TETROMINO_EMPTY && tetris->grid[row + 1][column]->occurence != tetris->last_occurence)) {
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
        tetris->grid[row + 1][column]->occurence =
            tetris->grid[row][column]->occurence;

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
        if (column == 0 ||
            (tetris->grid[row][column - 1]->type != TETROMINO_EMPTY && tetris->grid[row][column - 1]->occurence != tetris->last_occurence)) {
          return;
        }
      }
    }
  }

  struct Tetris* copy_tetris = tetris_copy(tetris);

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (copy_tetris->grid[row][column]->occurence ==
          copy_tetris->last_occurence) {
        copy_tetris->grid[row][column - 1]->type =
            copy_tetris->grid[row][column]->type;
        copy_tetris->grid[row][column - 1]->occurence =
            copy_tetris->grid[row][column]->occurence;

        copy_tetris->grid[row][column]->type = TETROMINO_EMPTY;
        copy_tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      tetris->grid[row][column]->type = copy_tetris->grid[row][column]->type;
      tetris->grid[row][column]->occurence =
          copy_tetris->grid[row][column]->occurence;
    }
  }
  tetris_free(copy_tetris);
}

void tetris_last_tetromino_step_right(struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (column == GRID_WIDTH - 1 ||
            (tetris->grid[row][column + 1]->type != TETROMINO_EMPTY && tetris->grid[row][column + 1]->occurence != tetris->last_occurence)) {
          return;
        }
      }
    }
  }

  struct Tetris* copy_tetris = tetris_copy(tetris);

  for (size_t row = GRID_HEIGHT - 1; row != SIZE_MAX; row--) {
    for (size_t column = GRID_WIDTH - 1; column != SIZE_MAX; column--) {
      if (copy_tetris->grid[row][column]->occurence ==
          copy_tetris->last_occurence) {
        copy_tetris->grid[row][column + 1]->type =
            copy_tetris->grid[row][column]->type;
        copy_tetris->grid[row][column + 1]->occurence =
            copy_tetris->grid[row][column]->occurence;

        copy_tetris->grid[row][column]->type = TETROMINO_EMPTY;
        copy_tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      tetris->grid[row][column]->type = copy_tetris->grid[row][column]->type;
      tetris->grid[row][column]->occurence =
          copy_tetris->grid[row][column]->occurence;
    }
  }
  tetris_free(copy_tetris);
}

void tetris_last_tetromino_step_rotate_right(struct Tetris* tetris) {
  struct Tetris* copy_tetris = tetris_copy(tetris);

  size_t min_row = GRID_HEIGHT;
  size_t min_column = GRID_WIDTH;
  size_t max_row = 0;
  size_t max_column = 0;

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (copy_tetris->grid[row][column]->occurence ==
          copy_tetris->last_occurence) {
        if (row < min_row) {
          min_row = row;
        }
        if (row > max_row) {
          max_row = row;
        }
        if (column < min_column) {
          min_column = column;
        }
        if (column > max_column) {
          max_column = column;
        }
      }
    }
  }

  size_t center_row = (min_row + max_row) / 2;
  size_t center_column = (min_column + max_column) / 2;

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (copy_tetris->grid[row][column]->occurence ==
          copy_tetris->last_occurence) {
        copy_tetris->grid[row][column]->type = TETROMINO_EMPTY;
        copy_tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  for (size_t row = min_row; row <= max_row; row++) {
    for (size_t column = min_column; column <= max_column; column++) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        int new_row = center_row - (column - center_column);
        int new_column = center_column + (row - center_row);

        if (new_row >= 0 && new_row < GRID_HEIGHT && new_column >= 0 &&
            new_column < GRID_WIDTH) {
          if (tetris->grid[new_row][new_column]->type != TETROMINO_EMPTY &&
              tetris->grid[new_row][new_column]->occurence !=
                  tetris->last_occurence) {
            tetris_free(copy_tetris);
            return;
          }

          copy_tetris->grid[new_row][new_column]->type =
              tetris->grid[row][column]->type;
          copy_tetris->grid[new_row][new_column]->occurence =
              tetris->grid[row][column]->occurence;
        } else {
          tetris_free(copy_tetris);
          return;
        }
      }
    }
  }

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        tetris->grid[row][column]->type = TETROMINO_EMPTY;
        tetris->grid[row][column]->occurence = 0;
      }
    }
  }
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (copy_tetris->grid[row][column]->occurence ==
          copy_tetris->last_occurence) {
        tetris->grid[row][column]->type = copy_tetris->grid[row][column]->type;
        tetris->grid[row][column]->occurence =
            copy_tetris->grid[row][column]->occurence;
      }
    }
  }

  tetris_free(copy_tetris);
}

void tetris_last_tetromino_step_rotate_left(struct Tetris* tetris) {
  tetris_last_tetromino_step_rotate_right(tetris);
  tetris_last_tetromino_step_rotate_right(tetris);
  tetris_last_tetromino_step_rotate_right(tetris);
}
