cmake_minimum_required(VERSION 3.13)

project(cryptopals LANGUAGES C)

set(CMAKE_C_FLAGS "-g")

# export compile commands for clangd lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_subdirectory(src)

# If you have precompiled headers you can add them like this
# target_precompiled_headers(my_app PRIVATE "${CMAKE_SOURCE_DIR}/src/pch.h")

# add_subdirectory(test)
