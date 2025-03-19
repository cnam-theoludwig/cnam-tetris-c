#ifndef __TETRIS_GAME_TEST__
#define __TETRIS_GAME_TEST__

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "tetris.h"

void tetris_game_test();

void tetris_init_test();

void tetris_add_tetromino_line_test();
void tetris_add_tetromino_square_test();
void tetris_add_tetromino_t_test();
void tetris_add_tetromino_l_test();
void tetris_add_tetromino_j_test();
void tetris_add_tetromino_z_test();
void tetris_add_tetromino_s_test();

void tetris_last_tetromino_step_down_test();
void tetris_last_tetromino_step_down_with_add_test();
void tetris_last_tetromino_step_down_with_collisions();

void tetris_last_tetromino_step_left_test();
void tetris_last_tetromino_step_right_test();

#endif
