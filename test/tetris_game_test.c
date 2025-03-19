#include "./tetris_game_test.h"

void tetris_game_test() {
  tetris_init_test();

  tetris_add_tetromino_line_test();
  tetris_add_tetromino_square_test();
  tetris_add_tetromino_t_test();
  tetris_add_tetromino_l_test();
  tetris_add_tetromino_j_test();
  tetris_add_tetromino_z_test();
  tetris_add_tetromino_s_test();

  tetris_last_tetromino_step_down_test();
  tetris_last_tetromino_step_down_with_add_test();
  tetris_last_tetromino_step_down_with_collisions();

  tetris_last_tetromino_step_left_test();
  tetris_last_tetromino_step_right_test();
}

void tetris_init_test() {
  struct Tetris* tetris = tetris_init();
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      assert(tetris->grid[row][column]->type == TETROMINO_EMPTY);
      assert(tetris->grid[row][column]->occurence == 0);
    }
  }
  tetris_free(tetris);
}

void tetris_add_tetromino_line_test() {
  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, TETROMINO_LINE);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[0][3]->type == TETROMINO_LINE);
  assert(tetris->grid[0][3]->occurence == 1);

  assert(tetris->grid[0][4]->type == TETROMINO_LINE);
  assert(tetris->grid[0][4]->occurence == 1);

  assert(tetris->grid[0][5]->type == TETROMINO_LINE);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[0][6]->type == TETROMINO_LINE);
  assert(tetris->grid[0][6]->occurence == 1);

  assert(tetris->grid[0][7]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][7]->occurence == 0);

  assert(tetris->grid[0][8]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][8]->occurence == 0);

  assert(tetris->grid[0][9]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][9]->occurence == 0);

  tetris_free(tetris);
}
void tetris_add_tetromino_square_test() {
  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, TETROMINO_SQUARE);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[0][3]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][3]->occurence == 0);

  assert(tetris->grid[0][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][4]->occurence == 1);

  assert(tetris->grid[1][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][4]->occurence == 1);

  assert(tetris->grid[0][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[1][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][5]->occurence == 1);

  tetris_free(tetris);
}
void tetris_add_tetromino_t_test() {
  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, TETROMINO_T);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[0][3]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][3]->occurence == 0);

  assert(tetris->grid[0][4]->type == TETROMINO_T);
  assert(tetris->grid[0][4]->occurence == 1);

  assert(tetris->grid[0][5]->type == TETROMINO_T);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[0][6]->type == TETROMINO_T);
  assert(tetris->grid[0][6]->occurence == 1);

  assert(tetris->grid[1][5]->type == TETROMINO_T);
  assert(tetris->grid[1][5]->occurence == 1);

  tetris_free(tetris);
}
void tetris_add_tetromino_l_test() {
  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, TETROMINO_L);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[0][3]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][3]->occurence == 0);

  assert(tetris->grid[0][4]->type == TETROMINO_L);
  assert(tetris->grid[0][4]->occurence == 1);

  assert(tetris->grid[1][4]->type == TETROMINO_L);
  assert(tetris->grid[1][4]->occurence == 1);

  assert(tetris->grid[0][5]->type == TETROMINO_L);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[0][6]->type == TETROMINO_L);
  assert(tetris->grid[0][6]->occurence == 1);

  tetris_free(tetris);
}
void tetris_add_tetromino_j_test() {
  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, TETROMINO_J);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[0][3]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][3]->occurence == 0);

  assert(tetris->grid[0][4]->type == TETROMINO_J);
  assert(tetris->grid[0][4]->occurence == 1);

  assert(tetris->grid[0][5]->type == TETROMINO_J);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[0][6]->type == TETROMINO_J);
  assert(tetris->grid[0][6]->occurence == 1);

  assert(tetris->grid[1][6]->type == TETROMINO_J);
  assert(tetris->grid[1][6]->occurence == 1);

  tetris_free(tetris);
}
void tetris_add_tetromino_z_test() {
  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, TETROMINO_Z);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[0][3]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][3]->occurence == 0);

  assert(tetris->grid[0][4]->type == TETROMINO_Z);
  assert(tetris->grid[0][4]->occurence == 1);

  assert(tetris->grid[0][5]->type == TETROMINO_Z);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[1][5]->type == TETROMINO_Z);
  assert(tetris->grid[1][5]->occurence == 1);

  assert(tetris->grid[1][6]->type == TETROMINO_Z);
  assert(tetris->grid[1][6]->occurence == 1);

  tetris_free(tetris);
}
void tetris_add_tetromino_s_test() {
  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, TETROMINO_S);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[0][3]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][3]->occurence == 0);

  assert(tetris->grid[0][5]->type == TETROMINO_S);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[0][6]->type == TETROMINO_S);
  assert(tetris->grid[0][6]->occurence == 1);

  assert(tetris->grid[1][4]->type == TETROMINO_S);
  assert(tetris->grid[1][4]->occurence == 1);

  assert(tetris->grid[1][5]->type == TETROMINO_S);
  assert(tetris->grid[1][5]->occurence == 1);

  tetris_free(tetris);
}

void tetris_last_tetromino_step_down_test() {
  struct Tetris* tetris = tetris_init();

  tetris_add_tetromino(tetris, TETROMINO_S);
  while (tetris_last_tetromino_step_down(tetris)) {
  }

  for (size_t row = 0; row < GRID_HEIGHT - 2; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      assert(tetris->grid[row][column]->type == TETROMINO_EMPTY);
      assert(tetris->grid[row][column]->occurence == 0);
    }
  }

  assert(tetris->grid[GRID_HEIGHT - 2][5]->type == TETROMINO_S);
  assert(tetris->grid[GRID_HEIGHT - 2][5]->occurence == 1);

  assert(tetris->grid[GRID_HEIGHT - 2][6]->type == TETROMINO_S);
  assert(tetris->grid[GRID_HEIGHT - 2][6]->occurence == 1);

  assert(tetris->grid[GRID_HEIGHT - 1][4]->type == TETROMINO_S);
  assert(tetris->grid[GRID_HEIGHT - 1][4]->occurence == 1);

  assert(tetris->grid[GRID_HEIGHT - 1][5]->type == TETROMINO_S);
  assert(tetris->grid[GRID_HEIGHT - 1][5]->occurence == 1);

  tetris_free(tetris);
}
void tetris_last_tetromino_step_down_with_add_test() {
  struct Tetris* tetris = tetris_init();

  tetris_add_tetromino(tetris, TETROMINO_S);
  while (tetris_last_tetromino_step_down(tetris)) {
  }

  tetris_add_tetromino(tetris, TETROMINO_SQUARE);

  assert(tetris->grid[0][3]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][3]->occurence == 0);

  assert(tetris->grid[0][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][4]->occurence == 2);

  assert(tetris->grid[1][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][4]->occurence == 2);

  assert(tetris->grid[0][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][5]->occurence == 2);

  assert(tetris->grid[1][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][5]->occurence == 2);

  tetris_free(tetris);
}
void tetris_last_tetromino_step_down_with_collisions() {
  struct Tetris* tetris = tetris_init();

  tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  while (tetris_last_tetromino_step_down(tetris)) {
  }

  tetris_add_tetromino(tetris, TETROMINO_LINE);
  while (tetris_last_tetromino_step_down(tetris)) {
  }

  assert(tetris->grid[GRID_HEIGHT - 2][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[GRID_HEIGHT - 2][4]->occurence == 1);

  assert(tetris->grid[GRID_HEIGHT - 2][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[GRID_HEIGHT - 2][5]->occurence == 1);

  assert(tetris->grid[GRID_HEIGHT - 1][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[GRID_HEIGHT - 1][4]->occurence == 1);

  assert(tetris->grid[GRID_HEIGHT - 1][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[GRID_HEIGHT - 1][5]->occurence == 1);

  assert(tetris->grid[0][0]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][0]->occurence == 0);

  assert(tetris->grid[0][1]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][1]->occurence == 0);

  assert(tetris->grid[0][2]->type == TETROMINO_EMPTY);
  assert(tetris->grid[0][2]->occurence == 0);

  assert(tetris->grid[GRID_HEIGHT - 3][3]->type == TETROMINO_LINE);
  assert(tetris->grid[GRID_HEIGHT - 3][3]->occurence == 2);

  assert(tetris->grid[GRID_HEIGHT - 3][4]->type == TETROMINO_LINE);
  assert(tetris->grid[GRID_HEIGHT - 3][4]->occurence == 2);

  assert(tetris->grid[GRID_HEIGHT - 3][5]->type == TETROMINO_LINE);
  assert(tetris->grid[GRID_HEIGHT - 3][5]->occurence == 2);

  assert(tetris->grid[GRID_HEIGHT - 3][6]->type == TETROMINO_LINE);
  assert(tetris->grid[GRID_HEIGHT - 3][6]->occurence == 2);

  assert(tetris->grid[GRID_HEIGHT - 3][7]->type == TETROMINO_EMPTY);
  assert(tetris->grid[GRID_HEIGHT - 3][7]->occurence == 0);

  assert(tetris->grid[GRID_HEIGHT - 3][8]->type == TETROMINO_EMPTY);
  assert(tetris->grid[GRID_HEIGHT - 3][8]->occurence == 0);

  assert(tetris->grid[GRID_HEIGHT - 3][9]->type == TETROMINO_EMPTY);
  assert(tetris->grid[GRID_HEIGHT - 3][9]->occurence == 0);

  tetris_free(tetris);
}

void tetris_last_tetromino_step_left_test() {
  struct Tetris* tetris = tetris_init();

  tetris_add_tetromino(tetris, TETROMINO_SQUARE);

  tetris_last_tetromino_step_left(tetris);
  assert(tetris->grid[0][3]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][3]->occurence == 1);

  assert(tetris->grid[0][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][4]->occurence == 1);

  assert(tetris->grid[1][3]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][3]->occurence == 1);

  assert(tetris->grid[1][4]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][4]->occurence == 1);

  tetris_last_tetromino_step_left(tetris);
  assert(tetris->grid[0][2]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][2]->occurence == 1);

  assert(tetris->grid[0][3]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][3]->occurence == 1);

  assert(tetris->grid[1][2]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][2]->occurence == 1);

  assert(tetris->grid[1][3]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][3]->occurence == 1);

  tetris_last_tetromino_step_left(tetris);
  assert(tetris->grid[0][1]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][1]->occurence == 1);

  assert(tetris->grid[0][2]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][2]->occurence == 1);

  assert(tetris->grid[1][1]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][1]->occurence == 1);

  assert(tetris->grid[1][2]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][2]->occurence == 1);

  tetris_last_tetromino_step_left(tetris);
  assert(tetris->grid[0][0]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][0]->occurence == 1);

  assert(tetris->grid[0][1]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][1]->occurence == 1);

  assert(tetris->grid[1][0]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][0]->occurence == 1);

  assert(tetris->grid[1][1]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][1]->occurence == 1);

  tetris_last_tetromino_step_left(tetris);
  assert(tetris->grid[0][0]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][0]->occurence == 1);

  assert(tetris->grid[0][1]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][1]->occurence == 1);

  assert(tetris->grid[1][0]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][0]->occurence == 1);

  assert(tetris->grid[1][1]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][1]->occurence == 1);

  tetris_free(tetris);
}

void tetris_last_tetromino_step_right_test() {
  struct Tetris* tetris = tetris_init();

  tetris_add_tetromino(tetris, TETROMINO_SQUARE);

  tetris_last_tetromino_step_right(tetris);
  assert(tetris->grid[0][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][5]->occurence == 1);

  assert(tetris->grid[0][6]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][6]->occurence == 1);

  assert(tetris->grid[1][5]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][5]->occurence == 1);

  assert(tetris->grid[1][6]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][6]->occurence == 1);

  tetris_last_tetromino_step_right(tetris);
  assert(tetris->grid[0][6]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][6]->occurence == 1);

  assert(tetris->grid[0][7]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][7]->occurence == 1);

  assert(tetris->grid[1][6]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][6]->occurence == 1);

  assert(tetris->grid[1][7]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][7]->occurence == 1);

  tetris_last_tetromino_step_right(tetris);
  assert(tetris->grid[0][7]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][7]->occurence == 1);

  assert(tetris->grid[0][8]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][8]->occurence == 1);

  assert(tetris->grid[1][7]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][7]->occurence == 1);

  assert(tetris->grid[1][8]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][8]->occurence == 1);

  tetris_last_tetromino_step_right(tetris);
  assert(tetris->grid[0][8]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][8]->occurence == 1);

  assert(tetris->grid[0][9]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][9]->occurence == 1);

  assert(tetris->grid[1][8]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][8]->occurence == 1);

  assert(tetris->grid[1][9]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][9]->occurence == 1);

  tetris_last_tetromino_step_right(tetris);
  assert(tetris->grid[0][8]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][8]->occurence == 1);

  assert(tetris->grid[0][9]->type == TETROMINO_SQUARE);
  assert(tetris->grid[0][9]->occurence == 1);

  assert(tetris->grid[1][8]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][8]->occurence == 1);

  assert(tetris->grid[1][9]->type == TETROMINO_SQUARE);
  assert(tetris->grid[1][9]->occurence == 1);

  tetris_free(tetris);
}
