#ifndef __TETRIS_MAIN_MENU_H__
#define __TETRIS_MAIN_MENU_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "tetris_struct.h"
#include "tetris_ui.h"
#include "tetris_ui_1v1.h"

typedef enum {
  MODE_NONE = 0,
  MODE_SOLO,
  MODE_1V1,
  MODE_EXIT
} GameMode;

/**
 * @brief Affiche le menu principal SDL et permet de choisir le mode de jeu.
 *
 * @param window   Pointeur vers la fenêtre SDL créée pour le menu.
 * @param renderer Pointeur vers le renderer SDL créé pour le menu.
 * @return GameMode Le mode sélectionné (MODE_SOLO, MODE_1V1, MODE_EXIT), ou MODE_NONE si erreur.
 */
GameMode run_tetris_main_menu(SDL_Window** window,
                              SDL_Renderer** renderer);

#endif  // __TETRIS_MAIN_MENU_H__
