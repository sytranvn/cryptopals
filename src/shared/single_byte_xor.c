#include "single_byte_xor.h"

#include <limits.h>

#include "english_character_scoring.h"

int compar(const void *a, const void *b) {
  decrypted_text *_a = (decrypted_text *)a;
  decrypted_text *_b = (decrypted_text *)b;
  return (_a->score < _b->score) - (_a->score > _b->score);
}

char *single_byte_xor(const u_int8_t *buff, size_t len, char *key,
                      float *score) {
  decrypted_text outputs[CHAR_MAX] = {0};
  decrypted_text *d;
  for (int c = 0; c < CHAR_MAX; c++) {
    d = &(outputs[c]);
    d->key = (char)c;
    d->text = mcalloc(len + 1, sizeof(char));
    for (int i = 0; i < len; i++) {
      d->text[i] = buff[i] ^ (char)c;
    }
    d->score = english_character_scoring(d->text, len);
  }
  qsort(outputs, CHAR_MAX, sizeof(decrypted_text), compar);
  char *out = (char *)mmalloc(len + 1);
  strcpy(out, outputs[0].text);
  if (score != NULL) *score = outputs[0].score;
  if (key != NULL) *key = outputs[0].key;

  return out;
};

void single_byte_xor_top_n(const u_int8_t *buff, size_t len, int top,
                           char **key) {
  decrypted_text outputs[256] = {0};
  decrypted_text *d;
  for (int c = 0; c < 256; c++) {
    d = &(outputs[c]);
    d->key = (char)c;
    d->text = mmalloc(len + 1);
    d->text[len] = '\0';
    for (int i = 0; i < len; i++) {
      d->text[i] = buff[i] ^ (char)c;
    }
    d->score = english_character_scoring(d->text, len);
  }
  qsort(outputs, 256, sizeof(decrypted_text), compar);

  // get the top highest score key out
  *key = mmalloc(top);
  for (int i = 0; i < top; i++) {
    (*key)[i] = outputs[i].key;
  }
};
