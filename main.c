#include <time.h>

#include "tetris.h"

int main() {
  srand(time(NULL));
  // arkanoid_game();
  // tetris_game();
  tetris_ui();
  return EXIT_SUCCESS;
}
