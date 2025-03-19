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
#define TETROMINO_SIZE 4

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

void tetris_add_tetromino_random(struct Tetris* tetris);

bool tetris_last_tetromino_step_down(struct Tetris* tetris);

void tetris_last_tetromino_step_left(struct Tetris* tetris);

void tetris_last_tetromino_step_right(struct Tetris* tetris);

struct Tetris* tetris_copy(struct Tetris* tetris);

void tetris_destroy_single_line(struct Tetris* tetris, size_t row);

int tetris_can_tetromino_step_down(struct Tetris* tetris) ;

void tetris_destroy_line(struct Tetris* tetris);

void destroy_single_line(struct Tetris* tetris, int row);

int get_tetromino_blocks(struct Tetris* tetris, int blocks[TETROMINO_SIZE][2], int *tetromino_type) ;


int is_rotation_valid(struct Tetris* tetris, int new_positions[TETROMINO_SIZE][2]);


void compute_rotation(int blocks[TETROMINO_SIZE][2], int new_positions[TETROMINO_SIZE][2], int tetromino_type, int direction) ;

void rotate_tetromino_right(struct Tetris* tetris);

void rotate_tetromino_left(struct Tetris* tetris);

void apply_rotation(struct Tetris* tetris, int blocks[TETROMINO_SIZE][2], int new_positions[TETROMINO_SIZE][2], int tetromino_type);

void get_rotation_center(int blocks[TETROMINO_SIZE][2], int *cx, int *cy, int tetromino_type) ;

#endif
