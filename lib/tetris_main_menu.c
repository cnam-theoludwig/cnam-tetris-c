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

GameMode run_tetris_main_menu(SDL_Window** window,
                              SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return MODE_NONE;
    if (TTF_Init() == -1) { SDL_Quit(); return MODE_NONE; }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) { TTF_Quit(); SDL_Quit(); return MODE_NONE; }

    *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    if (!*window) return MODE_NONE;
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) { SDL_DestroyWindow(*window); return MODE_NONE; }

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 36);
    SDL_Rect btnSolo = {(WINDOW_W - BUTTON_W)/2, 180, BUTTON_W, BUTTON_H};
    SDL_Rect btn1v1 = {(WINDOW_W - BUTTON_W)/2, 300, BUTTON_W, BUTTON_H};
    SDL_Rect btnExit = {(WINDOW_W - BUTTON_W)/2, 420, BUTTON_W, BUTTON_H};

    SDL_Texture* txtSolo = renderText(*renderer, font, "Mode Solo");
    SDL_Texture* txt1v1 = renderText(*renderer, font, "Mode 1v1");
    SDL_Texture* txtExit = renderText(*renderer, font, "Quitter");

    GameMode mode = MODE_NONE;
    SDL_Event ev;
    while (mode == MODE_NONE && SDL_WaitEvent(&ev)) {
        if (ev.type == SDL_QUIT) { mode = MODE_EXIT; break; }
        if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT) {
            int x = ev.button.x, y = ev.button.y;
            if (x >= btnSolo.x && x <= btnSolo.x+BUTTON_W && y >= btnSolo.y && y <= btnSolo.y+BUTTON_H)
                mode = MODE_SOLO;
            else if (x >= btn1v1.x && x <= btn1v1.x+BUTTON_W && y >= btn1v1.y && y <= btn1v1.y+BUTTON_H)
                mode = MODE_1V1;
            else if (x >= btnExit.x && x <= btnExit.x+BUTTON_W && y >= btnExit.y && y <= btnExit.y+BUTTON_H)
                mode = MODE_EXIT;
        }
        SDL_SetRenderDrawColor(*renderer, 26, 26, 26, 255);
        SDL_RenderClear(*renderer);
        SDL_SetRenderDrawColor(*renderer, 60, 60, 60, 255);
        SDL_RenderFillRect(*renderer, &btnSolo);
        SDL_RenderFillRect(*renderer, &btn1v1);
        SDL_RenderFillRect(*renderer, &btnExit);

        SDL_Rect dst = {btnSolo.x + 30, btnSolo.y + 20, 0, 0};
        SDL_QueryTexture(txtSolo, NULL, NULL, &dst.w, &dst.h);
        SDL_RenderCopy(*renderer, txtSolo, NULL, &dst);

        dst = (SDL_Rect){btn1v1.x + 40, btn1v1.y + 20, 0, 0};
        SDL_QueryTexture(txt1v1, NULL, NULL, &dst.w, &dst.h);
        SDL_RenderCopy(*renderer, txt1v1, NULL, &dst);

        dst = (SDL_Rect){btnExit.x + 55, btnExit.y + 20, 0, 0};
        SDL_QueryTexture(txtExit, NULL, NULL, &dst.w, &dst.h);
        SDL_RenderCopy(*renderer, txtExit, NULL, &dst);

        SDL_RenderPresent(*renderer);
    }

    SDL_DestroyTexture(txtSolo);
    SDL_DestroyTexture(txt1v1);
    SDL_DestroyTexture(txtExit);
    TTF_CloseFont(font);

    return mode;
}
