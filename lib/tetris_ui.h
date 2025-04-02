#ifndef __TETRIS_UI__
#define __TETRIS_UI__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dependencies/SDL/include/SDL.h"
#include "../tetris.h"

#define TETRIS_WINDOW_WIDTH 400
#define TETRIS_WINDOW_HEIGHT 800
#define TETRIS_BLOCK_SIZE (TETRIS_WINDOW_WIDTH / GRID_WIDTH)

int tetris_ui();

void tetris_ui_render_grid(SDL_Renderer* renderer, struct Tetris* tetris);

#endif
