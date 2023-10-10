#ifndef CH_4_H_
#define CH_4_H_

#include "ch_3.h"
#include "common.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string.h>

void detect_single_byte_xor(const char **strs, std::size_t strs_len, char **out,
                            char *cipher);

#endif
