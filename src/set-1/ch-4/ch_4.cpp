#include "ch_4.h"
#include "common.h"
#include <cstring>

void detect_single_byte_xor(const char *strs[], std::size_t strs_len,
                            char **out, char *cipher) {
  char *cur;
  char cur_cipher;
  float fitness;
  float fitness_max = 0;
  *out = (char *)malloc(strlen(strs[0]) * sizeof(char));
  memset(*out, '\0', strlen(strs[0]));

  for (int i = 0; i < strs_len; i++) {
    single_byte_xor_cipher((strs)[i], &cur, &cur_cipher, &fitness);
    if (fitness > fitness_max) {
      memcpy(*out, (strs)[i], strlen(strs[i]) * sizeof(char));
      *cipher = cur_cipher;
    }
  }
}
