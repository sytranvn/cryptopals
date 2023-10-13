#include "ch_5.h"
#include "common.h"
#include <gtest/gtest.h>
#include <iostream>
#include <stdio.h>
#include <string>

TEST(ch_6, repeating_key_xor) {
  const char *test_data = R"(
@FILE_6_CONTENT@
)";
  // process lines
  char **strs;
  std::size_t len;
  long_str_to_lines(test_data, 500, &strs, &len);

  // clean up
  for (int i = 0; i < len; i++) {
    free(strs[i]);
  }
  free(strs);
};
