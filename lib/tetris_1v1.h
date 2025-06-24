#ifndef __TETRIS_1V1__
#define __TETRIS_1V1__

#include "tetris_1v1.h"
#include "tetris_destroy.h"
#include "tetris_struct.h"
#include <stdlib.h>

size_t tetris_1v1_handle_lines_and_attack(struct Tetris* self, struct Tetris* opponent) ;

void tetris_1v1_receive_garbage(struct Tetris* tetris, size_t lines);

#endif // __TETRIS_1V1__
