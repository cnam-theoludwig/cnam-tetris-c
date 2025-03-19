#include "./tetris_game.h"

int tetris_game() {
  srand(time(NULL));
  printf("Tetris game\n");
  struct Tetris* tetris = tetris_init();

  tetris_add_tetrimino(tetris, TETRIMINO_T);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_print(tetris);
  printf("-------------\n");
  rotate_tetrimino_right(tetris);
  tetris_print(tetris);
  printf("-------------\n");
  rotate_tetrimino_right(tetris);
  tetris_print(tetris);
  printf("-------------\n");
  rotate_tetrimino_right(tetris);
  tetris_print(tetris);
  printf("-------------\n");
  tetris_add_tetrimino(tetris, TETRIMINO_T);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);

  tetris_step_down_last_tetrimino(tetris);
  tetris_add_tetrimino(tetris, TETRIMINO_T);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);
  tetris_step_down_last_tetrimino(tetris);

  tetris_step_down_last_tetrimino(tetris);

  tetris_print(tetris);
  printf("-------------\n");


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
int tetris_can_tetrimino_step_down(struct Tetris* tetris) {
  for (int row = GRID_HEIGHT - 2; row >= 0; row--) {
      for (int column = GRID_WIDTH - 1; column >= 0; column--) {
          if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
              // Vérifier si la case en dessous est hors de la grille ou occupée par un autre Tetrimino
              if (row + 1 >= GRID_HEIGHT ||
                  (tetris->grid[row + 1][column]->type != TETRIMINO_EMPTY &&
                   tetris->grid[row + 1][column]->occurence != tetris->last_occurence)) {
                  printf("Cannot Move\n");
                  return 0;  // Collision détectée, le Tetrimino ne peut pas descendre
              }
          }
      }
  }
  return 1;  // Le Tetrimino peut descendre
}

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

void tetris_destroy_line(struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    bool is_complete = true;

    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (tetris->grid[row][column]->type == TETROMINO_EMPTY) {
        is_complete = false;
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
void tetris_step_down_last_tetrimino(struct Tetris* tetris) {
  int can_move = tetris_can_tetrimino_step_down(tetris);

  if (can_move) {
      // Parcourir la grille de bas en haut pour éviter d’écraser des parties qui n'ont pas encore bougé
      for (int row = GRID_HEIGHT - 2; row >= 0; row--) {
        for (int column = GRID_WIDTH - 1; column >= 0; column--) {
              if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                  // Déplacer la cellule vers le bas
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

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      if (copy_tetris->grid[row][column]->occurence == copy_tetris->last_occurence) {
        if (column > 0 && copy_tetris->grid[row][column - 1]->type == TETROMINO_EMPTY) {
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

  for (size_t row = GRID_HEIGHT - 1; row != SIZE_MAX; row--) {
    for (size_t column = GRID_WIDTH - 1; column != SIZE_MAX; column--) {
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
// 🛠 Fonction qui détruit UNE ligne et décale les autres vers le bas
void destroy_single_line(struct Tetris* tetris, int row) {
  printf("Destruction de la ligne %d\n", row);

  for (int r = row; r > 0; r--) {
      for (int column = 0; column < GRID_WIDTH; column++) {
          tetris->grid[r][column]->type = tetris->grid[r - 1][column]->type;
          tetris->grid[r][column]->occurence = tetris->grid[r - 1][column]->occurence;
      }
  }

  for (int column = 0; column < GRID_WIDTH; column++) {
      tetris->grid[0][column]->type = TETRIMINO_EMPTY;
      tetris->grid[0][column]->occurence = 0;
  }
}

void tetris_destroy_line(struct Tetris* tetris) {
  for (int row = 0; row < GRID_HEIGHT; row++) {
      int is_complete = 1;

      for (int column = 0; column < GRID_WIDTH; column++) {
          if (tetris->grid[row][column]->type == TETRIMINO_EMPTY) {
              is_complete = 0;
              break;
          }
      }
      if (is_complete) {
          destroy_single_line(tetris, row);
          row--;
      }
  }
}
// 1️⃣ Récupère les positions des blocs du Tetrimino actif et son type
int get_tetrimino_blocks(struct Tetris* tetris, int blocks[TETRIMINO_SIZE][2], int *tetrimino_type) {
    int count = 0;
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int column = 0; column < GRID_WIDTH; column++) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                if (count == 0) {
                    *tetrimino_type = tetris->grid[row][column]->type; // Récupérer le type
                }
                blocks[count][0] = column;
                blocks[count][1] = row;
                count++;
                if (count == TETRIMINO_SIZE) return 1;
            }
        }
    }
    return 0; // Sécurité : si on n'a pas trouvé 4 blocs, on annule
}

// 2️⃣ Calcule les nouvelles positions après rotation
void compute_rotation(int blocks[TETRIMINO_SIZE][2], int new_positions[TETRIMINO_SIZE][2]) {
    // Déterminer le centre de rotation (moyenne des coordonnées)
    int cx = (blocks[0][0] + blocks[1][0] + blocks[2][0] + blocks[3][0]) / 4;
    int cy = (blocks[0][1] + blocks[1][1] + blocks[2][1] + blocks[3][1]) / 4;

    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        int x = blocks[i][0], y = blocks[i][1];
        new_positions[i][0] = cx + (y - cy);
        new_positions[i][1] = cy - (x - cx);
    }
}

// 3️⃣ Vérifie si la rotation est valide
int is_rotation_valid(struct Tetris* tetris, int new_positions[TETRIMINO_SIZE][2]) {
    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        int new_x = new_positions[i][0];
        int new_y = new_positions[i][1];

        // Vérifie les limites de la grille
        if (new_x < 0 || new_x >= GRID_WIDTH || new_y < 0 || new_y >= GRID_HEIGHT) {
            return 0; // Rotation invalide
        }
        // Vérifie s'il y a un bloc qui appartient à un autre Tetrimino
        if (tetris->grid[new_y][new_x]->type != TETRIMINO_EMPTY &&
            tetris->grid[new_y][new_x]->occurence != tetris->last_occurence) {
            return 0; // Collision détectée
        }
    }
    return 1; // Rotation valide
}

// 4️⃣ Applique la rotation si elle est valide
void apply_rotation(struct Tetris* tetris, int blocks[TETRIMINO_SIZE][2], int new_positions[TETRIMINO_SIZE][2], int tetrimino_type) {
    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        tetris->grid[blocks[i][1]][blocks[i][0]]->type = TETRIMINO_EMPTY;
        tetris->grid[blocks[i][1]][blocks[i][0]]->occurence = 0;
    }
    for (int i = 0; i < TETRIMINO_SIZE; i++) {
        tetris->grid[new_positions[i][1]][new_positions[i][0]]->type = tetrimino_type;
        tetris->grid[new_positions[i][1]][new_positions[i][0]]->occurence = tetris->last_occurence;
    }
}

// 5️⃣ Fonction principale qui gère la rotation à droite
void rotate_tetrimino_right(struct Tetris* tetris) {
    int blocks[TETRIMINO_SIZE][2], new_positions[TETRIMINO_SIZE][2];
    int tetrimino_type;

    // Récupérer les blocs du Tetrimino et son type
    if (!get_tetrimino_blocks(tetris, blocks, &tetrimino_type)) return;

    // Calculer la rotation
    compute_rotation(blocks, new_positions);

    // Vérifier si la rotation est possible
    if (!is_rotation_valid(tetris, new_positions)) return;

    // Appliquer la rotation
    apply_rotation(tetris, blocks, new_positions, tetrimino_type);
}
