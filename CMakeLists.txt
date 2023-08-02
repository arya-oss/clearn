cmake_minimum_required(VERSION 3.15)

project(clearn)

set(CMAKE_CXX_STANDARD 14)
set(OUTPUT_NAME "clearn")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_library(PTHREAD_LIBRARY pthread)
find_library(ROCKSDB_LIBRARY rocksdb)
find_package (SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})

add_library(db STATIC lib/db/database.cpp lib/db/database.hpp)
add_library(hash STATIC lib/utils/hash.cpp lib/utils/hash.hpp)
add_executable(${OUTPUT_NAME} main.cpp)

target_link_libraries(${OUTPUT_NAME} db hash)
target_link_libraries(${OUTPUT_NAME} ${PTHREAD_LIBRARY})
target_link_libraries(${OUTPUT_NAME} ${ROCKSDB_LIBRARY})
target_link_libraries(${OUTPUT_NAME} ${SQLite3_LIBRARIES})
target_link_libraries(${OUTPUT_NAME} ${OPENSSL_LIBRARIES})