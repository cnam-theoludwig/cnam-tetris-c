#include "./tetris_game.h"

int tetris_game() {
  srand(time(NULL));
  printf("Tetris game\n");
  struct Tetris* tetris = tetris_init();

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  // while (tetris_last_tetromino_step_down(tetris)) {

  tetris_add_tetromino_random(tetris);
  tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  // tetris_last_tetromino_step_left(tetris);
  // tetris_last_tetromino_step_left(tetris);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  // tetris_last_tetromino_step_left(tetris);
  // tetris_last_tetromino_step_left(tetris);
  // tetris_last_tetromino_step_left(tetris);
  // tetris_last_tetromino_step_left(tetris);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  // tetris_last_tetromino_step_right(tetris);
  // tetris_last_tetromino_step_right(tetris);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  // tetris_last_tetromino_step_right(tetris);
  // tetris_last_tetromino_step_right(tetris);
  // tetris_last_tetromino_step_right(tetris);
  // tetris_last_tetromino_step_right(tetris);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_T);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_L);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_Z);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_J);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_add_tetromino(tetris, TETROMINO_S);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  // }

  // tetris_destroy_line(tetris);
  // tetris_print(tetris);

  // tetris_add_tetromino(tetris, TETROMINO_LINE);
  // while (tetris_last_tetromino_step_down(tetris)) {
  //   tetris_print(tetris);
  //   sleep(1);
  // }

  tetris_free(tetris);
  return EXIT_SUCCESS;
}

struct Tetris* tetris_init() {
  struct Tetris* tetris = malloc(sizeof(struct Tetris));
  if (tetris == NULL) {
    perror("Error (tetris_init)");
    exit(EXIT_FAILURE);
  }
  tetris->last_occurence = 0;

  tetris->grid = malloc(sizeof(byte_t*) * GRID_HEIGHT);
  if (tetris->grid == NULL) {
    perror("Error (tetris_init)");
    exit(EXIT_FAILURE);
  }

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    tetris->grid[row] = malloc(sizeof(struct Block*) * GRID_WIDTH);
    if (tetris->grid[row] == NULL) {
      perror("Error (tetris_init)");
      exit(EXIT_FAILURE);
    }
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      struct Block* block = malloc(sizeof(struct Block));
      if (block == NULL) {
        perror("Error (tetris_init)");
        exit(EXIT_FAILURE);
      }
      block->type = TETROMINO_EMPTY;
      block->occurence = 0;
      tetris->grid[row][column] = block;
    }
  }

  return tetris;
}

void tetris_print(struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      printf("%c", tetris->grid[row][column]->type);
    }
    printf("\n");
  }
  printf("\n");
}

void tetris_free(struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      free(tetris->grid[row][column]);
    }
    free(tetris->grid[row]);
  }
  free(tetris->grid);
  free(tetris);
}

void tetris_add_tetromino(struct Tetris* tetris, byte_t type) {
  size_t row = 0;
  size_t column = GRID_WIDTH / 2;
  tetris->last_occurence += 1;

  switch (type) {
    case TETROMINO_SQUARE:
      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column - 1]->type = type;
      tetris->grid[row + 1][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;
      break;

    case TETROMINO_LINE:
      tetris->grid[row][column - 2]->type = type;
      tetris->grid[row][column - 2]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;
      break;

    case TETROMINO_L:
      tetris->grid[row + 1][column - 1]->type = type;
      tetris->grid[row + 1][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;
      break;

    case TETROMINO_J:
      tetris->grid[row + 1][column + 1]->type = type;
      tetris->grid[row + 1][column + 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;
      break;

    case TETROMINO_Z:
      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column + 1]->type = type;
      tetris->grid[row + 1][column + 1]->occurence = tetris->last_occurence;
      break;

    case TETROMINO_S:
      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column - 1]->type = type;
      tetris->grid[row + 1][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;
      break;

    case TETROMINO_T:
      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;
      break;
  }
}

void tetris_add_tetromino_random(struct Tetris* tetris) {
  byte_t tetrominos[] = {TETROMINO_LINE, TETROMINO_SQUARE, TETROMINO_T, TETROMINO_L, TETROMINO_Z, TETROMINO_J, TETROMINO_S};
  size_t tetrominos_size = sizeof(tetrominos) / sizeof(tetrominos[0]);
  byte_t tetromino = tetrominos[random_size_t(0, tetrominos_size - 1)];
  tetris_add_tetromino(tetris, tetromino);
}

struct Tetris* tetris_copy(struct Tetris* tetris) {
  struct Tetris* copy_tetris = tetris_init();
  copy_tetris->last_occurence = tetris->last_occurence;
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      copy_tetris->grid[row][column]->type = tetris->grid[row][column]->type;
      copy_tetris->grid[row][column]->occurence = tetris->grid[row][column]->occurence;
    }
  }
  return copy_tetris;
}

// void tetris_add_tetromino_random(struct Tetris* tetris) {
// }

void tetris_destroy_single_line(struct Tetris* tetris, int row) {
  for (int r = row; r > 0; r--) {
    for (int column = 0; column < GRID_WIDTH; column++) {
      tetris->grid[r][column]->type = tetris->grid[r - 1][column]->type;
      tetris->grid[r][column]->occurence = tetris->grid[r - 1][column]->occurence;
    }
  }

  for (int column = 0; column < GRID_WIDTH; column++) {
    tetris->grid[0][column]->type = TETROMINO_EMPTY;
    tetris->grid[0][column]->occurence = 0;
  }
}

void tetris_destroy_line(struct Tetris* tetris) {
  for (int row = 0; row < GRID_HEIGHT; row++) {
    int is_complete = 1;

    for (int column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->type == TETROMINO_EMPTY) {
        is_complete = 0;
        break;
      }
    }
    if (is_complete) {
      tetris_destroy_single_line(tetris, row);
      row--;
    }
  }
}

bool tetris_last_tetromino_step_down(struct Tetris* tetris) {
  bool can_move = true;

  for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
    for (int column = GRID_WIDTH - 1; column >= 0; column--) {
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

  return true;
}

void tetris_last_tetromino_step_left(struct Tetris* tetris) {
  bool is_moving = false;
  struct Tetris* copy_tetris = tetris_copy(tetris);

  for (int row = 0; row < GRID_HEIGHT; row++) {
    for (int column = 0; column < GRID_WIDTH; column++) {
      if (copy_tetris->grid[row][column]->occurence == copy_tetris->last_occurence) {
        if (column - 1 >= 0 && copy_tetris->grid[row][column - 1]->type == TETROMINO_EMPTY) {
          is_moving = true;
          copy_tetris->grid[row][column - 1]->type = copy_tetris->grid[row][column]->type;
          copy_tetris->grid[row][column - 1]->occurence = copy_tetris->grid[row][column]->occurence;

          copy_tetris->grid[row][column]->type = TETROMINO_EMPTY;
          copy_tetris->grid[row][column]->occurence = 0;
        } else if (is_moving) {
          tetris_free(copy_tetris);
          return;
        }
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
  bool is_moving = false;
  struct Tetris* copy_tetris = tetris_copy(tetris);

  for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
    for (int column = GRID_WIDTH - 1; column >= 0; column--) {
      if (copy_tetris->grid[row][column]->occurence == copy_tetris->last_occurence) {
        if (GRID_WIDTH > column + 1 && copy_tetris->grid[row][column + 1]->type == TETROMINO_EMPTY) {
          is_moving = true;
          copy_tetris->grid[row][column + 1]->type = copy_tetris->grid[row][column]->type;
          copy_tetris->grid[row][column + 1]->occurence = copy_tetris->grid[row][column]->occurence;

          copy_tetris->grid[row][column]->type = TETROMINO_EMPTY;
          copy_tetris->grid[row][column]->occurence = 0;
        } else if (is_moving) {
          tetris_free(copy_tetris);
          return;
        }
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
