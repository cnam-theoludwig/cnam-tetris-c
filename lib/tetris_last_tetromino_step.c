#include "./tetris_last_tetromino_step.h"

bool tetris_last_tetromino_step_down(struct Tetris* tetris) {
  bool can_move = true;

  for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
    for (int column = GRID_WIDTH - 1; column >= 0; column--) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (row + 1 >= GRID_HEIGHT ||
            (tetris->grid[row + 1][column]->type != TETROMINO_EMPTY &&
             tetris->grid[row + 1][column]->occurence != tetris->last_occurence)) {
          can_move = false;
          break;
        }
      }
    }
    if (!can_move) {
      break;
    }
  }

  if (!can_move) {
    return false;
  }

  for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
    for (int column = GRID_WIDTH - 1; column >= 0; column--) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        tetris->grid[row + 1][column]->type = tetris->grid[row][column]->type;
        tetris->grid[row + 1][column]->occurence = tetris->grid[row][column]->occurence;

        tetris->grid[row][column]->type = TETROMINO_EMPTY;
        tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  tetris->last_pivot_y += 1;
  return true;
}

void tetris_last_tetromino_step_left(struct Tetris* tetris) {
  bool can_move = true;

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (column == 0 || (tetris->grid[row][column - 1]->type != TETROMINO_EMPTY && tetris->grid[row][column - 1]->occurence != tetris->last_occurence)) {
          can_move = false;
          break;
        }
      }
    }
    if (!can_move) {
      break;
    }
  }

  if (!can_move) {
    return;
  }

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        tetris->grid[row][column - 1]->type = tetris->grid[row][column]->type;
        tetris->grid[row][column - 1]->occurence = tetris->grid[row][column]->occurence;

        tetris->grid[row][column]->type = TETROMINO_EMPTY;
        tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  tetris->last_pivot_x -= 1;
}

void tetris_last_tetromino_step_right(struct Tetris* tetris) {
  bool can_move = true;

  for (int row = 0; row < GRID_HEIGHT; row++) {
    for (int column = GRID_WIDTH - 1; column >= 0; column--) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        if (column + 1 >= GRID_WIDTH || (tetris->grid[row][column + 1]->type != TETROMINO_EMPTY && tetris->grid[row][column + 1]->occurence != tetris->last_occurence)) {
          can_move = false;
          break;
        }
      }
    }
    if (!can_move) {
      break;
    }
  }

  if (!can_move) {
    return;
  }

  for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
    for (int column = GRID_WIDTH - 1; column >= 0; column--) {
      if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
        tetris->grid[row][column + 1]->type = tetris->grid[row][column]->type;
        tetris->grid[row][column + 1]->occurence = tetris->grid[row][column]->occurence;

        tetris->grid[row][column]->type = TETROMINO_EMPTY;
        tetris->grid[row][column]->occurence = 0;
      }
    }
  }

  tetris->last_pivot_x += 1;
}

void tetris_last_tetromino_step_rotate_right(struct Tetris* tetris) {
  if (tetris->last_type == TETROMINO_SQUARE) {
    return;
  }

  size_t blocks[4][2];
  size_t rotated[4][2];
  size_t count = 0;

  for (size_t y = 0; y < GRID_HEIGHT; y++) {
    for (size_t x = 0; x < GRID_WIDTH; x++) {
      if (tetris->grid[y][x]->occurence == tetris->last_occurence) {
        blocks[count][0] = x;
        blocks[count][1] = y;
        count++;
        if (count == 4) {
          break;
        }
      }
    }
    if (count == 4) {
      break;
    }
  }

  if (count != 4) {
    return;
  }

  size_t cx = tetris->last_pivot_x;
  size_t cy = tetris->last_pivot_y;

  for (size_t i = 0; i < 4; i++) {
    size_t dx = blocks[i][0] - cx;
    size_t dy = blocks[i][1] - cy;
    rotated[i][0] = cx + dy;
    rotated[i][1] = cy - dx;
  }

  for (size_t i = 0; i < 4; i++) {
    size_t x = rotated[i][0];
    size_t y = rotated[i][1];

    if (x >= GRID_WIDTH || y >= GRID_HEIGHT) {
      return;
    }

    if (tetris->grid[y][x]->type != TETROMINO_EMPTY && tetris->grid[y][x]->occurence != tetris->last_occurence) {
      return;
    }
  }

  for (size_t i = 0; i < 4; i++) {
    size_t x = blocks[i][0];
    size_t y = blocks[i][1];
    tetris->grid[y][x]->type = TETROMINO_EMPTY;
    tetris->grid[y][x]->occurence = 0;
  }

  for (size_t i = 0; i < 4; i++) {
    size_t x = rotated[i][0];
    size_t y = rotated[i][1];
    tetris->grid[y][x]->type = tetris->last_type;
    tetris->grid[y][x]->occurence = tetris->last_occurence;
  }
}

void tetris_last_tetromino_step_rotate_left(struct Tetris* tetris) {
  tetris_last_tetromino_step_rotate_right(tetris);
  tetris_last_tetromino_step_rotate_right(tetris);
  tetris_last_tetromino_step_rotate_right(tetris);
}
