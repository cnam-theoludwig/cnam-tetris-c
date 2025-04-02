#ifndef __TETRIS_LAST_TETROMINO_STEP__
#define __TETRIS_LAST_TETROMINO_STEP__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./tetris_struct.h"

bool tetris_last_tetromino_step_down(struct Tetris* tetris);

void tetris_last_tetromino_step_left(struct Tetris* tetris);

void tetris_last_tetromino_step_right(struct Tetris* tetris);

void tetris_last_tetromino_step_rotate_right(struct Tetris* tetris);

void tetris_last_tetromino_step_rotate_left(struct Tetris* tetris);

#endif
