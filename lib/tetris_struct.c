#include "./tetris_struct.h"

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
    tetris->grid[row] = malloc(sizeof(struct TetrisBlock*) * GRID_WIDTH);
    if (tetris->grid[row] == NULL) {
      perror("Error (tetris_init)");
      exit(EXIT_FAILURE);
    }
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      struct TetrisBlock* block = malloc(sizeof(struct TetrisBlock));
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
