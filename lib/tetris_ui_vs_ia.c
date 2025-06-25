#include "tetris_ui_vs_ia.h"

#define IA_ACTION_DELAY_MS 10

SDL_Texture* load_texture_from_file(const char* path, SDL_Renderer* renderer);

static int count_holes(struct Tetris* t) {
  int holes = 0;
  for (int col = 0; col < GRID_WIDTH; ++col) {
    bool block_seen = false;
    for (int row = 0; row < GRID_HEIGHT; ++row) {
      byte_t type = t->grid[row][col]->type;
      if (type != TETROMINO_EMPTY && type != TETROMINO_GARBAGE) {
        block_seen = true;
      } else if (block_seen && type == TETROMINO_EMPTY) {
        holes++;
      }
    }
  }
  return holes;
}

static int aggregate_height(struct Tetris* t) {
  int total = 0;
  for (int col = 0; col < GRID_WIDTH; ++col) {
    int col_height = 0;
    for (int row = 0; row < GRID_HEIGHT; ++row) {
      byte_t type = t->grid[row][col]->type;
      if (type != TETROMINO_EMPTY && type != TETROMINO_GARBAGE) {
        col_height = GRID_HEIGHT - row;
        break;
      }
    }
    total += col_height;
  }
  return total;
}

static int bumpiness(struct Tetris* t) {
  int bump = 0;
  int prev_h = 0;
  for (int col = 0; col < GRID_WIDTH; ++col) {
    int h = 0;
    for (int row = 0; row < GRID_HEIGHT; ++row) {
      byte_t type = t->grid[row][col]->type;
      if (type != TETROMINO_EMPTY && type != TETROMINO_GARBAGE) {
        h = GRID_HEIGHT - row;
        break;
      }
    }
    if (col > 0) bump += abs(prev_h - h);
    prev_h = h;
  }
  return bump;
}

static void ia_compute_best_move(struct Tetris* ia, int* best_rot, int* best_col) {
  int best_gain = -1;
  double best_score = 1e9;
  for (int rot = 0; rot < 4; ++rot) {
    for (int col = 0; col < GRID_WIDTH; ++col) {
      struct Tetris* copy = tetris_copy(ia);
      for (int r = 0; r < rot; ++r)
        tetris_last_tetromino_step_rotate_right(copy);
      int dx = col - (int)copy->last_pivot_x;
      while (dx > 0) {
        tetris_last_tetromino_step_right(copy);
        dx--;
      }
      while (dx < 0) {
        tetris_last_tetromino_step_left(copy);
        dx++;
      }
      while (tetris_last_tetromino_step_down(copy));
      size_t lines = tetris_destroy_line(copy);
      int holes = count_holes(copy);
      int agg = aggregate_height(copy);
      int bump = bumpiness(copy);
      double score = agg * 0.5 + holes * 5.0 + bump * 0.2;
      if ((int)lines > best_gain || ((int)lines == best_gain && score < best_score)) {
        best_gain = (int)lines;
        best_score = score;
        *best_rot = rot;
        *best_col = col;
      }
      tetris_free(copy);
    }
  }
}

TetrisUIAction tetris_ui_vs_ai(struct Tetris* human, struct Tetris* ia, SDL_Window** window_in, SDL_Renderer** renderer_in) {
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  bool own_window = false;
  if (window_in && *window_in && renderer_in && *renderer_in) {
    window = *window_in;
    renderer = *renderer_in;
  } else {
    window = SDL_CreateWindow("Tetris vs IA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TETRIS_WINDOW_WIDTH * 2 + 100, TETRIS_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return UI_ACTION_QUIT;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      SDL_DestroyWindow(window);
      return UI_ACTION_QUIT;
    }
    own_window = true;
    *window_in = window;
    *renderer_in = renderer;
  }

  SDL_Texture* pause_button_texture = load_texture_from_file("assets/pause_icon.png", renderer);
  SDL_Rect pause_button_rect = {PAUSE_BUTTON_X, PAUSE_BUTTON_Y, PAUSE_BUTTON_SIZE, PAUSE_BUTTON_SIZE};

  tetris_add_tetromino(human);
  tetris_add_tetromino(ia);

  bool running = true;
  bool paused = false;
  Uint32 last_drop_h = SDL_GetTicks();
  Uint32 last_drop_ai = SDL_GetTicks();
  Uint32 last_ai_action = SDL_GetTicks();
  SDL_Event event;
  int offset_h = 50;
  int offset_ai = TETRIS_WINDOW_WIDTH + 100;

  int ia_target_rot = 0, ia_target_col = (int)ia->last_pivot_x;
  int ia_current_rot = 0;
  bool ia_new_piece = true;

  while (running) {
    if (human->game_over || ia->game_over) {
      return UI_ACTION_RESTART;
    }
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
      if (!paused) {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
          int mx = event.button.x, my = event.button.y;
          if (mx >= pause_button_rect.x && mx <= pause_button_rect.x + pause_button_rect.w &&
              my >= pause_button_rect.y && my <= pause_button_rect.y + pause_button_rect.h) {
            paused = true;
          }
        } else if (event.type == SDL_KEYDOWN) {
          switch (event.key.keysym.sym) {
            case SDLK_LEFT:
              tetris_last_tetromino_step_left(human);
              break;
            case SDLK_RIGHT:
              tetris_last_tetromino_step_right(human);
              break;
            case SDLK_DOWN:
              tetris_last_tetromino_step_down(human);
              break;
            case SDLK_r:
              tetris_last_tetromino_step_rotate_right(human);
              break;
            case SDLK_e:
              tetris_last_tetromino_step_rotate_left(human);
              break;
            case SDLK_SPACE:
              while (tetris_last_tetromino_step_down(human));
              tetris_1v1_handle_lines_and_attack(human, ia);
              if (!tetris_add_tetromino(human)) human->game_over = true;
              ia_new_piece = true;
              break;
            case SDLK_p:
            case SDLK_ESCAPE:
              paused = true;
              break;
          }
        }
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_p:
          case SDLK_ESCAPE:
            paused = false;
            break;
          case SDLK_UP:
            human->selected_pause_option = (human->selected_pause_option - 1 + PAUSE_MENU_OPTION_COUNT) % PAUSE_MENU_OPTION_COUNT;
            break;
          case SDLK_DOWN:
            human->selected_pause_option = (human->selected_pause_option + 1) % PAUSE_MENU_OPTION_COUNT;
            break;
          case SDLK_RETURN:
            switch (human->selected_pause_option) {
              case PAUSE_MENU_RESUME:
                paused = false;
                break;
              case PAUSE_MENU_RESTART:
                return UI_ACTION_RESTART;
              case PAUSE_MENU_MAIN_MENU:
                return UI_ACTION_CONTINUE;
            }
            break;
        }
      }
    }

    Uint32 now = SDL_GetTicks();
    if (!paused) {
      float lvl_h = (float)tetris_get_level(human);
      Uint32 delay_h = (Uint32)(0.6f * powf(0.85f, lvl_h) * 1000);
      if (now - last_drop_h >= delay_h) {
        if (!tetris_last_tetromino_step_down(human)) {
          tetris_1v1_handle_lines_and_attack(human, ia);
          if (!tetris_add_tetromino(human)) human->game_over = true;
          ia_new_piece = true;
        }
        last_drop_h = now;
      }
      float lvl_ai = (float)tetris_get_level(ia);
      Uint32 delay_ai = (Uint32)(0.6f * powf(0.85f, lvl_ai) * 1000);
      if (now - last_drop_ai >= delay_ai) {
        if (!tetris_last_tetromino_step_down(ia)) {
          tetris_1v1_handle_lines_and_attack(ia, human);
          if (!tetris_add_tetromino(ia)) ia->game_over = true;
          ia_new_piece = true;
        }
        last_drop_ai = now;
      }
      if (ia_new_piece) {
        ia_compute_best_move(ia, &ia_target_rot, &ia_target_col);
        ia_current_rot = 0;
        ia_new_piece = false;
      }
      if (now - last_ai_action >= IA_ACTION_DELAY_MS) {
        if (ia_current_rot < ia_target_rot) {
          tetris_last_tetromino_step_rotate_right(ia);
          ia_current_rot++;
        } else if ((int)ia->last_pivot_x < ia_target_col) {
          tetris_last_tetromino_step_right(ia);
        } else if ((int)ia->last_pivot_x > ia_target_col) {
          tetris_last_tetromino_step_left(ia);
        } else {
          while (tetris_last_tetromino_step_down(ia));
          tetris_1v1_handle_lines_and_attack(ia, human);
          if (!tetris_add_tetromino(ia)) ia->game_over = true;
          ia_new_piece = true;
        }
        last_ai_action = now;
      }
    }

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_RenderSetViewport(renderer, (SDL_Rect[]){{offset_h, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT}});
    tetris_ui_render_grid(renderer, human);
    tetris_ui_render_score(renderer, human);
    tetris_ui_render_level(renderer, human);
    tetris_ui_render_next_tetromino(renderer, human);

    SDL_RenderSetViewport(renderer, (SDL_Rect[]){{offset_ai, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT}});
    tetris_ui_render_grid(renderer, ia);
    tetris_ui_render_score(renderer, ia);
    tetris_ui_render_level(renderer, ia);
    tetris_ui_render_next_tetromino(renderer, ia);

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
      tetris_ui_render_pause_menu(renderer, human);
      SDL_RenderSetViewport(renderer, NULL);
    }
    SDL_RenderPresent(renderer);
  }

  if (pause_button_texture) SDL_DestroyTexture(pause_button_texture);
  if (own_window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    *window_in = NULL;
    *renderer_in = NULL;
  }
  return UI_ACTION_QUIT;
}
