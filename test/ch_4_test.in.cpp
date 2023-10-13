#include "ch_4.h"
#include "common.h"
#include <cstdio>
#include <gtest/gtest.h>

TEST(ch_4, detect_single_byte_xor) {
  const char *test_data = R"(
@FILE_4_CONTENT@
)";
  char *out;
  char cipher;
  char **encrypted_texts;
  std::size_t encrypted_texts_len;
  long_str_to_lines(test_data, 500, &encrypted_texts, &encrypted_texts_len);

  for (int i = 0; i < encrypted_texts_len; i++) {
    printf("%d: %s\n", i, encrypted_texts[i]);
  }

  detect_single_byte_xor(encrypted_texts, encrypted_texts_len, &out, &cipher);
  ASSERT_STREQ(out, "Now that the party is jumping");
  ASSERT_EQ(cipher, '5');

  free(out);
};
