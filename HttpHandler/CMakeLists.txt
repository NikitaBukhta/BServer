#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.6.0)
set(PROJECT_NAME server_httphandler)
project(${PROJECT_NAME})

file(GLOB_RECURSE LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(
    ${PROJECT_NAME}
    ${LIB_SRC}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    public/include
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    private/include
)

#----------------------------- LINK LIBRARIES -----------------------------#

set(
    PUBLIC_LIBS
    bserver_connectionhandler
    picohttpparser
)

set(
    PRIVATE_LIBS
    spdlog::spdlog
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ${PUBLIC_LIBS}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${PRIVATE_LIBS}
)