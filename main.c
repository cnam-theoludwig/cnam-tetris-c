#include <time.h>

#include "tetris.h"

int main() {
  srand((unsigned)time(NULL));
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    SDL_Quit();
    return 1;
  }
  if (TTF_Init() == -1) {
    SDL_Quit();
    return 1;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  SDL_Window* menu_win = NULL;
  SDL_Renderer* menu_ren = NULL;
  GameMode mode = run_tetris_main_menu(&menu_win, &menu_ren);
  if (menu_ren) SDL_DestroyRenderer(menu_ren);
  if (menu_win) SDL_DestroyWindow(menu_win);

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
    while (true) {
      TetrisUIAction act = tetris_ui_1v1(p1, p2);
      if (act == UI_ACTION_RESTART) {
        tetris_free(p1);
        tetris_free(p2);
        p1 = tetris_init();
        p2 = tetris_init();
      } else if (act == UI_ACTION_QUIT) {
        break;
      }
    }
    tetris_free(p1);
    tetris_free(p2);
  }

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
  return EXIT_SUCCESS;
}
