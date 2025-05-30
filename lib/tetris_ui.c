#include "tetris_ui.h"

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

SDL_Texture* load_texture_from_file(const char* path, SDL_Renderer* renderer) {
  SDL_Texture* new_texture = IMG_LoadTexture(renderer, path);
  if (new_texture == NULL) {
    fprintf(stderr, "Failed to load texture %s: %s\n", path, IMG_GetError());
  }
  return new_texture;
}

void tetris_ui_render_pause_menu(SDL_Renderer* renderer, struct Tetris* tetris) {
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
  SDL_Rect overlay_rect = {0, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT};
  SDL_RenderFillRect(renderer, &overlay_rect);

  TTF_Font* title_font = TTF_OpenFont("assets/font.ttf", 48);
  TTF_Font* item_font = TTF_OpenFont("assets/font.ttf", 36);
  if (!title_font || !item_font) {
    fprintf(stderr, "Failed to load font for pause menu: %s\n", TTF_GetError());
    if (title_font) TTF_CloseFont(title_font);
    if (item_font) TTF_CloseFont(item_font);
    return;
  }

  SDL_Color title_color = {255, 255, 255, 255};
  SDL_Color item_color = {200, 200, 200, 255};
  SDL_Color selected_item_color = {255, 255, 0, 255};

  SDL_Surface* surface = TTF_RenderText_Solid(title_font, "PAUSED", title_color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect dest_rect = {(TETRIS_WINDOW_WIDTH - surface->w) / 2, TETRIS_WINDOW_HEIGHT / 4 - surface->h / 2, surface->w, surface->h};
  SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  const char* menu_item_texts[] = {"Resume", "Restart", "Quit"};
  int icon_size = 48;
  int text_height_approx = 40;
  int item_spacing = 20;
  int total_item_height = icon_size + text_height_approx + item_spacing;

  int base_y = TETRIS_WINDOW_HEIGHT / 2 - (PAUSE_MENU_OPTION_COUNT * total_item_height - item_spacing) / 2;

  for (int i = 0; i < PAUSE_MENU_OPTION_COUNT; ++i) {
    SDL_Rect icon_placeholder_rect = {(TETRIS_WINDOW_WIDTH - icon_size) / 2, base_y + i * total_item_height, icon_size, icon_size};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderDrawRect(renderer, &icon_placeholder_rect);

    SDL_Color current_color = (i == tetris->selected_pause_option) ? selected_item_color : item_color;
    surface = TTF_RenderText_Solid(item_font, menu_item_texts[i], current_color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    dest_rect.x = (TETRIS_WINDOW_WIDTH - surface->w) / 2;
    dest_rect.y = base_y + i * total_item_height + icon_size + 5;
    dest_rect.w = surface->w;
    dest_rect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
  }

  TTF_CloseFont(title_font);
  TTF_CloseFont(item_font);
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

TetrisUIAction tetris_ui(struct Tetris* tetris) {
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

  if (!tetris_add_tetromino(tetris)) {
    tetris->game_over = true;
  }

  bool running = true;
  TetrisUIAction action_result = UI_ACTION_CONTINUE;
  Uint32 last_drop_time = SDL_GetTicks();

  SDL_Texture* pause_button_texture = load_texture_from_file("assets/pause_icon.png", renderer);

  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        action_result = UI_ACTION_QUIT;
        running = false;
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (tetris->game_over) {
          int mouse_x, mouse_y;
          SDL_GetMouseState(&mouse_x, &mouse_y);
          TTF_Font* button_font = TTF_OpenFont("assets/font.ttf", 36);
          if (button_font) {
            SDL_Surface* button_surface = TTF_RenderText_Solid(button_font, "Restart", (SDL_Color){200, 200, 200, 255});
            if (button_surface) {
              SDL_Rect button_rect = {
                  (TETRIS_WINDOW_WIDTH - button_surface->w) / 2,
                  TETRIS_WINDOW_HEIGHT * 2 / 3 - button_surface->h / 2,
                  button_surface->w,
                  button_surface->h};
              if (mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w &&
                  mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h) {
                action_result = UI_ACTION_RESTART;
                running = false;
              }
              SDL_FreeSurface(button_surface);
            }
            TTF_CloseFont(button_font);
          }
        } else if (!tetris->paused && !tetris->game_over) {
          int mouse_x, mouse_y;
          SDL_GetMouseState(&mouse_x, &mouse_y);
          SDL_Rect pause_button_rect = {PAUSE_BUTTON_X, PAUSE_BUTTON_Y, PAUSE_BUTTON_SIZE, PAUSE_BUTTON_SIZE};
          if (mouse_x >= pause_button_rect.x && mouse_x <= pause_button_rect.x + pause_button_rect.w &&
              mouse_y >= pause_button_rect.y && mouse_y <= pause_button_rect.y + pause_button_rect.h) {
            tetris->paused = true;
            tetris->selected_pause_option = PAUSE_MENU_RESUME;
          }
        }
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_RIGHT:
            if (!tetris->paused && !tetris->game_over) tetris_last_tetromino_step_right(tetris);
            break;
          case SDLK_LEFT:
            if (!tetris->paused && !tetris->game_over) tetris_last_tetromino_step_left(tetris);
            break;
          case SDLK_ESCAPE:
          case SDLK_p:
            if (!tetris->game_over) {
              tetris->paused = !tetris->paused;
              if (tetris->paused) {
                tetris->selected_pause_option = PAUSE_MENU_RESUME;
              }
            }
            break;
          case SDLK_r:
            if (!tetris->paused && !tetris->game_over) tetris_last_tetromino_step_rotate_right(tetris);
            break;
          case SDLK_e:
            if (!tetris->paused && !tetris->game_over) tetris_last_tetromino_step_rotate_left(tetris);
            break;
          case SDLK_DOWN:
            if (tetris->paused && !tetris->game_over) {
              tetris->selected_pause_option = (tetris->selected_pause_option + 1) % PAUSE_MENU_OPTION_COUNT;
            } else if (!tetris->paused && !tetris->game_over) {
              tetris_last_tetromino_step_down(tetris);
              last_drop_time = SDL_GetTicks();
            }
            break;
          case SDLK_UP:
            if (tetris->paused && !tetris->game_over) {
              tetris->selected_pause_option = (tetris->selected_pause_option - 1 + PAUSE_MENU_OPTION_COUNT) % PAUSE_MENU_OPTION_COUNT;
            }
            break;
          case SDLK_RETURN:
            if (tetris->paused && !tetris->game_over) {
              switch (tetris->selected_pause_option) {
                case PAUSE_MENU_RESUME:
                  tetris->paused = false;
                  break;
                case PAUSE_MENU_RESTART:
                  action_result = UI_ACTION_RESTART;
                  running = false;
                  break;
                case PAUSE_MENU_QUIT:
                  action_result = UI_ACTION_QUIT;
                  running = false;
                  break;
                default:
                  break;
              }
            }
            break;
          case SDLK_SPACE:
            if (!tetris->paused && !tetris->game_over) {
              while (tetris_last_tetromino_step_down(tetris)) {
              }
              tetris_destroy_line(tetris);
              if (!tetris_add_tetromino(tetris)) {
                tetris->game_over = true;
              }
              last_drop_time = SDL_GetTicks();
            }
            break;
        }
      }
    }

    Uint32 current_time = SDL_GetTicks();
    float level_float = (float)tetris_get_level(tetris);
    float drop_delay_sec = 0.6f * powf(0.85f, level_float);
    if (drop_delay_sec < 0.05f) {
      drop_delay_sec = 0.05f;
    }
    Uint32 drop_delay_ms = (Uint32)(drop_delay_sec * 1000.0f);

    if (!tetris->paused && !tetris->game_over && current_time - last_drop_time >= drop_delay_ms) {
      bool piece_landed = !tetris_last_tetromino_step_down(tetris);
      if (piece_landed) {
        tetris_destroy_line(tetris);
        if (!tetris_add_tetromino(tetris)) {
          tetris->game_over = true;
        }
      }
      last_drop_time = current_time;
    }

    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_A);
    SDL_RenderClear(renderer);

    if (!tetris->paused && !tetris->game_over) {
      SDL_Rect pause_button_rect = {PAUSE_BUTTON_X, PAUSE_BUTTON_Y, PAUSE_BUTTON_SIZE, PAUSE_BUTTON_SIZE};
      if (pause_button_texture) {
        SDL_RenderCopy(renderer, pause_button_texture, NULL, &pause_button_rect);
      } else {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &pause_button_rect);
      }
    }

    tetris_ui_render_grid(renderer, tetris);
    tetris_ui_render_score(renderer, tetris);
    tetris_ui_render_level(renderer, tetris);
    tetris_ui_render_next_tetromino(renderer, tetris);

    if (tetris->game_over) {
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
      SDL_Rect overlay_rect = {0, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT};
      SDL_RenderFillRect(renderer, &overlay_rect);

      TTF_Font* title_font = TTF_OpenFont("assets/font.ttf", 48);
      TTF_Font* button_font = TTF_OpenFont("assets/font.ttf", 36);
      if (title_font && button_font) {
        SDL_Color text_color = {255, 0, 0, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(title_font, "GAME OVER", text_color);
        if (surface) {
          SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
          if (texture) {
            SDL_Rect dest_rect = {(TETRIS_WINDOW_WIDTH - surface->w) / 2, TETRIS_WINDOW_HEIGHT / 3 - surface->h / 2, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
            SDL_DestroyTexture(texture);
          }
          SDL_FreeSurface(surface);
        }

        SDL_Color button_color = {200, 200, 200, 255};
        SDL_Color button_hover_color = {255, 255, 0, 255};
        const char* button_text = "Restart";
        SDL_Surface* button_surface = TTF_RenderText_Solid(button_font, button_text, button_color);
        if (button_surface) {
          SDL_Texture* button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
          if (button_texture) {
            SDL_Rect button_rect = {
                (TETRIS_WINDOW_WIDTH - button_surface->w) / 2,
                TETRIS_WINDOW_HEIGHT * 2 / 3 - button_surface->h / 2,
                button_surface->w,
                button_surface->h};

            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            bool is_hover = (mouse_x >= button_rect.x && mouse_x <= button_rect.x + button_rect.w && mouse_y >= button_rect.y && mouse_y <= button_rect.y + button_rect.h);

            if (is_hover) {
              SDL_DestroyTexture(button_texture);
              button_surface = TTF_RenderText_Solid(button_font, button_text, button_hover_color);
              button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
            }

            SDL_RenderCopy(renderer, button_texture, NULL, &button_rect);
            SDL_DestroyTexture(button_texture);
          }
          SDL_FreeSurface(button_surface);
        }
        TTF_CloseFont(title_font);
        TTF_CloseFont(button_font);
      }
    } else if (tetris->paused) {
      tetris_ui_render_pause_menu(renderer, tetris);
    }

    SDL_RenderPresent(renderer);
  }

  SDL_CloseAudioDevice(device);
  SDL_FreeWAV(wav_buffer);
  if (pause_button_texture) {
    SDL_DestroyTexture(pause_button_texture);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  return action_result;
}
