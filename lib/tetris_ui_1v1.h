#ifndef __TETRIS_UI_1V1__
#define __TETRIS_UI_1V1__

#include "tetris_struct.h"
#include "tetris_ui.h"

// Prototype de la fonction utilitaire définie dans tetris_ui.c
SDL_Texture* load_texture_from_file(const char* path, SDL_Renderer* renderer);


/**
 * @brief  Lance un mode Tetris 1v1 local avec écrans splittés
 *
 * @param p1  Pointeur vers la structure Tetris du Joueur 1
 * @param p2  Pointeur vers la structure Tetris du Joueur 2
 * @return TetrisUIAction  Action retournée (CONTINUE, QUIT, RESTART)
 */
TetrisUIAction tetris_ui_1v1(struct Tetris* p1, struct Tetris* p2);

#endif // __TETRIS_UI_1V1__
