#ifndef __TETRIS_UI__
#define __TETRIS_UI__

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../dependencies/SDL/include/SDL.h"
#include "../dependencies/SDL_image/include/SDL_image.h"
#include "../dependencies/SDL_ttf/SDL_ttf.h"
#include "tetris_add_tetromino.h"
#include "tetris_destroy.h"
#include "tetris_last_tetromino_step.h"
#include "tetris_struct.h"

#define TETRIS_WINDOW_WIDTH 640
#define GRID_BLOCK_SIZE 30
#define GRID_BORDER_SIZE 2
#define GRID_OFFSET_X 160
#define GRID_OFFSET_Y 40
#define TETRIS_WINDOW_HEIGHT (GRID_OFFSET_Y + GRID_HEIGHT * GRID_BLOCK_SIZE + GRID_OFFSET_Y)

#define SCORE_OFFSET_X (GRID_OFFSET_X + (GRID_WIDTH * GRID_BLOCK_SIZE) + 40)
#define SCORE_OFFSET_Y 80
#define LEVEL_OFFSET_X SCORE_OFFSET_X
#define LEVEL_OFFSET_Y (SCORE_OFFSET_Y + 70)

#define NEXT_LABEL_OFFSET_X SCORE_OFFSET_X
#define NEXT_LABEL_OFFSET_Y (LEVEL_OFFSET_Y + 70)
#define NEXT_PIECE_AREA_OFFSET_X SCORE_OFFSET_X
#define NEXT_PIECE_AREA_OFFSET_Y (NEXT_LABEL_OFFSET_Y + 40)
#define NEXT_PIECE_BLOCK_SIZE 20
#define NEXT_PIECE_AREA_WIDTH (4 * NEXT_PIECE_BLOCK_SIZE)
#define NEXT_PIECE_AREA_HEIGHT (4 * NEXT_PIECE_BLOCK_SIZE)

#define BACKGROUND_COLOR_R 0x1a
#define BACKGROUND_COLOR_G 0x1a
#define BACKGROUND_COLOR_B 0x1a
#define BACKGROUND_COLOR_A 255

#define GRID_BORDER_COLOR_R 128
#define GRID_BORDER_COLOR_G 128
#define GRID_BORDER_COLOR_B 128
#define GRID_BORDER_COLOR_A 255

typedef enum {
  PAUSE_MENU_RESUME,
  PAUSE_MENU_RESTART,
  PAUSE_MENU_MAIN_MENU,
  PAUSE_MENU_OPTION_COUNT
} PauseMenuOption;

typedef enum {
  UI_ACTION_CONTINUE,
  UI_ACTION_QUIT,
  UI_ACTION_RESTART
} TetrisUIAction;

#define PAUSE_BUTTON_X 10
#define PAUSE_BUTTON_Y 10
#define PAUSE_BUTTON_SIZE 40

TetrisUIAction tetris_ui(struct Tetris* tetris);

void tetris_ui_render_block(SDL_Renderer* renderer, int x, int y, int block_size, byte_t type);

void tetris_ui_render_grid(SDL_Renderer* renderer, struct Tetris* tetris);
void tetris_ui_render_score(SDL_Renderer* renderer, struct Tetris* tetris);
void tetris_ui_render_level(SDL_Renderer* renderer, struct Tetris* tetris);
void tetris_ui_render_next_tetromino(SDL_Renderer* renderer, struct Tetris* tetris);
void tetris_ui_render_pause_menu(SDL_Renderer* renderer, struct Tetris* tetris);
void tetris_ui_render_block(SDL_Renderer* renderer, int x, int y, int block_size, byte_t type);

#endif
