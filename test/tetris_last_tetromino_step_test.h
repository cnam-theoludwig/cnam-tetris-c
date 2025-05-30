#ifndef __TETRIS_LAST_TETROMINO_STEP_TEST__
#define __TETRIS_LAST_TETROMINO_STEP_TEST__

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/tetris_add_tetromino.h"
#include "../lib/tetris_last_tetromino_step.h"
#include "../lib/tetris_struct.h"

void tetris_last_tetromino_step_test();

void tetris_last_tetromino_step_down_test();
void tetris_last_tetromino_step_down_with_add_test();
void tetris_last_tetromino_step_down_with_collisions_test();

void tetris_last_tetromino_step_left_test();
void tetris_last_tetromino_step_right_test();

#endif
