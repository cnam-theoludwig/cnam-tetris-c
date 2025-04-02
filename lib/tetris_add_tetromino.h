#ifndef __TETRIS_ADD_TETROMINO__
#define __TETRIS_ADD_TETROMINO__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./tetris_struct.h"
#include "./utils.h"

void tetris_add_tetromino(struct Tetris* tetris, byte_t type);

byte_t tetris_get_tetromino_random();

#endif
