#include "tetris_add_tetromino.h"

static byte_t last_tetromino = 0;

bool tetris_add_tetromino(struct Tetris* tetris) {
  byte_t type = tetris->next_tetromino_type;
  tetris->next_tetromino_type = tetris_get_tetromino_random();

  size_t row = 0;
  size_t column = GRID_WIDTH / 2;
  tetris->last_occurence += 1;
  tetris->last_type = type;

  bool has_space = true;

  switch (type) {
    case TETROMINO_LINE:
      has_space = tetris->grid[row][column - 2]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column + 1]->type == TETROMINO_EMPTY;

      tetris->grid[row][column - 2]->type = type;
      tetris->grid[row][column - 2]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;

      tetris->last_pivot_x = column;
      tetris->last_pivot_y = row;
      break;

    case TETROMINO_SQUARE:
      has_space = tetris->grid[row][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column]->type == TETROMINO_EMPTY;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column - 1]->type = type;
      tetris->grid[row + 1][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;

      tetris->last_pivot_x = column;
      tetris->last_pivot_y = row;
      break;

    case TETROMINO_T:
      has_space = tetris->grid[row][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column + 1]->type == TETROMINO_EMPTY;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;

      tetris->last_pivot_x = column;
      tetris->last_pivot_y = row;
      break;

    case TETROMINO_L:
      has_space = tetris->grid[row + 1][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column]->type == TETROMINO_EMPTY;

      tetris->grid[row + 1][column - 1]->type = type;
      tetris->grid[row + 1][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;

      tetris->last_pivot_x = column;
      tetris->last_pivot_y = row;
      break;

    case TETROMINO_J:
      has_space = tetris->grid[row + 1][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column + 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column]->type == TETROMINO_EMPTY;

      tetris->grid[row + 1][column + 1]->type = type;
      tetris->grid[row + 1][column + 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;

      tetris->last_pivot_x = column;
      tetris->last_pivot_y = row;
      break;

    case TETROMINO_Z:
      has_space = tetris->grid[row][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column + 1]->type == TETROMINO_EMPTY;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column + 1]->type = type;
      tetris->grid[row + 1][column + 1]->occurence = tetris->last_occurence;

      tetris->last_pivot_x = column;
      tetris->last_pivot_y = row;
      break;

    case TETROMINO_S:
      has_space = tetris->grid[row][column]->type == TETROMINO_EMPTY &&
                  tetris->grid[row][column + 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column - 1]->type == TETROMINO_EMPTY &&
                  tetris->grid[row + 1][column]->type == TETROMINO_EMPTY;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column - 1]->type = type;
      tetris->grid[row + 1][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;

      tetris->last_pivot_x = column;
      tetris->last_pivot_y = row;
      break;
  }

  return has_space;
}

byte_t tetris_get_tetromino_random() {
  byte_t tetrominos[] = {TETROMINO_LINE, TETROMINO_SQUARE, TETROMINO_T, TETROMINO_L, TETROMINO_Z, TETROMINO_J, TETROMINO_S};
  size_t tetrominos_size = sizeof(tetrominos) / sizeof(tetrominos[0]);

  byte_t available_tetrominos[7];
  size_t available_count = 0;

  for (size_t i = 0; i < tetrominos_size; i++) {
    if (tetrominos[i] != last_tetromino) {
      available_tetrominos[available_count] = tetrominos[i];
      available_count++;
    }
  }

  byte_t tetromino = available_tetrominos[random_size_t(0, available_count - 1)];
  last_tetromino = tetromino;
  return tetromino;
}
