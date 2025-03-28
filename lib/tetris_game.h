#ifndef __TETRIS_GAME__
#define __TETRIS_GAME__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dependencies/SDL/include/SDL.h"
#include "../dependencies/libcproject/libcproject.h"
#include "./random.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

#define TETROMINO_EMPTY '0'
#define TETROMINO_LINE 'I'
#define TETROMINO_SQUARE 'O'
#define TETROMINO_T 'T'
#define TETROMINO_L 'L'
#define TETROMINO_J 'J'
#define TETROMINO_Z 'Z'
#define TETROMINO_S 'S'

struct Tetris {
  struct TetrisBlock*** grid;
  size_t score;
  size_t last_occurence;
};

struct TetrisBlock {
  byte_t type;
  size_t occurence;
};

void tetris_print(struct Tetris* tetris);

struct Tetris* tetris_init();

void tetris_free(struct Tetris* tetris);

void tetris_add_tetromino(struct Tetris* tetris, byte_t type);

void tetris_add_tetromino_random(struct Tetris* tetris);

bool tetris_last_tetromino_step_down(struct Tetris* tetris);

void tetris_last_tetromino_step_left(struct Tetris* tetris);

void tetris_last_tetromino_step_right(struct Tetris* tetris);

struct Tetris* tetris_copy(struct Tetris* tetris);

void tetris_destroy_line(struct Tetris* tetris);

void tetris_destroy_single_line(struct Tetris* tetris, size_t row);

#endif
