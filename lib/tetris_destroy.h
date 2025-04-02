#ifndef __TETRIS_DESTROY__
#define __TETRIS_DESTROY__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./tetris_struct.h"

void tetris_destroy_line(struct Tetris* tetris);

void tetris_destroy_single_line(struct Tetris* tetris, size_t row);

#endif
