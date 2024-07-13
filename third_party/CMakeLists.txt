add_subdirectory(spdlog)

#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.6.0)
set(LIBPICO_NAME picohttpparser)
project(${LIBPICO_NAME} C)

file(GLOB_RECURSE LIB_PICO_SRC "${CMAKE_CURRENT_SOURCE_DIR}/picohttpparser/*.c")

add_library(
    ${LIBPICO_NAME}
    ${LIB_PICO_SRC}
)

target_include_directories(
    ${LIBPICO_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/picohttpparser
)