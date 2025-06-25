#ifndef TETRIS_VS_IA_H
#define TETRIS_VS_IA_H

#include "tetris_1v1.h"
#include "tetris_struct.h"
#include "tetris_ui.h"

TetrisUIAction tetris_ui_vs_ai(struct Tetris* human,
                               struct Tetris* ia,
                               SDL_Window** window,
                               SDL_Renderer** renderer);

#endif
