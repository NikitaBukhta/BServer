#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.6.0)
set(PROJECT_NAME bserver_library)
project(${PROJECT_NAME})

file(GLOB LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(
    ${PROJECT_NAME}
    INTERFACE
    ${LIB_SRC}
)

#----------------------------- LINK LIBRARIES -----------------------------#

add_subdirectory(third_party)
add_subdirectory(common)
add_subdirectory(Connection)
add_subdirectory(Initializer)
add_subdirectory(HttpHandler)

set(
    PUBLIC_LIBS
    bserver_initializer
    server_httphandler
)

target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    ${PUBLIC_LIBS}
)