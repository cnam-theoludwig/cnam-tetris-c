#include "tetris_ui_1v1.h"

SDL_Texture* load_texture_from_file(const char* path, SDL_Renderer* renderer);

TetrisUIAction tetris_ui_1v1(struct Tetris* p1, struct Tetris* p2, SDL_Window** window_in, SDL_Renderer** renderer_in, bool ai_right_player) {
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  bool own_window = false;
  if (window_in && *window_in && renderer_in && *renderer_in) {
    window = *window_in;
    renderer = *renderer_in;
  } else {
    window = SDL_CreateWindow(
        "Tetris 1v1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        TETRIS_WINDOW_WIDTH * 2 + 100,
        TETRIS_WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) {
      fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
      return UI_ACTION_QUIT;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      SDL_DestroyWindow(window);
      fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
      return UI_ACTION_QUIT;
    }
    own_window = true;
    if (window_in) *window_in = window;
    if (renderer_in) *renderer_in = renderer;
  }

  SDL_AudioSpec wav_spec;
  Uint32 wav_length;
  Uint8* wav_buffer;
  SDL_AudioDeviceID audio_device = 0;
  if (SDL_LoadWAV("assets/music.wav", &wav_spec, &wav_buffer, &wav_length)) {
    audio_device = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    if (audio_device) {
      SDL_QueueAudio(audio_device, wav_buffer, wav_length);
      SDL_PauseAudioDevice(audio_device, 0);
    } else {
      SDL_FreeWAV(wav_buffer);
      wav_buffer = NULL;
    }
  }

  SDL_Texture* pause_button_texture = load_texture_from_file("assets/pause_icon.png", renderer);
  SDL_Rect pause_button_rect = {PAUSE_BUTTON_X, PAUSE_BUTTON_Y, PAUSE_BUTTON_SIZE, PAUSE_BUTTON_SIZE};

  tetris_add_tetromino(p1);
  tetris_add_tetromino(p2);

  bool running = true;
  bool paused = false;
  Uint32 last_drop_time_p1 = SDL_GetTicks();
  Uint32 last_drop_time_p2 = SDL_GetTicks();
  SDL_Event event;
  int offset_x1 = 50;
  int offset_x2 = TETRIS_WINDOW_WIDTH + 100;

  while (running) {
    if (p1->game_over || p2->game_over) {
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
      SDL_Rect overlay = {0, 0, TETRIS_WINDOW_WIDTH * 2 + 100, TETRIS_WINDOW_HEIGHT};
      SDL_RenderFillRect(renderer, &overlay);

      const char* msg = NULL;
      if (p1->game_over && p2->game_over) {
        msg = "Draw!";
      } else if (p1->game_over) {
        msg = "Player 2 Wins!";
      } else if (p2->game_over) {
        msg = "Player 1 Wins!";
      }

      TTF_Font* font = TTF_OpenFont("assets/font.ttf", 48);
      TTF_Font* btn_font = TTF_OpenFont("assets/font.ttf", 36);
      SDL_Color yellow = {255, 255, 0, 255};
      SDL_Color white = {255, 255, 255, 255};
      SDL_Color btn_bg = {40, 40, 40, 220};
      SDL_Color btn_border = {255, 255, 0, 255};

      const char* btn_txt = "Restart";
      SDL_Rect btn_rect;
      int btn_w = 240, btn_h = 60;
      int center_x = (TETRIS_WINDOW_WIDTH * 2 + 100) / 2;
      int center_y = (TETRIS_WINDOW_HEIGHT) / 2 + 80;
      btn_rect.w = btn_w;
      btn_rect.h = btn_h;
      btn_rect.x = center_x - btn_w / 2;
      btn_rect.y = center_y;
      int selected_btn = 0;

      if (font) {
        SDL_Surface* surf = TTF_RenderText_Solid(font, msg, yellow);
        if (surf) {
          SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
          if (tex) {
            int tw = surf->w, th = surf->h;
            SDL_Rect dst = {center_x - tw / 2, btn_rect.y - th - 50, tw, th};
            SDL_RenderCopy(renderer, tex, NULL, &dst);
            SDL_DestroyTexture(tex);
          }
          SDL_FreeSurface(surf);
        }
      }

      SDL_SetRenderDrawColor(renderer, btn_bg.r, btn_bg.g, btn_bg.b, btn_bg.a);
      SDL_RenderFillRect(renderer, &btn_rect);

      for (size_t j = 0; j < 3; ++j) {
        SDL_Rect border = {btn_rect.x + j, btn_rect.y + j, btn_rect.w - 2 * j, btn_rect.h - 2 * j};
        SDL_SetRenderDrawColor(renderer, btn_border.r, btn_border.g, btn_border.b, btn_border.a);
        SDL_RenderDrawRect(renderer, &border);
      }
      if (btn_font) {
        SDL_Surface* surf = TTF_RenderText_Solid(btn_font, btn_txt, white);
        if (surf) {
          SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
          if (tex) {
            int tw = surf->w, th = surf->h;
            SDL_Rect dst = {btn_rect.x + (btn_w - tw) / 2, btn_rect.y + (btn_h - th) / 2, tw, th};
            SDL_RenderCopy(renderer, tex, NULL, &dst);
            SDL_DestroyTexture(tex);
          }
          SDL_FreeSurface(surf);
        }
      }
      SDL_RenderPresent(renderer);

      SDL_Event e;
      bool wait = true;
      while (wait && SDL_WaitEvent(&e)) {
        if (e.type == SDL_QUIT) {
          wait = false;
          running = false;
        } else if (e.type == SDL_KEYDOWN) {
          if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {
            if (font) TTF_CloseFont(font);
            if (btn_font) TTF_CloseFont(btn_font);
            return UI_ACTION_RESTART;
          } else if (e.key.keysym.sym == SDLK_ESCAPE) {
            wait = false;
            running = false;
          }
        }
      }
      if (font) {
        TTF_CloseFont(font);
      }
      if (btn_font) {
        TTF_CloseFont(btn_font);
      }
      break;
    }

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
      if (!paused && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        Sint32 mx = event.button.x, my = event.button.y;
        if (mx >= pause_button_rect.x && mx <= pause_button_rect.x + pause_button_rect.w &&
            my >= pause_button_rect.y && my <= pause_button_rect.y + pause_button_rect.h) {
          paused = true;
        }
      }
      if (!paused && event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            tetris_last_tetromino_step_left(p1);
            break;
          case SDLK_RIGHT:
            tetris_last_tetromino_step_right(p1);
            break;
          case SDLK_DOWN:
            tetris_last_tetromino_step_down(p1);
            break;
          case SDLK_r:
            tetris_last_tetromino_step_rotate_right(p1);
            break;
          case SDLK_e:
            tetris_last_tetromino_step_rotate_left(p1);
            break;
          case SDLK_SPACE: {
            while (tetris_last_tetromino_step_down(p1)) {
            }
            tetris_1v1_handle_lines_and_attack(p1, p2);
            if (!tetris_add_tetromino(p1)) p1->game_over = true;
            break;
          }

          case SDLK_a:
            tetris_last_tetromino_step_left(p2);
            break;
          case SDLK_d:
            tetris_last_tetromino_step_right(p2);
            break;
          case SDLK_s:
            tetris_last_tetromino_step_down(p2);
            break;
          case SDLK_RCTRL:
            tetris_last_tetromino_step_rotate_right(p2);
            break;
          case SDLK_LCTRL:
            tetris_last_tetromino_step_rotate_left(p2);
            break;
          case SDLK_RETURN: {
            while (tetris_last_tetromino_step_down(p2)) {
            }
            tetris_1v1_handle_lines_and_attack(p2, p1);
            if (!tetris_add_tetromino(p2)) p2->game_over = true;
            break;
          }
          case SDLK_p:
          case SDLK_ESCAPE:
            paused = true;
            break;
        }
      } else if (paused && event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_p:
          case SDLK_ESCAPE:
            paused = false;
            break;
          case SDLK_UP:
            p1->selected_pause_option = (p1->selected_pause_option - 1 + PAUSE_MENU_OPTION_COUNT) % PAUSE_MENU_OPTION_COUNT;
            break;
          case SDLK_DOWN:
            p1->selected_pause_option = (p1->selected_pause_option + 1) % PAUSE_MENU_OPTION_COUNT;
            break;
          case SDLK_RETURN:
            switch (p1->selected_pause_option) {
              case PAUSE_MENU_RESUME:
                paused = false;
                break;
              case PAUSE_MENU_RESTART:
                if (audio_device) SDL_CloseAudioDevice(audio_device);
                if (wav_buffer) SDL_FreeWAV(wav_buffer);
                if (pause_button_texture) SDL_DestroyTexture(pause_button_texture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return UI_ACTION_RESTART;
              case PAUSE_MENU_MAIN_MENU:
                if (audio_device) SDL_CloseAudioDevice(audio_device);
                if (wav_buffer) SDL_FreeWAV(wav_buffer);
                if (pause_button_texture) SDL_DestroyTexture(pause_button_texture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                return UI_ACTION_CONTINUE;
            }
            break;
        }
      }
    }

    if (!paused) {
      Uint32 now = SDL_GetTicks();
      float lvl1 = (float)tetris_get_level(p1);
      float lvl2 = (float)tetris_get_level(p2);
      Uint32 delay1 = (Uint32)(0.6f * powf(0.85f, lvl1) * 1000);
      Uint32 delay2 = (Uint32)(0.6f * powf(0.85f, lvl2) * 1000);

      if (now - last_drop_time_p1 >= delay1) {
        if (!tetris_last_tetromino_step_down(p1)) {
          tetris_1v1_handle_lines_and_attack(p1, p2);
          if (!tetris_add_tetromino(p1)) p1->game_over = true;
        }
        last_drop_time_p1 = now;
      }
      if (now - last_drop_time_p2 >= delay2) {
        if (!tetris_last_tetromino_step_down(p2)) {
          tetris_1v1_handle_lines_and_attack(p2, p1);
          if (!tetris_add_tetromino(p2)) p2->game_over = true;
        }
        last_drop_time_p2 = now;
      }
    }

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_RenderSetViewport(renderer, &(SDL_Rect){offset_x1, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT});
    tetris_ui_render_grid(renderer, p1);
    tetris_ui_render_score(renderer, p1);
    tetris_ui_render_level(renderer, p1);
    tetris_ui_render_next_tetromino(renderer, p1);

    SDL_RenderSetViewport(renderer, &(SDL_Rect){offset_x2, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT});
    tetris_ui_render_grid(renderer, p2);
    tetris_ui_render_score(renderer, p2);
    tetris_ui_render_level(renderer, p2);
    tetris_ui_render_next_tetromino(renderer, p2);

    SDL_RenderSetViewport(renderer, NULL);
    if (!paused) {
      SDL_RenderCopy(renderer, pause_button_texture, NULL, &pause_button_rect);
    } else {
      SDL_RenderSetViewport(renderer, NULL);
      SDL_Rect pause_overlay = {0, 0, TETRIS_WINDOW_WIDTH * 2 + 100, TETRIS_WINDOW_HEIGHT};
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
      SDL_RenderFillRect(renderer, &pause_overlay);
      SDL_Rect menu_vp = {((TETRIS_WINDOW_WIDTH * 2 + 100) - TETRIS_WINDOW_WIDTH) / 2, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT};
      SDL_RenderSetViewport(renderer, &menu_vp);
      tetris_ui_render_pause_menu(renderer, p1);
      SDL_RenderSetViewport(renderer, NULL);
    }

    SDL_RenderPresent(renderer);
  }

  if (audio_device) {
    SDL_CloseAudioDevice(audio_device);
  }
  if (wav_buffer) {
    SDL_FreeWAV(wav_buffer);
  }
  if (pause_button_texture) {
    SDL_DestroyTexture(pause_button_texture);
  }
  if (own_window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    if (window_in) *window_in = NULL;
    if (renderer_in) *renderer_in = NULL;
  }
  return UI_ACTION_QUIT;
}
