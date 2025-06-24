#include <time.h>

#include "tetris.h"

int main() {
  srand((unsigned)time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    SDL_Quit();
    return EXIT_FAILURE;
  }
  if (TTF_Init() == -1) {
    SDL_Quit();
    return EXIT_FAILURE;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Window* menu_win = NULL;
  SDL_Renderer* menu_ren = NULL;
  GameMode mode = run_tetris_main_menu(&menu_win, &menu_ren);
  if (menu_ren) {
    SDL_DestroyRenderer(menu_ren);
  }
  if (menu_win) {
    SDL_DestroyWindow(menu_win);
  }

  while (mode != MODE_EXIT && mode != MODE_NONE) {
    if (mode == MODE_SOLO) {
      struct Tetris* game = tetris_init();
      int quit_flag = 0;
      while (true) {
        TetrisUIAction act = tetris_ui(game);
        if (act == UI_ACTION_RESTART) {
          tetris_free(game);
          game = tetris_init();
        } else if (act == UI_ACTION_QUIT) {
          tetris_free(game);
          quit_flag = 1;
          break;
        } else if (act == UI_ACTION_CONTINUE) {
          tetris_free(game);
          break;
        }
      }
      if (quit_flag) {
        break;
      }
    } else if (mode == MODE_1V1 || mode == MODE_1V1_AI) {
      struct Tetris* p1 = tetris_init();
      struct Tetris* p2 = tetris_init();
      int quit_flag = 0;
      SDL_Window* game_win = NULL;
      SDL_Renderer* game_ren = NULL;
      bool ai_right_player = (mode == MODE_1V1_AI);
      while (true) {
        TetrisUIAction act = tetris_ui_1v1(p1, p2, &game_win, &game_ren, ai_right_player);
        if (act == UI_ACTION_RESTART) {
          tetris_free(p1);
          tetris_free(p2);
          p1 = tetris_init();
          p2 = tetris_init();
        } else if (act == UI_ACTION_QUIT) {
          tetris_free(p1);
          tetris_free(p2);
          if (game_ren) SDL_DestroyRenderer(game_ren);
          if (game_win) SDL_DestroyWindow(game_win);
          game_ren = NULL;
          game_win = NULL;
          quit_flag = 1;
          break;
        } else if (act == UI_ACTION_CONTINUE) {
          tetris_free(p1);
          tetris_free(p2);
          if (game_ren) SDL_DestroyRenderer(game_ren);
          if (game_win) SDL_DestroyWindow(game_win);
          game_ren = NULL;
          game_win = NULL;
          break;
        }
      }
      if (quit_flag) {
        break;
      }
    }

    menu_win = NULL;
    menu_ren = NULL;
    mode = run_tetris_main_menu(&menu_win, &menu_ren);
    if (menu_ren) {
      SDL_DestroyRenderer(menu_ren);
    }
    if (menu_win) {
      SDL_DestroyWindow(menu_win);
    }
  }

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
  return EXIT_SUCCESS;
}
