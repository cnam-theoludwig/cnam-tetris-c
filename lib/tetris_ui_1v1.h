#ifndef __TETRIS_UI_1V1__
#define __TETRIS_UI_1V1__

#include "tetris_1v1.h"
#include "tetris_struct.h"
#include "tetris_ui.h"

SDL_Texture* load_texture_from_file(const char* path, SDL_Renderer* renderer);

TetrisUIAction tetris_ui_1v1(struct Tetris* p1, struct Tetris* p2, SDL_Window** window, SDL_Renderer** renderer, bool ai_right_player);

#endif
