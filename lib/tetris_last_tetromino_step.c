#include "./tetris_last_tetromino_step.h"

/**
 * @brief Move the last tetromino down if possible. Updates the pivot.
 */
bool tetris_last_tetromino_step_down(struct Tetris* tetris) {
    bool can_move = true;

    // Step 1: Check collisions
    for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
        for (int column = GRID_WIDTH - 1; column >= 0; column--) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                if (row + 1 >= GRID_HEIGHT ||
                    (tetris->grid[row + 1][column]->type != TETROMINO_EMPTY &&
                     tetris->grid[row + 1][column]->occurence != tetris->last_occurence)) {
                    can_move = false;
                    break;
                }
            }
        }
        if (!can_move) break;
    }

    if (!can_move) {
        return false;
    }

    // Step 2: Move blocks downward
    for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
        for (int column = GRID_WIDTH - 1; column >= 0; column--) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                tetris->grid[row + 1][column]->type = tetris->grid[row][column]->type;
                tetris->grid[row + 1][column]->occurence = tetris->grid[row][column]->occurence;

                tetris->grid[row][column]->type = TETROMINO_EMPTY;
                tetris->grid[row][column]->occurence = 0;
            }
        }
    }

    // Step 3: Update pivot
    tetris->last_pivot_y += 1;

    return true;
}

/**
 * @brief Move the last tetromino left if possible. Updates the pivot.
 */
void tetris_last_tetromino_step_left(struct Tetris* tetris) {
    bool can_move = true;

    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int column = 0; column < GRID_WIDTH; column++) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                if (column == 0 || (tetris->grid[row][column - 1]->type != TETROMINO_EMPTY &&
                    tetris->grid[row][column - 1]->occurence != tetris->last_occurence)) {
                    can_move = false;
                    break;
                }
            }
        }
        if (!can_move) break;
    }

    if (!can_move) return;

    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int column = 0; column < GRID_WIDTH; column++) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                tetris->grid[row][column - 1]->type = tetris->grid[row][column]->type;
                tetris->grid[row][column - 1]->occurence = tetris->grid[row][column]->occurence;

                tetris->grid[row][column]->type = TETROMINO_EMPTY;
                tetris->grid[row][column]->occurence = 0;
            }
        }
    }

    tetris->last_pivot_x -= 1;
}

/**
 * @brief Move the last tetromino right if possible. Updates the pivot.
 */
void tetris_last_tetromino_step_right(struct Tetris* tetris) {
    bool can_move = true;

    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int column = GRID_WIDTH - 1; column >= 0; column--) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                if (column + 1 >= GRID_WIDTH || (tetris->grid[row][column + 1]->type != TETROMINO_EMPTY &&
                    tetris->grid[row][column + 1]->occurence != tetris->last_occurence)) {
                    can_move = false;
                    break;
                }
            }
        }
        if (!can_move) break;
    }

    if (!can_move) return;

    for (int row = GRID_HEIGHT - 1; row >= 0; row--) {
        for (int column = GRID_WIDTH - 1; column >= 0; column--) {
            if (tetris->grid[row][column]->occurence == tetris->last_occurence) {
                tetris->grid[row][column + 1]->type = tetris->grid[row][column]->type;
                tetris->grid[row][column + 1]->occurence = tetris->grid[row][column]->occurence;

                tetris->grid[row][column]->type = TETROMINO_EMPTY;
                tetris->grid[row][column]->occurence = 0;
            }
        }
    }

    tetris->last_pivot_x += 1;
}

/**
 * @brief Rotate the last tetromino 90° clockwise around the stored pivot.
 */
void tetris_last_tetromino_rotate_right(struct Tetris* tetris) {
    if (tetris->last_type == TETROMINO_SQUARE) {
        printf("[ROTATE] Square does not rotate.\n");
        return;
    }

    int blocks[4][2];
    int rotated[4][2];
    int count = 0;

    printf("[ROTATE] Attempting to rotate tetromino type %c\n", tetris->last_type);

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (tetris->grid[y][x]->occurence == tetris->last_occurence) {
                blocks[count][0] = x;
                blocks[count][1] = y;
                count++;
                if (count == 4) break;
            }
        }
        if (count == 4) break;
    }

    if (count != 4) {
        printf("[ROTATE] Not enough blocks found.\n");
        return;
    }

    int cx = tetris->last_pivot_x;
    int cy = tetris->last_pivot_y;
    printf("  [PIVOT] (%d, %d)\n", cx, cy);

    for (int i = 0; i < 4; i++) {
        int dx = blocks[i][0] - cx;
        int dy = blocks[i][1] - cy;
        rotated[i][0] = cx + dy;
        rotated[i][1] = cy - dx;
        printf("  [ROTATED %d] (%d, %d)\n", i, rotated[i][0], rotated[i][1]);
    }

    for (int i = 0; i < 4; i++) {
        int x = rotated[i][0];
        int y = rotated[i][1];

        if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
            printf("  [INVALID] Out of bounds (%d, %d)\n", x, y);
            return;
        }

        if (tetris->grid[y][x]->type != TETROMINO_EMPTY &&
            tetris->grid[y][x]->occurence != tetris->last_occurence) {
            printf("  [INVALID] Collision at (%d, %d)\n", x, y);
            return;
        }
    }

    for (int i = 0; i < 4; i++) {
        int x = blocks[i][0];
        int y = blocks[i][1];
        tetris->grid[y][x]->type = TETROMINO_EMPTY;
        tetris->grid[y][x]->occurence = 0;
    }

    for (int i = 0; i < 4; i++) {
        int x = rotated[i][0];
        int y = rotated[i][1];
        tetris->grid[y][x]->type = tetris->last_type;
        tetris->grid[y][x]->occurence = tetris->last_occurence;
    }

    printf("[ROTATE] Rotation applied successfully.\n");
}

/**
 * @brief Rotate the last tetromino 90° clockwise around the stored pivot.
 */
void tetris_last_tetromino_rotate_left(struct Tetris* tetris) {
  tetris_last_tetromino_rotate_right(tetris);
  tetris_last_tetromino_rotate_right(tetris);
  tetris_last_tetromino_rotate_right(tetris);
}
