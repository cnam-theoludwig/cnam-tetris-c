#include "tetris.h"

int main() {
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if (TTF_Init() == -1) {
    fprintf(stderr, "Failed to initialize TTF: %s\n", TTF_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    fprintf(stderr, "Failed to initialize SDL_image: %s\n", IMG_GetError());
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  struct Tetris* tetris = tetris_init();
  if (!tetris) {
    fprintf(stderr, "Failed to initialize Tetris struct.\n");
    return EXIT_FAILURE;
  }

  bool game_running = true;
  while (game_running) {
    TetrisUIAction action = tetris_ui(tetris);

    switch (action) {
      case UI_ACTION_RESTART:
        tetris_free(tetris);
        tetris = tetris_init();
        if (!tetris) {
          fprintf(stderr, "Failed to re-initialize Tetris struct after restart.\n");
          game_running = false;
        }
        break;
      case UI_ACTION_QUIT:
        game_running = false;
        break;
      case UI_ACTION_CONTINUE:
        break;
    }
  }

  tetris_free(tetris);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
