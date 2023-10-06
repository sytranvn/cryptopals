#include "ch_3.h"
#include <gtest/gtest.h>

TEST(ch_3, single_byte_xor_cipher) {
  char *str =
      "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  char *rs;
  char cipher;
  std::size_t len;
  single_byte_xor_cipher(str, &rs, &cipher);
  printf("%c: %s\n", cipher, rs);
}
