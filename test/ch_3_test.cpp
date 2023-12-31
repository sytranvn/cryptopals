#include "ch_3.h"
#include <gtest/gtest.h>

TEST(ch_3, single_byte_xor_cipher) {
  const char *str =
      "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  const char *expect = "Cooking MC's like a pound of bacon";
  char *out;
  char cipher;
  std::size_t len;
  float fitness;
  single_byte_xor_cipher(str, &out, &cipher, &fitness);
  printf("%c: %s\n", cipher, out);
  ASSERT_EQ(cipher, 'X');
  ASSERT_STREQ(out, expect);
  ASSERT_EQ(fitness, 181);

  free(out);
}
