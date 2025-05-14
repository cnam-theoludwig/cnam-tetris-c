#include "./tetris_ui.h"

void tetris_ui_render_grid(SDL_Renderer* renderer, struct Tetris* tetris) {
  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      SDL_Rect rect = {
          column * TETRIS_BLOCK_SIZE,
          row * TETRIS_BLOCK_SIZE,
          TETRIS_BLOCK_SIZE,
          TETRIS_BLOCK_SIZE};
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
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    return EXIT_FAILURE;
  }

  SDL_Window* window = SDL_CreateWindow(
      "Tetris",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      TETRIS_WINDOW_WIDTH,
      TETRIS_WINDOW_HEIGHT,
      SDL_WINDOW_SHOWN);
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

  SDL_AudioSpec wav_spec;
  Uint32 wav_length;
  Uint8* wav_buffer;
  if (SDL_LoadWAV("assets/music.wav", &wav_spec, &wav_buffer, &wav_length) ==
      NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
  if (device == 0) {
    SDL_FreeWAV(wav_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_QueueAudio(device, wav_buffer, wav_length);
  SDL_PauseAudioDevice(device, 0);

  struct Tetris* tetris = tetris_init();
  // tetris_add_tetromino(tetris, tetris_get_tetromino_random());
  for (size_t index_column = 0; index_column < GRID_WIDTH - 2; index_column += 1) {
    tetris->grid[GRID_HEIGHT - 1][index_column]->type = TETROMINO_SQUARE;
    tetris->grid[GRID_HEIGHT - 1][index_column]->occurence = 1;
    tetris->last_occurence += 1;

    tetris->grid[GRID_HEIGHT - 2][index_column]->type = TETROMINO_SQUARE;
    tetris->grid[GRID_HEIGHT - 2][index_column]->occurence = 1;
    tetris->last_occurence += 1;
  }

  tetris_add_tetromino(tetris, TETROMINO_SQUARE);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);
  tetris_last_tetromino_step_right(tetris);

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
            tetris_last_tetromino_step_rotate_right(tetris);
            break;
          case SDLK_l:
            tetris_last_tetromino_step_rotate_left(tetris);
            break;
          case SDLK_DOWN:
            tetris_last_tetromino_step_down(tetris);
            break;
          case SDLK_SPACE:
            while (tetris_last_tetromino_step_down(tetris)) {
            }
            break;
        }
      }
    }

    Uint32 current_time = SDL_GetTicks();

    float level = (float)tetris_get_level(tetris);
    float drop_delay_sec = powf((0.8f - ((level - 1) * 0.007f)), level - 1);
    Uint32 drop_delay_ms = (Uint32)(drop_delay_sec * 1000.0f);

    if (current_time - last_drop_time >= drop_delay_ms) {
      bool is_posed = !tetris_last_tetromino_step_down(tetris);

      if (is_posed) {
        tetris_destroy_line(tetris);
      }

      bool is_game_over = is_posed && !tetris_add_tetromino(tetris, tetris_get_tetromino_random());
      if (is_game_over) {
        tetris_free(tetris);
        tetris = tetris_init();
        tetris_add_tetromino(tetris, tetris_get_tetromino_random());
      }

      last_drop_time = current_time;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    tetris_ui_render_grid(renderer, tetris);
    SDL_RenderPresent(renderer);
  }

  tetris_free(tetris);
  SDL_CloseAudioDevice(device);
  SDL_FreeWAV(wav_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
