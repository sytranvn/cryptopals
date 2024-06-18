#include "single_byte_xor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "english_character_scoring.h"

int compar(const void *a, const void *b) {
  decrypted_text *_a = (decrypted_text *)a;
  decrypted_text *_b = (decrypted_text *)b;
  return (_a->score < _b->score) - (_a->score > _b->score);
}

float single_byte_xor(const u_int8_t *buff, size_t len, char **out, char *key) {
  decrypted_text outputs[256] = {0};
  decrypted_text *d;
  for (int c = 0; c < 256; c++) {
    d = &(outputs[c]);
    d->key = (char)c;
    d->text = malloc((len + 1) * sizeof(char));
    if (!d->text) {
      fprintf(stderr, "Unable to allocate %ld bytes\n", len + 1 * sizeof(char));
      exit(EXIT_FAILURE);
    }
    d->text[len] = '\0';
    for (int i = 0; i < len; i++) {
      d->text[i] = buff[i] ^ (char)c;
    }
    d->score = english_character_scoring(d->text, len);
  }
  qsort(outputs, 256, sizeof(decrypted_text), compar);
  (*out) = (char *)malloc((len + 1) * sizeof(char));
  if (!*out) {
    fprintf(stderr, "Unable to allocate %ld bytes\n", len + 1 * sizeof(char));
    exit(EXIT_FAILURE);
  }
  strcpy(*out, outputs[0].text);
  *key = outputs[0].key;
  return outputs[0].score;
};
