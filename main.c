#include <time.h>

#include "tetris.h"

int main() {
  srand(time(NULL));
  return tetris_ui();
}
