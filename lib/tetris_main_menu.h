#ifndef __TETRIS_MAIN_MENU_H__
#define __TETRIS_MAIN_MENU_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "tetris_struct.h"
#include "tetris_ui.h"
#include "tetris_ui_1v1.h"

typedef enum {
  MODE_NONE = 0,
  MODE_SOLO,
  MODE_1V1,
  MODE_AI,
  MODE_EXIT
} GameMode;

GameMode run_tetris_main_menu(SDL_Window** window, SDL_Renderer** renderer);

#endif
