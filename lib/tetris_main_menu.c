#include "tetris_main_menu.h"

#define WINDOW_W 800
#define WINDOW_H 600
#define BUTTON_W 200
#define BUTTON_H 80

static SDL_Texture* renderText(SDL_Renderer* rend, TTF_Font* font, const char* text) {
  SDL_Color white = {255, 255, 255, 255};
  SDL_Surface* surf = TTF_RenderText_Solid(font, text, white);
  SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
  SDL_FreeSurface(surf);
  return tex;
}

GameMode run_tetris_main_menu(SDL_Window** window, SDL_Renderer** renderer) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return MODE_NONE;
  }
  if (TTF_Init() == -1) {
    SDL_Quit();
    return MODE_NONE;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    TTF_Quit();
    SDL_Quit();
    return MODE_NONE;
  }

  *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
  if (!*window) {
    return MODE_NONE;
  }
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  if (!*renderer) {
    SDL_DestroyWindow(*window);
    return MODE_NONE;
  }

  TTF_Font* title_font = TTF_OpenFont("assets/font.ttf", 72);
  TTF_Font* font = TTF_OpenFont("assets/font.ttf", 36);

#define BUTTON_COUNT 4
  const int spacing = 30;
  int total_height = BUTTON_COUNT * BUTTON_H + (BUTTON_COUNT - 1) * spacing;
  int start_y = (WINDOW_H - total_height) / 2 + 60;

  SDL_Rect btn_rects[BUTTON_COUNT];
  btn_rects[0] = (SDL_Rect){(WINDOW_W - BUTTON_W) / 2, start_y, BUTTON_W, BUTTON_H};
  btn_rects[1] = (SDL_Rect){(WINDOW_W - BUTTON_W) / 2, start_y + BUTTON_H + spacing, BUTTON_W, BUTTON_H};
  btn_rects[2] = (SDL_Rect){(WINDOW_W - BUTTON_W) / 2, start_y + 2.5 * BUTTON_H + spacing, BUTTON_W, BUTTON_H};
  btn_rects[3] = (SDL_Rect){(WINDOW_W - BUTTON_W) / 2, start_y + 3 * (BUTTON_H + spacing), BUTTON_W, BUTTON_H};

  SDL_Texture* txtTitle = renderText(*renderer, title_font, "TETRIS");
  SDL_Texture* btn_textures[BUTTON_COUNT];
  btn_textures[0] = renderText(*renderer, font, "Solo");
  btn_textures[1] = renderText(*renderer, font, "1v1");
  btn_textures[2] = renderText(*renderer, font, "Versus IA");
  btn_textures[3] = renderText(*renderer, font, "Quit");

  GameMode mode = MODE_NONE;
  GameMode selected = MODE_SOLO;
  SDL_Event ev;
  while (mode == MODE_NONE && SDL_WaitEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
      mode = MODE_EXIT;
      break;
    }
    if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
      int x = ev.button.x, y = ev.button.y;
      for (int btn = 0; btn < BUTTON_COUNT; ++btn) {
        SDL_Rect* r = &btn_rects[btn];
        if (x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h) {
          if (btn == 0) {
            mode = MODE_SOLO;
          } else if (btn == 1) {
            mode = MODE_1V1;
          } else if (btn == 2) {
            mode = MODE_AI;
          } else if (btn == 3) {
            mode = MODE_EXIT;
          }

          selected = mode;
        }
      }
    }
    if (ev.type == SDL_KEYDOWN) {
      static const GameMode menu_modes[BUTTON_COUNT] = {MODE_SOLO, MODE_1V1, MODE_AI, MODE_EXIT};
      size_t index = 0;
      for (size_t i = 0; i < BUTTON_COUNT; ++i) {
        if (menu_modes[i] == selected) {
          index = i;
          break;
        }
      }
      if (ev.key.keysym.sym == SDLK_UP) {
        index = (index + BUTTON_COUNT - 1) % BUTTON_COUNT;
        selected = menu_modes[index];
      } else if (ev.key.keysym.sym == SDLK_DOWN) {
        index = (index + 1) % BUTTON_COUNT;
        selected = menu_modes[index];
      } else if (ev.key.keysym.sym == SDLK_RETURN || ev.key.keysym.sym == SDLK_KP_ENTER || ev.key.keysym.sym == SDLK_SPACE) {
        mode = selected;
      }
    }
    SDL_SetRenderDrawColor(*renderer, 26, 26, 26, 255);
    SDL_RenderClear(*renderer);

    int title_w, title_h;
    SDL_QueryTexture(txtTitle, NULL, NULL, &title_w, &title_h);
    SDL_Rect title_dst = {(WINDOW_W - title_w) / 2, 40, title_w, title_h};
    SDL_RenderCopy(*renderer, txtTitle, NULL, &title_dst);

    SDL_Color highlight = {255, 221, 51, 255};
    SDL_Color gray = {60, 60, 60, 255};
    for (size_t btn = 0; btn < BUTTON_COUNT; ++btn) {
      SDL_SetRenderDrawColor(*renderer, gray.r, gray.g, gray.b, 255);
      SDL_RenderFillRect(*renderer, &btn_rects[btn]);
    }
    SDL_SetRenderDrawColor(*renderer, highlight.r, highlight.g, highlight.b, 255);

    int sel_idx = 0;
    if (selected == MODE_SOLO) {
      sel_idx = 0;
    } else if (selected == MODE_1V1) {
      sel_idx = 1;
    } else if (selected == MODE_AI) {
      sel_idx = 2;
    } else if (selected == MODE_EXIT) {
      sel_idx = 3;
    }

    for (int i = 0; i < 3; ++i) {
      SDL_Rect border = {btn_rects[sel_idx].x + i, btn_rects[sel_idx].y + i, btn_rects[sel_idx].w - 2 * i, btn_rects[sel_idx].h - 2 * i};
      SDL_RenderDrawRect(*renderer, &border);
    }

    int txt_w, txt_h;
    for (size_t btn = 0; btn < BUTTON_COUNT; ++btn) {
      SDL_QueryTexture(btn_textures[btn], NULL, NULL, &txt_w, &txt_h);
      SDL_Rect dst = {btn_rects[btn].x + (BUTTON_W - txt_w) / 2, btn_rects[btn].y + (BUTTON_H - txt_h) / 2, txt_w, txt_h};
      SDL_RenderCopy(*renderer, btn_textures[btn], NULL, &dst);
    }

    SDL_RenderPresent(*renderer);
  }

  SDL_DestroyTexture(txtTitle);
  for (int btn = 0; btn < BUTTON_COUNT; ++btn) {
    SDL_DestroyTexture(btn_textures[btn]);
  }
  SDL_DestroyTexture(txtTitle);
  TTF_CloseFont(title_font);
  TTF_CloseFont(font);

  return mode;
}
