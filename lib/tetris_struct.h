#ifndef __TETRIS_STRUCT__
#define __TETRIS_STRUCT__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

#define SCORE_SINGLE 40
#define SCORE_DOUBLE 100
#define SCORE_TRIPLE 300
#define SCORE_TETRIS 1200

#define TETRIS_LEVEL_STEP 10

typedef uint8_t byte_t;

typedef char* string_t;

typedef float float32_t;
typedef double float64_t;

struct Tetris {
  struct TetrisBlock*** grid;
  size_t score;
  size_t destroyed_lines_count;

  size_t last_occurence;
  byte_t last_type;
  size_t last_pivot_x;
  size_t last_pivot_y;
};

struct TetrisBlock {
  byte_t type;
  size_t occurence;
};

void tetris_print(struct Tetris* tetris);

struct Tetris* tetris_init();

void tetris_free(struct Tetris* tetris);

struct Tetris* tetris_copy(struct Tetris* tetris);

size_t tetris_get_level(struct Tetris* tetris);

#endif
