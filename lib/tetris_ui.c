#include "./tetris_ui.h"

void tetris_ui_render_grid(SDL_Renderer* renderer, struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      SDL_Rect rect = {column * TETRIS_BLOCK_SIZE, row * TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE};
      switch (tetris->grid[row][column]->type) {
        case TETROMINO_LINE:
          SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
          break;
        case TETROMINO_SQUARE:
          SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
          break;
        case TETROMINO_T:
          SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
          break;
        case TETROMINO_L:
          SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
          break;
        case TETROMINO_J:
          SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
          break;
        case TETROMINO_Z:
          SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
          break;
        case TETROMINO_S:
          SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
          break;
        default:
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          break;
      }
      SDL_RenderFillRect(renderer, &rect);
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
}

int tetris_ui() {
  printf("Tetris game\n");
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return EXIT_FAILURE;
  }

  SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris, tetris_get_tetromino_random());

  bool running = true;
  SDL_Event event;
  Uint32 last_drop_time = SDL_GetTicks();

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_RIGHT:
            tetris_last_tetromino_step_right(tetris);
            break;
          case SDLK_LEFT:
            tetris_last_tetromino_step_left(tetris);
            break;
          case SDLK_r:
            tetris_last_tetromino_rotate_right(tetris);
            break;
          case  SDLK_l :
            tetris_last_tetromino_rotate_left(tetris);
            break;
        }
      }
    }

    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_drop_time >= 500) {
      if (!tetris_last_tetromino_step_down(tetris)) {
        tetris_add_tetromino(tetris, tetris_get_tetromino_random());
      }
      tetris_destroy_line(tetris);
      last_drop_time = current_time;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    tetris_ui_render_grid(renderer, tetris);

    SDL_RenderPresent(renderer);
    // SDL_Delay(1);
  }

  tetris_free(tetris);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
