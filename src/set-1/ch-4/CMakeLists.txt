add_executable(ch_4)
target_sources(ch_4 PRIVATE ch_4.c)
target_link_libraries(ch_4 PRIVATE common)

add_executable(ch_4_random)
target_sources(ch_4_random PRIVATE ch_4_random.c)
target_link_libraries(ch_4_random PRIVATE common)

add_executable(ch_4_limits)
target_sources(ch_4_limits PRIVATE ch_4_limits.c)
