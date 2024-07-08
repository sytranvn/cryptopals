#include <ctype.h>
#include <limits.h>  // for CHAR_MAX
#include <stdio.h>

int main() {
  printf("%5s%5s\n", "dec", "char");
  printf("%5s%5s\n", "---", "----");

  for (char i = 0; i < CHAR_MAX; i++) {
    printf("%5hhd%5c\n", i, isprint(i) || isspace(i) ? i : '.');
  }
}
