#ifndef __TETRIS_GAME__
#define __TETRIS_GAME__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dependencies/SDL/include/SDL.h"
#include "../dependencies/libcproject/libcproject.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

#define tetromino_EMPTY '0'
#define tetromino_LINE 'I'
#define tetromino_SQUARE 'O'
#define tetromino_T 'T'
#define tetromino_L 'L'
#define tetromino_Z 'Z'
#define tetromino_J 'J'
#define tetromino_S 'S'

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

void tetris_add_tetromino(struct Tetris* tetris, byte_t type);

// void tetris_add_tetromino_random(struct Tetris* tetris);

bool tetris_last_tetromino_step_down(struct Tetris* tetris);

void tetris_last_tetromino_step_left(struct Tetris* tetris);

void tetris_last_tetromino_step_right(struct Tetris* tetris);

struct Tetris* tetris_copy(struct Tetris* tetris);

void tetris_destroy_line(struct Tetris* tetris);

void tetris_destroy_single_line(struct Tetris* tetris, int row);

#endif
