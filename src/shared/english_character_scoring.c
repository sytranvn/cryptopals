#include "english_character_scoring.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>

// https://github.com/ricpacca/cryptopals/blob/master/S1C03.py#L1-L7
const float CHAR_FREQ[CHAR_MAX] = {
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0.1918182, 0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0,
    0,         0,         0,         0,         0,         0,         0.0651738,
    0.0124248, 0.0217339, 0.0349835, 0.1041442, 0.0197881, 0.0158610, 0.0492888,
    0.0558094, 0.0009033, 0.0050529, 0.0331490, 0.0202124, 0.0564513, 0.0596302,
    0.0137645, 0.0008606, 0.0497563, 0.0515760, 0.0729357, 0.0225134, 0.0082903,
    0.0171272, 0.0013692, 0.0145984, 0.0007836, 0,
};

/**
 * Calculate square frequency error
 *
 */
float english_character_scoring(const char* str, size_t len) {
  float s = 0;
  int c;
  int freq[CHAR_MAX] = {0};

  for (int i = 0; i < len; i++) {
    c = tolower(str[i]);
    if (isalpha(c) || isspace(c)) freq[c]++;
  }

  for (int i = 0; i < CHAR_MAX; i++) {
    if (CHAR_FREQ[i]) {
      s += (1.0 * freq[i] / len - CHAR_FREQ[i]) *
           (1.0 * freq[i] / len - CHAR_FREQ[i]);
    }
  }
  return 1.0 / s / len;
};
