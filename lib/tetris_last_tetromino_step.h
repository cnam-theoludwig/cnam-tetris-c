#ifndef __TETRIS_LAST_TETROMINO_STEP__
#define __TETRIS_LAST_TETROMINO_STEP__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./tetris_struct.h"

/**
 * @brief Move the last tetromino down if possible. Updates the pivot.
 */
bool tetris_last_tetromino_step_down(struct Tetris* tetris);

/**
 * @brief Move the last tetromino left if possible. Updates the pivot.
 */
void tetris_last_tetromino_step_left(struct Tetris* tetris);

/**
 * @brief Move the last tetromino right if possible. Updates the pivot.
 */
void tetris_last_tetromino_step_right(struct Tetris* tetris);

/**
 * @brief Rotate the last tetromino 90° clockwise around the stored pivot.
 */
void tetris_last_tetromino_step_rotate_right(struct Tetris* tetris);

/**
 * @brief Rotate the last tetromino 90° clockwise around the stored pivot.
 */
void tetris_last_tetromino_step_rotate_left(struct Tetris* tetris);

#endif
