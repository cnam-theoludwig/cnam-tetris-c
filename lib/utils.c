#include "utils.h"

size_t random_size_t(size_t min, size_t max) {
  return (rand() % (max - min + 1)) + min;
}
