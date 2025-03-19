#ifndef __TETRIS_RANDOM__
#define __TETRIS_RANDOM__

#include <stdlib.h>

/**
 * @brief Get a random `size_t` between min (inclusive) and max (inclusive).
 *
 * @param min
 * @param max
 * @return size_t
 */
size_t random_size_t(size_t min, size_t max);

#endif
