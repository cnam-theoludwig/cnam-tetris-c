#include "./tetris_ui.h"

void tetris_ui_render_grid(SDL_Renderer* renderer, struct Tetris* tetris) {
  SDL_Rect border_rect = {
      GRID_OFFSET_X - GRID_BORDER_SIZE,
      GRID_OFFSET_Y - GRID_BORDER_SIZE,
      (GRID_WIDTH * GRID_BLOCK_SIZE) + (GRID_BORDER_SIZE * 2),
      (GRID_HEIGHT * GRID_BLOCK_SIZE) + (GRID_BORDER_SIZE * 2)};

  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderFillRect(renderer, &border_rect);

  for (size_t row = 0; row < GRID_HEIGHT; row++) {
    for (size_t column = 0; column < GRID_WIDTH; column++) {
      SDL_Rect rect = {
          GRID_OFFSET_X + (column * GRID_BLOCK_SIZE),
          GRID_OFFSET_Y + (row * GRID_BLOCK_SIZE),
          GRID_BLOCK_SIZE,
          GRID_BLOCK_SIZE};

      SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
      SDL_RenderFillRect(renderer, &rect);

      switch (tetris->grid[row][column]->type) {
        case TETROMINO_LINE:
          SDL_SetRenderDrawColor(renderer, 0, 180, 180, 255);
          break;
        case TETROMINO_SQUARE:
          SDL_SetRenderDrawColor(renderer, 180, 180, 0, 255);
          break;
        case TETROMINO_T:
          SDL_SetRenderDrawColor(renderer, 100, 0, 100, 255);
          break;
        case TETROMINO_L:
          SDL_SetRenderDrawColor(renderer, 200, 120, 0, 255);
          break;
        case TETROMINO_J:
          SDL_SetRenderDrawColor(renderer, 0, 0, 180, 255);
          break;
        case TETROMINO_Z:
          SDL_SetRenderDrawColor(renderer, 180, 0, 0, 255);
          break;
        case TETROMINO_S:
          SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
          break;
        default:
          SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
          break;
      }
      SDL_RenderFillRect(renderer, &rect);
      SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
}

void tetris_ui_render_score(SDL_Renderer* renderer, struct Tetris* tetris) {
  TTF_Font* font = TTF_OpenFont("assets/font.ttf", 30);
  if (!font) {
    return;
  }

  char score_text[32];
  snprintf(score_text, sizeof(score_text), "SCORE: %zu", tetris->score);

  SDL_Color text_color = {255, 255, 255, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(font, score_text, text_color);
  if (!surface) {
    TTF_CloseFont(font);
    return;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return;
  }

  SDL_Rect dest = {SCORE_OFFSET_X, SCORE_OFFSET_Y, surface->w, surface->h};
  SDL_RenderCopy(renderer, texture, NULL, &dest);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

void tetris_ui_render_level(SDL_Renderer* renderer, struct Tetris* tetris) {
  TTF_Font* font = TTF_OpenFont("assets/font.ttf", 30);
  if (!font) {
    return;
  }

  char level_text[32];
  snprintf(level_text, sizeof(level_text), "LEVEL: %zu", tetris_get_level(tetris));

  SDL_Color text_color = {255, 255, 255, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(font, level_text, text_color);
  if (!surface) {
    TTF_CloseFont(font);
    return;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return;
  }

  SDL_Rect dest = {LEVEL_OFFSET_X, LEVEL_OFFSET_Y, surface->w, surface->h};
  SDL_RenderCopy(renderer, texture, NULL, &dest);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

static void tetris_ui_render_next_tetromino_block(SDL_Renderer* renderer, int x, int y, byte_t type) {
  SDL_Rect block_rect = {x, y, NEXT_PIECE_BLOCK_SIZE, NEXT_PIECE_BLOCK_SIZE};

  switch (type) {
    case TETROMINO_LINE:
      SDL_SetRenderDrawColor(renderer, 0, 180, 180, 255);
      break;
    case TETROMINO_SQUARE:
      SDL_SetRenderDrawColor(renderer, 180, 180, 0, 255);
      break;
    case TETROMINO_T:
      SDL_SetRenderDrawColor(renderer, 100, 0, 100, 255);
      break;
    case TETROMINO_L:
      SDL_SetRenderDrawColor(renderer, 200, 120, 0, 255);
      break;
    case TETROMINO_J:
      SDL_SetRenderDrawColor(renderer, 0, 0, 180, 255);
      break;
    case TETROMINO_Z:
      SDL_SetRenderDrawColor(renderer, 180, 0, 0, 255);
      break;
    case TETROMINO_S:
      SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
      break;
    default:
      return;
  }
  SDL_RenderFillRect(renderer, &block_rect);
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderDrawRect(renderer, &block_rect);
}

void tetris_ui_render_next_tetromino(SDL_Renderer* renderer, struct Tetris* tetris) {
  TTF_Font* font = TTF_OpenFont("assets/font.ttf", 30);
  if (!font) {
    fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
    return;
  }

  SDL_Color text_color = {255, 255, 255, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(font, "NEXT:", text_color);
  if (!surface) {
    fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
    TTF_CloseFont(font);
    return;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return;
  }

  SDL_Rect dest_label = {NEXT_LABEL_OFFSET_X, NEXT_LABEL_OFFSET_Y, surface->w, surface->h};
  SDL_RenderCopy(renderer, texture, NULL, &dest_label);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);

  byte_t next_type = tetris->next_tetromino_type;
  int base_x = NEXT_PIECE_AREA_OFFSET_X;
  int base_y = NEXT_PIECE_AREA_OFFSET_Y;

  switch (next_type) {
    case TETROMINO_LINE:
      tetris_ui_render_next_tetromino_block(renderer, base_x + 0 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 3 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      break;
    case TETROMINO_SQUARE:
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      break;
    case TETROMINO_T:
      tetris_ui_render_next_tetromino_block(renderer, base_x + 0 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      break;
    case TETROMINO_L:
      tetris_ui_render_next_tetromino_block(renderer, base_x + 0 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      break;
    case TETROMINO_J:
      tetris_ui_render_next_tetromino_block(renderer, base_x + 0 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 0 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      break;
    case TETROMINO_Z:
      tetris_ui_render_next_tetromino_block(renderer, base_x + 0 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      break;
    case TETROMINO_S:
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 2 * NEXT_PIECE_BLOCK_SIZE, base_y + 0 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 0 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      tetris_ui_render_next_tetromino_block(renderer, base_x + 1 * NEXT_PIECE_BLOCK_SIZE, base_y + 1 * NEXT_PIECE_BLOCK_SIZE, next_type);
      break;
  }
}

int tetris_ui() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    return EXIT_FAILURE;
  }

  if (TTF_Init() != 0) {
    SDL_Quit();
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
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_AudioSpec wav_spec;
  Uint32 wav_length;
  Uint8* wav_buffer;
  if (SDL_LoadWAV("assets/music.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
  if (device == 0) {
    SDL_FreeWAV(wav_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_QueueAudio(device, wav_buffer, wav_length);
  SDL_PauseAudioDevice(device, 0);

  struct Tetris* tetris = tetris_init();
  tetris_add_tetromino(tetris);

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
    float drop_delay_sec = 0.6f * powf(0.85f, level);
    if (drop_delay_sec < 0.05f) {
      drop_delay_sec = 0.05f;
    }
    Uint32 drop_delay_ms = (Uint32)(drop_delay_sec * 1000.0f);

    if (current_time - last_drop_time >= drop_delay_ms) {
      bool is_posed = !tetris_last_tetromino_step_down(tetris);

      if (is_posed) {
        tetris_destroy_line(tetris);
      }

      bool is_game_over = is_posed && !tetris_add_tetromino(tetris);
      if (is_game_over) {
        tetris_free(tetris);
        tetris = tetris_init();
        tetris_add_tetromino(tetris);
      }

      last_drop_time = current_time;
    }

    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_A);
    SDL_RenderClear(renderer);

    tetris_ui_render_grid(renderer, tetris);
    tetris_ui_render_score(renderer, tetris);
    tetris_ui_render_level(renderer, tetris);
    tetris_ui_render_next_tetromino(renderer, tetris);

    SDL_RenderPresent(renderer);
  }

  tetris_free(tetris);
  SDL_CloseAudioDevice(device);
  SDL_FreeWAV(wav_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  return EXIT_SUCCESS;
}
