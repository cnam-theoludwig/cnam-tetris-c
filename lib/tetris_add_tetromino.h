#ifndef __TETRIS_ADD_TETROMINO__
#define __TETRIS_ADD_TETROMINO__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tetris_struct.h"
#include "utils.h"

struct Tetris;

/**
 * @brief
 *
 * @param tetris
 * @param type
 * @return bool true if the tetromino has space to be added, false otherwise.
 */
bool tetris_add_tetromino(struct Tetris* tetris);

uint8_t tetris_get_tetromino_random();

#endif
