#ifndef SINGLE_BYTE_XOR_H_
#define SINGLE_BYTE_XOR_H_

#include <stdlib.h>

#include "common.h"
#include "english_character_scoring.h"

typedef struct {
  char key;
  char *text;
  float score;
} decrypted_text;
char *single_byte_xor(const u_int8_t *buff, size_t len, char *key,
                      float *score);

void single_byte_xor_top_n(const u_int8_t *buff, size_t len, int top,
                           char **key);
#endif
