#include "./tetris_game.h"

int tetris_game() {
  printf("Tetris game\n");
  struct Tetris* tetris = tetris_init();
  tetris_add_tetrimino(tetris, TETRIMINO_SQUARE);
  tetris_print(tetris);
  printf("\n---\n");
  tetris_step_down_last_tetrimino(tetris);
  tetris_print(tetris);
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
      block->type = TETRIMINO_EMPTY;
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

void tetris_add_tetrimino(struct Tetris* tetris, byte_t type) {
  size_t row = 0;
  size_t column = GRID_WIDTH / 2;
  tetris->last_occurence += 1;

  switch (type) {
    case TETRIMINO_SQUARE:
      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column - 1]->type = type;
      tetris->grid[row + 1][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row + 1][column]->type = type;
      tetris->grid[row + 1][column]->occurence = tetris->last_occurence;
      break;
    case TETRIMINO_LINE:
      tetris->grid[row][column - 2]->type = type;
      tetris->grid[row][column - 2]->occurence = tetris->last_occurence;

      tetris->grid[row][column - 1]->type = type;
      tetris->grid[row][column - 1]->occurence = tetris->last_occurence;

      tetris->grid[row][column]->type = type;
      tetris->grid[row][column]->occurence = tetris->last_occurence;

      tetris->grid[row][column + 1]->type = type;
      tetris->grid[row][column + 1]->occurence = tetris->last_occurence;

      break;
  }
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

// void tetris_add_tetrimino_random(struct Tetris* tetris) {
// }

void tetris_step_down_last_tetrimino(struct Tetris* tetris) {
  struct Tetris* copy_tetris = tetris_copy(tetris);
  for (size_t row = GRID_HEIGHT - 1; row > 0; row--) {
    for (size_t column = GRID_WIDTH - 1; column > 0; column--) {
      if (copy_tetris->grid[row][column]->occurence == tetris->last_occurence) {
        tetris->grid[row + 1][column]->type = copy_tetris->grid[row][column]->type;
        tetris->grid[row + 1][column]->occurence = copy_tetris->grid[row][column]->occurence;
        tetris->grid[row][column]->type = TETRIMINO_EMPTY;
        tetris->grid[row][column]->occurence = 0;
      }
    }
  }
  tetris_free(copy_tetris);
}
