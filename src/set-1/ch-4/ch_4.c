
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "single_byte_xor.h"

int main(int argc, const char** args) {
  FILE* f;
  char* line;
  char** out;
  const char* expected = "Now that the party is jumping\n";
  if (argc == 1) {
    fprintf(stderr, "%s <file ch_4.txt>\n", args[0]);
    exit(EXIT_FAILURE);
  }
  f = fopen(args[1], "r");
  if (!f) {
    fprintf(stderr, "Cannot open file %s\n", args[1]);
    exit(EXIT_FAILURE);
  }
  char* str;
  float s = 0;
  u_int8_t* buf;
  size_t len = 0, nread;
  char* rs;
  char* result = mmalloc(100);
  while ((nread = getline(&line, &len, f)) != -1) {
    char* c = strchr(line, '\n');
    if (c) *c = '\0';
    buf = hex_str_to_buff(line, &len);
    float score;
    rs = single_byte_xor(buf, len, NULL, &score);
    if (score > s) {
      s = score;
      strcpy(result, rs);
    }
    free(rs);
  }
  if (line != NULL) free(line);
  printf("%s\nscore: %f\n", result, s);

  assert(strcmp(result, expected) == 0);
  fclose(f);
  return 0;
}
