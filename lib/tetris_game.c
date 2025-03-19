#include "./tetris_game.h"

int tetris_game() {
  srand(time(NULL));
  printf("Tetris game\n");
  struct Tetris* tetris = tetris_init();

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  while (tetris_last_tetromino_step_down(tetris)) {

  tetris_add_tetromino_random(tetris);
  tetris_print(tetris);
  }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  tetris_last_tetromino_step_left(tetris);
  tetris_last_tetromino_step_left(tetris);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  tetris_last_tetromino_step_left(tetris);
  tetris_last_tetromino_step_left(tetris);
  tetris_last_tetromino_step_left(tetris);
  tetris_last_tetromino_step_left(tetris);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  // tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  tetris_add_tetromino(tetris, TETROMINO_T);
  while (tetris_last_tetromino_step_down(tetris)) {
    rotate_tetromino_left(tetris);
    tetris_print(tetris);
    printf("Rotate left\n");
    sleep(1);
    rotate_tetromino_left(tetris);
    tetris_print(tetris);
    printf("Rotate left\n");
    sleep(1);
    rotate_tetromino_left(tetris);
    tetris_print(tetris);
    printf("Rotate left\n");
    sleep(1);
    rotate_tetromino_left(tetris);
    tetris_print(tetris);
    printf("Rotate left\n");
    sleep(1);
    rotate_tetromino_right(tetris);
    tetris_print(tetris);
    printf("Rotate right\n");
    sleep(1);

  }

  // tetris_add_tetromino(tetris, TETROMINO_L);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  // tetris_add_tetromino(tetris, TETROMINO_Z);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  // tetris_add_tetromino(tetris, TETROMINO_J);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  // tetris_add_tetromino(tetris, TETROMINO_S);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
  }

  tetris_destroy_line(tetris);
  tetris_print(tetris);

  // tetris_add_tetromino(tetris, TETROMINO_LINE);
  while (tetris_last_tetromino_step_down(tetris)) {
    tetris_print(tetris);
    sleep(1);
  }

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
      tetris->grid[0][column]->type = TETROMINO_EMPTY;
      tetris->grid[0][column]->occurence = 0;
  }
}
// 1️⃣ Récupère les positions des blocs du TETROMINO actif et son type
int get_tetromino_blocks(struct Tetris* tetris, int blocks[TETROMINO_SIZE][2], int *tetromino_type) {
    int count = 0;
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int column = 0; column < GRID_WIDTH; column++) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                if (count == 0) {
                    *tetromino_type = tetris->grid[row][column]->type; // Récupérer le type
                }
                blocks[count][0] = column;
                blocks[count][1] = row;
                count++;
                if (count == TETROMINO_SIZE) return 1;
            }
        }
    }
    return 0; // Sécurité : si on n'a pas trouvé 4 blocs, on annule
}
// 📌 Définition des centres de rotation en fonction du type de Tetrimino
void get_rotation_center(int blocks[TETROMINO_SIZE][2], int *cx, int *cy, int tetromino_type) {
  switch (tetromino_type) {
      case TETROMINO_SQUARE:  // O ne tourne pas
          *cx = blocks[0][0];
          *cy = blocks[0][1];
          break;
      case TETROMINO_T:  // Le centre est le bloc du milieu sur la ligne horizontale
          *cx = blocks[1][0];
          *cy = blocks[1][1];
          break;
      case TETROMINO_LINE:  // Centre entre les 2 blocs du milieu
          *cx = (blocks[1][0] + blocks[2][0]) / 2;
          *cy = (blocks[1][1] + blocks[2][1]) / 2;
          break;
      case TETROMINO_S:  // On suit la structure 3x3
          *cx = blocks[1][0];
          *cy = blocks[1][1];
          break;
      case TETROMINO_L:  // Bloc vide dans la structure 3x3
          *cx = blocks[1][0];
          *cy = blocks[1][1];
          break;
      default:  // Pour J, Z, etc. : on prend le deuxième bloc
          *cx = blocks[1][0];
          *cy = blocks[1][1];
          break;
  }
}

// 📌 Calcule les nouvelles positions après rotation en fonction du sens
void compute_rotation(int blocks[TETROMINO_SIZE][2], int new_positions[TETROMINO_SIZE][2], int tetromino_type, int direction) {
  int cx, cy;
  get_rotation_center(blocks, &cx, &cy, tetromino_type);  // Récupérer le centre de rotation

  for (int i = 0; i < TETROMINO_SIZE; i++) {
      int x = blocks[i][0] - cx;
      int y = blocks[i][1] - cy;

      if (direction == 1) { // Rotation à droite (+90°)
          new_positions[i][0] = cx + y;
          new_positions[i][1] = cy - x;
      } else { // Rotation à gauche (-90°)
          new_positions[i][0] = cx - y;
          new_positions[i][1] = cy + x;
      }
  }
}

// 📌 Vérifie si la rotation est valide
int is_rotation_valid(struct Tetris* tetris, int new_positions[TETROMINO_SIZE][2]) {
  for (int i = 0; i < TETROMINO_SIZE; i++) {
      int new_x = new_positions[i][0];
      int new_y = new_positions[i][1];

      // Vérifie si la nouvelle position est en dehors de la grille
      if (new_x < 0 || new_x >= GRID_WIDTH || new_y < 0 || new_y >= GRID_HEIGHT) {
          return 0;
      }
      // Vérifie s'il y a un bloc qui appartient à un autre Tetrimino
      if (tetris->grid[new_y][new_x]->type != TETROMINO_EMPTY &&
          tetris->grid[new_y][new_x]->occurence != tetris->last_occurence) {
          return 0;
      }
  }
  return 1; // Rotation valide
}

// 📌 Applique la rotation sur le Tetrimino
void apply_rotation(struct Tetris* tetris, int blocks[TETROMINO_SIZE][2], int new_positions[TETROMINO_SIZE][2], int tetromino_type) {
  for (int i = 0; i < TETROMINO_SIZE; i++) {
      tetris->grid[blocks[i][1]][blocks[i][0]]->type = TETROMINO_EMPTY;
      tetris->grid[blocks[i][1]][blocks[i][0]]->occurence = 0;
  }
  for (int i = 0; i < TETROMINO_SIZE; i++) {
      tetris->grid[new_positions[i][1]][new_positions[i][0]]->type = tetromino_type;
      tetris->grid[new_positions[i][1]][new_positions[i][0]]->occurence = tetris->last_occurence;
  }
}

// 📌 Fonction principale qui gère la rotation à droite
void rotate_tetromino_right(struct Tetris* tetris) {
  int blocks[TETROMINO_SIZE][2], new_positions[TETROMINO_SIZE][2];
  int tetromino_type;

  // Récupérer les blocs du Tetrimino et son type
  if (!get_tetromino_blocks(tetris, blocks, &tetromino_type)) return;

  // Calculer la rotation vers la droite (+90°)
  compute_rotation(blocks, new_positions, tetromino_type, 1);

  // Vérifier si la rotation est possible
  if (!is_rotation_valid(tetris, new_positions)) return;

  // Appliquer la rotation
  apply_rotation(tetris, blocks, new_positions, tetromino_type);
}

// 📌 Fonction principale qui gère la rotation à gauche
void rotate_tetromino_left(struct Tetris* tetris) {
  int blocks[TETROMINO_SIZE][2], new_positions[TETROMINO_SIZE][2];
  int tetromino_type;

  // Récupérer les blocs du Tetrimino et son type
  if (!get_tetromino_blocks(tetris, blocks, &tetromino_type)) return;

  // Calculer la rotation vers la gauche (-90°)
  compute_rotation(blocks, new_positions, tetromino_type, -1);

  // Vérifier si la rotation est possible
  if (!is_rotation_valid(tetris, new_positions)) return;

  // Appliquer la rotation
  apply_rotation(tetris, blocks, new_positions, tetromino_type);
}
