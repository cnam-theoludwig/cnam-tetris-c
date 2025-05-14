#include <stdio.h>
#include <stdlib.h>

#include "./tetris_add_tetromino_test.h"
#include "./tetris_destroy_test.h"
#include "./tetris_last_tetromino_step_test.h"
#include "./tetris_struct_test.h"

int main() {
  tetris_add_tetromino_test();
  tetris_destroy_test();
  tetris_last_tetromino_step_test();
  tetris_struct_test();
  printf("Success: Tests passed!\n");
  return EXIT_SUCCESS;
}
