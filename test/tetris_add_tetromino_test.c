#include "./tetris_add_tetromino_test.h"

void tetris_add_tetromino_test() {
  tetris_add_tetromino_line_test();
  tetris_add_tetromino_square_test();
  tetris_add_tetromino_t_test();
  tetris_add_tetromino_l_test();
  tetris_add_tetromino_j_test();
  tetris_add_tetromino_z_test();
  tetris_add_tetromino_s_test();
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
  printf("tetris_add_tetromino_line_test\n");
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
  printf("tetris_add_tetromino_square_test\n");
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
  printf("tetris_add_tetromino_t_test\n");
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
  printf("tetris_add_tetromino_l_test\n");
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
  printf("tetris_add_tetromino_j_test\n");
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
  printf("tetris_add_tetromino_z_test\n");
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
  printf("tetris_add_tetromino_s_test\n");
}
