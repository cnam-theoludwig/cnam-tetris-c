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

/**
 * @struct Tetris
 * @brief Represents the Tetris game state, including the grid, score, and last active Tetromino.
 */
struct Tetris {
    /** The game grid containing blocks */
    struct Block*** grid;

    /** The current player score */
    size_t score;

    /** Identifier of the last placed Tetromino */
    size_t last_occurence;
};

/**
 * @struct Block
 * @brief Represents a single block in the Tetris grid.
 */
struct Block {
    /** The type of the block (Tetromino identifier) */
    byte_t type;

    /** Unique occurrence ID of the Tetromino to which the block belongs */
    size_t occurence;
};

/**
 * @brief Starts the Tetris game loop.
 * @return 0 on successful execution, non-zero otherwise.
 */
int tetris_game();

/**
 * @brief Prints the current Tetris grid to the console.
 * @param tetris Pointer to the Tetris game instance.
 */
void tetris_print(struct Tetris* tetris);

/**
 * @brief Initializes a new Tetris game instance.
 * @return Pointer to the newly allocated Tetris game structure.
 */
struct Tetris* tetris_init();

/**
 * @brief Frees the memory allocated for a Tetris game instance.
 * @param tetris Pointer to the Tetris game instance.
 */
void tetris_free(struct Tetris* tetris);

/**
 * @brief Adds a specific Tetromino to the game grid.
 * @param tetris Pointer to the Tetris game instance.
 * @param type The type of Tetromino to add.
 */
void tetris_add_tetromino(struct Tetris* tetris, byte_t type);

/**
 * @brief Adds a random Tetromino to the game grid.
 * @param tetris Pointer to the Tetris game instance.
 */
void tetris_add_tetromino_random(struct Tetris* tetris);

/**
 * @brief Moves the last active Tetromino down by one step.
 * @param tetris Pointer to the Tetris game instance.
 * @return True if the move was successful, false if blocked.
 */
bool tetris_last_tetromino_step_down(struct Tetris* tetris);

/**
 * @brief Moves the last active Tetromino one step to the left.
 * @param tetris Pointer to the Tetris game instance.
 */
void tetris_last_tetromino_step_left(struct Tetris* tetris);

/**
 * @brief Moves the last active Tetromino one step to the right.
 * @param tetris Pointer to the Tetris game instance.
 */
void tetris_last_tetromino_step_right(struct Tetris* tetris);

/**
 * @brief Creates a copy of the current Tetris game instance.
 * @param tetris Pointer to the Tetris game instance.
 * @return Pointer to the copied Tetris structure.
 */
struct Tetris* tetris_copy(struct Tetris* tetris);

/**
 * @brief Destroys a single line in the Tetris grid and shifts the above rows down.
 * @param tetris Pointer to the Tetris game instance.
 * @param row The row index to be destroyed.
 */
void tetris_destroy_single_line(struct Tetris* tetris, size_t row);

/**
 * @brief Checks if the last Tetromino can move down.
 * @param tetris Pointer to the Tetris game instance.
 * @return 1 if the move is possible, 0 otherwise.
 */
int tetris_can_tetromino_step_down(struct Tetris* tetris);

/**
 * @brief Destroys all complete lines in the Tetris grid.
 * @param tetris Pointer to the Tetris game instance.
 */
void tetris_destroy_line(struct Tetris* tetris);

/**
 * @brief Destroys a single line in the Tetris grid and shifts down the above rows.
 * @param tetris Pointer to the Tetris game instance.
 * @param row The row index to be destroyed.
 */
void destroy_single_line(struct Tetris* tetris, int row);

/**
 * @brief Retrieves the positions of blocks belonging to the last Tetromino.
 * @param tetris Pointer to the Tetris game instance.
 * @param blocks Output array to store the block positions.
 * @param tetromino_type Output variable to store the type of Tetromino.
 * @return 1 if successful, 0 otherwise.
 */
int get_tetromino_blocks(struct Tetris* tetris, int blocks[TETROMINO_SIZE][2], int *tetromino_type);

/**
 * @brief Checks if the proposed Tetromino rotation is valid.
 * @param tetris Pointer to the Tetris game instance.
 * @param new_positions Array of new block positions after rotation.
 * @return 1 if the rotation is valid, 0 otherwise.
 */
int is_rotation_valid(struct Tetris* tetris, int new_positions[TETROMINO_SIZE][2]);

/**
 * @brief Computes the new positions of a Tetromino after rotation.
 * @param blocks Array containing the current block positions.
 * @param new_positions Output array storing the new block positions after rotation.
 * @param tetromino_type The type of Tetromino being rotated.
 * @param direction Rotation direction (1 for right, -1 for left).
 */
void compute_rotation(int blocks[TETROMINO_SIZE][2], int new_positions[TETROMINO_SIZE][2], int tetromino_type, int direction);

/**
 * @brief Rotates the last active Tetromino 90° clockwise.
 * @param tetris Pointer to the Tetris game instance.
 */
void rotate_tetromino_right(struct Tetris* tetris);

/**
 * @brief Rotates the last active Tetromino 90° counterclockwise.
 * @param tetris Pointer to the Tetris game instance.
 */
void rotate_tetromino_left(struct Tetris* tetris);

/**
 * @brief Applies the computed rotation to the Tetris grid.
 * @param tetris Pointer to the Tetris game instance.
 * @param blocks Array of original block positions.
 * @param new_positions Array of new block positions after rotation.
 * @param tetromino_type The type of Tetromino being rotated.
 */
void apply_rotation(struct Tetris* tetris, int blocks[TETROMINO_SIZE][2], int new_positions[TETROMINO_SIZE][2], int tetromino_type);

/**
 * @brief Determines the rotation center of a Tetromino based on its type.
 * @param blocks Array containing the block positions of the Tetromino.
 * @param cx Output variable storing the X-coordinate of the rotation center.
 * @param cy Output variable storing the Y-coordinate of the rotation center.
 * @param tetromino_type The type of Tetromino.
 */
void get_rotation_center(int blocks[TETROMINO_SIZE][2], int *cx, int *cy, int tetromino_type);

#endif
