cmake_minimum_required(VERSION 3.15)

project(clearn)

set(CMAKE_CXX_STANDARD 14)
set(OUTPUT_NAME "clearn")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

if( OPENSSL_FOUND )
    include_directories(${OPENSSL_INCLUDE_DIRS})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

find_library(PTHREAD_LIBRARY pthread)
find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})

add_library(db STATIC lib/db/database.cpp lib/db/user.cpp)
add_library(exception STATIC lib/exception/exception.cpp)
add_library(utils STATIC lib/utils/hash.cpp)
add_library(view STATIC lib/view/view.cpp lib/view/AdminView.cpp lib/view/TrainerView.cpp lib/view/TrainerView.cpp)
add_executable(${OUTPUT_NAME} main.cpp)

target_link_libraries(${OUTPUT_NAME} db utils exception)
target_link_libraries(${OUTPUT_NAME} ${PTHREAD_LIBRARY})
target_link_libraries(${OUTPUT_NAME} ${SQLite3_LIBRARIES})
target_link_libraries(${OUTPUT_NAME} ${OPENSSL_LIBRARIES})