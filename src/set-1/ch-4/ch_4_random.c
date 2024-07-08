#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "english_character_scoring.h"
#include "single_byte_xor.h"

int main() {
  srand(time(NULL));
  u_int8_t buff[30] = {0};
  char key;
  float s;
  for (int i = 0; i < 30; i++) {
    buff[i] = (u_int8_t)rand();
  }
  s = english_character_scoring("the dog jump over a running cat", 31);
  printf("%f\n", s);
  s = english_character_scoring((char*)buff, 30);
  printf("%f\n", s);
}
