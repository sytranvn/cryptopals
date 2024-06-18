add_executable(ch_1)

target_sources(
  ch_1
  PRIVATE ch_1.h ch_1.c)

target_link_libraries(ch_1 PRIVATE common)
