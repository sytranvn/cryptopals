#include "hamming_distance.h"

int hamming_distance(const u_int8_t *a, const u_int8_t *b, size_t len) {
  int d = 0;
  for (int i = 0; i < len; i++) {
    d += __builtin_popcount(a[i] ^ b[i]);
  }
  return d;
}
