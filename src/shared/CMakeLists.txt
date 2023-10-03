add_library(common)

target_sources(common
  PRIVATE
    common.cpp
  PUBLIC
    common.h
  )

target_include_directories(common
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(ch_1
    PUBLIC
      "--coverage"
    )
  target_link_options(ch_1
    INTERFACE
      "--coverage"
    )
endif()
