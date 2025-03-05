#ifndef __TETRIS_GAME__
#define __TETRIS_GAME__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dependencies/SDL/include/SDL.h"
#include "../dependencies/libcproject/libcproject.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

#define TETRIMINO_EMPTY '0'
#define TETRIMINO_LINE 'I'
#define TETRIMINO_SQUARE 'O'
#define TETRIMINO_T 'T'
#define TETRIMINO_L 'L'
#define TETRIMINO_Z 'Z'
#define TETRIMINO_J 'J'
#define TETRIMINO_S 'S'

struct Tetris {
  struct Block*** grid;
  size_t score;
  size_t last_occurence;
};

struct Block {
  byte_t type;
  size_t occurence;
};

int tetris_game();

void tetris_print(struct Tetris* tetris);

struct Tetris* tetris_init();

void tetris_free(struct Tetris* tetris);

void tetris_add_tetrimino(struct Tetris* tetris, byte_t type);

// void tetris_add_tetrimino_random(struct Tetris* tetris);

bool tetris_step_down_last_tetrimino(struct Tetris* tetris);

struct Tetris* tetris_copy(struct Tetris* tetris);

void tetris_destroy_line(struct Tetris* tetris);

void tetris_destroy_single_line(struct Tetris* tetris, int row);

#endif
