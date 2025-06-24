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

  if (mode == MODE_SOLO) {
    struct Tetris* game = tetris_init();
    while (true) {
      TetrisUIAction act = tetris_ui(game);
      if (act == UI_ACTION_RESTART) {
        tetris_free(game);
        game = tetris_init();
      } else if (act == UI_ACTION_QUIT) {
        break;
      }
    }
    tetris_free(game);
  } else if (mode == MODE_1V1) {
    struct Tetris* p1 = tetris_init();
    struct Tetris* p2 = tetris_init();
    bool running_1v1 = true;
    while (running_1v1) {
      TetrisUIAction act = tetris_ui_1v1(p1, p2);
      if (act == UI_ACTION_RESTART) {
        tetris_free(p1);
        tetris_free(p2);
        p1 = tetris_init();
        p2 = tetris_init();
      } else if (act == UI_ACTION_QUIT) {
        break;
      } else if (act == UI_ACTION_CONTINUE) {
        tetris_free(p1);
        tetris_free(p2);
        menu_win = NULL;
        menu_ren = NULL;
        mode = run_tetris_main_menu(&menu_win, &menu_ren);
        if (menu_ren) SDL_DestroyRenderer(menu_ren);
        if (menu_win) SDL_DestroyWindow(menu_win);
        if (mode == MODE_SOLO) {
          struct Tetris* game = tetris_init();
          while (1) {
            TetrisUIAction solo_act = tetris_ui(game);
            if (solo_act == UI_ACTION_RESTART) {
              tetris_free(game);
              game = tetris_init();
            } else if (solo_act == UI_ACTION_QUIT) {
              break;
            }
          }
          tetris_free(game);
          running_1v1 = false;
        } else if (mode == MODE_1V1) {
          p1 = tetris_init();
          p2 = tetris_init();
          continue;
        } else {
          running_1v1 = false;
        }
      }
    }
    // Only free if not already freed
    if (p1) tetris_free(p1);
    if (p2) tetris_free(p2);
  }

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
  return EXIT_SUCCESS;
}
