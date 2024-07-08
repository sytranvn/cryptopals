#include "ch_4.h"

#include <limits.h>
#include <math.h>

FILE* f;
char** strings;
char line[100];
int lines = 0;
u_int8_t** buff;
size_t* len;
char** out;
const char* expected = "Now that the party is jumping\n";

void read_input(int argc, const char** args);
void cleanup();

int main(int argc, const char** args) {
  read_input(argc, args);
  for (int i = 0; i < lines; i++) {
    fgets(line, 100, f);
    char* c = strchr(line, '\n');
    if (c) *c = '\0';
    strings[i] = (char*)mmalloc(strlen(line) * sizeof(char));
    strcpy(strings[i], line);
  }
  float s = 0;
  char result[100];
  for (int i = 0; i < lines; i++) {
    buff[i] = hex_str_to_buff(strings[i], &len[i]);
    float score;
    single_byte_xor(buff[i], len[i], NULL, &score);
    if (score > s) {
      s = score;
      strcpy(result, out[i]);
    }
  }
  printf("%s\n", result);

  assert(strcmp(result, expected) == 0);
  cleanup();

  return 0;
}

void cleanup() {
  for (int i = 0; i < lines; i++) {
    free(buff[i]);
    free(strings[i]);
  }
  free(buff);
  free(strings);
}
void read_input(int argc, const char** args) {
  if (argc == 1) {
    fprintf(stderr, "%s <file ch_4.txt>\n", args[0]);
    exit(EXIT_FAILURE);
  }
  f = fopen(args[1], "r");
  if (!f) {
    fprintf(stderr, "Cannot open file %s\n", args[1]);
    exit(EXIT_FAILURE);
  }
  while (fgets(line, 100, f)) {
    lines++;
  }
  fseek(f, 0, SEEK_SET);
  strings = mmalloc(lines * sizeof(char*));
  len = mmalloc(lines * sizeof(*len));
  buff = mmalloc(lines * sizeof(u_int8_t));
  out = mmalloc(lines * sizeof(char*));
  printf("Read %d lines\n", lines);
  fclose(f);
}
