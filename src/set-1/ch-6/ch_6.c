#include "ch_6.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "hamming_distance.h"
#include "repeating_key_xor.h"
#include "single_byte_xor.h"

void read_input(int, const char**, char**);
void cleanup();

int main(int argc, const char** args) {
  int d = hamming_distance((u_int8_t*)"this is a test",
                           (u_int8_t*)"wokka wokka!!!", 15);
  assert(d == 37);
  char* content;
  u_int8_t* buff;
  size_t buff_len;

  read_input(argc, args, &content);
  b64_str_to_buff(content, &buff, &buff_len);
  free(content);

  int keysize;
  float min_d = 999.9;
  float avg_d;
  for (int ks = 2; ks < 40; ks++) {
    d = 0;
    // TODO: need all combination pair
    for (int i = 0; i < buff_len - ks - 2; i += ks) {
      d += hamming_distance(buff + i, buff + i + ks, 4);
    }
    avg_d = (1.0 * d) / ((buff_len - ks - 1) / ks);
    if (avg_d < min_d) {
      keysize = ks;
      min_d = avg_d;
    };
  }
  printf("%d %f\n", keysize, min_d);
  u_int8_t* transformed_buff;
  char* temp;
  char* key = calloc(keysize, sizeof(char));
  if (!key) {
    fprintf(stderr, "Unalble to allocate %d bytes", keysize);
    exit(EXIT_FAILURE);
  }
  int width = keysize * ((buff_len + keysize) / keysize);
  for (int i = 0; i < keysize; i++) {
    single_byte_xor(buff + (i * width), width, &temp, &key[i]);
  }
  printf("key: %s\n", key);
  u_int8_t* out;
  repeating_key_xor((char*)buff, key, &out);
  printf("%s\n", out);
}

void read_input(int argc, const char** args, char** content) {
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
  char* str = (char*)malloc(content_len + 1);
  memset(str, 0, content_len + 1);
  if (!str) {
    fprintf(stderr, "Unable to allocate %ld bytes\n", content_len);
    exit(EXIT_FAILURE);
  }
  content_len = 0;
  while ((c = fgetc(f)) != EOF) {
    // remove redundant newlines
    if (c != '\n') str[content_len++] = c;
  }
  fclose(f);
  str[content_len] = '\0';

  *content = (char*)malloc(content_len + 1);
  strcpy(*content, str);
  free(str);
}

void combination() {};
