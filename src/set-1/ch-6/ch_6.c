#include "ch_6.h"

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "english_character_scoring.h"
#include "hamming_distance.h"
#include "repeating_key_xor.h"
#include "single_byte_xor.h"

char* read_input(int, const char**);
void cleanup();
void all_key_comb(char** top_keys, int len, int top, char* curr,
                  char*** gen_keys, int i, int* comb_count);

char** get_top_keys(u_int8_t* buff, size_t buff_len, size_t keysize,
                    const int top);

int main(int argc, const char** args) {
  int d = hamming_distance((u_int8_t*)"this is a test",
                           (u_int8_t*)"wokka wokka!!!", 15);
  assert(d == 37);
  char* content = read_input(argc, args);
  size_t buff_len;

  u_int8_t* buff = b64_str_to_buff(content, &buff_len);
  free(content);

  int keysize;
  const int top = 5;
  char** top_keys = get_top_keys(buff, buff_len, keysize, top);
  char** key_combs;
  int comb_count = ipow(top, keysize);
  key_combs = mmalloc(sizeof(char*) * comb_count);
  char* curr = mmalloc(keysize + 1);
  memset(curr, 0, keysize + 1);
  all_key_comb(top_keys, keysize, top, curr, &key_combs, 0, &comb_count);
  char* temp;
  char* result = mmalloc(buff_len + 1);
  float score = 0, min_score = 0;
  for (int i = 0; i < comb_count; i++) {
    temp = repeating_key_xor((char*)buff, buff_len, key_combs[i]);
    score = english_character_scoring(temp, buff_len);
    if (score > min_score) {
      min_score = score;
      strcpy(result, temp);
    }
    free(temp);
  }
  printf("%s", result);
}

char* read_input(int argc, const char** args) {
  FILE* f;
  if (argc != 2) {
    fprintf(stderr, "%s <file 6.txt>\n", args[0]);
    exit(EXIT_FAILURE);
  }

  f = fopen(args[1], "r");
  if (!f) {
    fprintf(stderr, "Unable to open file %s\n", args[1]);
    exit(EXIT_FAILURE);
  }

  size_t content_len = 0;
  char c;
  while ((c = fgetc(f)) != EOF) {
    // remove redundant newlines
    if (c != '\n') content_len++;
  }
  fseek(f, 0, SEEK_SET);
  char* str = (char*)mmalloc(content_len + 1);
  memset(str, 0, content_len + 1);
  content_len = 0;
  while ((c = fgetc(f)) != EOF) {
    // remove redundant newlines
    if (c != '\n') str[content_len++] = c;
  }
  fclose(f);
  str[content_len] = '\0';

  return str;
}

void all_key_comb(char** top_keys, int len, int top, char* curr,
                  char*** gen_keys, int i, int* comb_count) {
  if (i == len) {
    (*gen_keys)[i] = mmalloc(len);
    strcpy(curr, (*gen_keys)[i]);
    (*comb_count)++;
    return;
  }
  for (int j = 0; j < top; j++) {
    curr[i] = top_keys[i][j];
    all_key_comb(top_keys, len, top, curr, gen_keys, i + 1, comb_count);
  }
}

char** get_top_keys(u_int8_t* buff, size_t buff_len, size_t keysize,
                    const int top) {
  float min_d = 999.9;
  float avg_d;
  int d;
  for (int ks = 2; ks < 40; ks++) {
    d = 0;
    int c = 0;
    // TODO: need all combination pair
    for (int i = 0; i < buff_len - ks - 4; i += ks) {
      for (int j = i + 1; j < buff_len - 4; j++) {
        d += hamming_distance(buff + i, buff + i + ks, 4);
        c++;
      }
    }
    avg_d = (1.0 * d) / c;
    if (avg_d < min_d) {
      keysize = ks;
      min_d = avg_d;
    };
  }
  printf("%ld %f\n", keysize, min_d);
  char** top_keys = mmalloc(keysize * sizeof(char*));
  for (int i = 0; i < top; i++) {
    top_keys[i] = mmalloc(top);
  }
  int width = keysize * ((buff_len + keysize) / keysize);
  for (int i = 0; i < keysize; i++) {
    single_byte_xor_top_n(buff + (i * width), width, top, &(top_keys[i]));
  }
  return top_keys;
}
