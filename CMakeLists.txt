# Minimalna wymagana wersja CMake
cmake_minimum_required(VERSION 3.10)


project(Struktury_Danych_2 VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")



set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/BinaryHeap.cpp
    ${SRC_DIR}/LinkedList_q.cpp
)

set(HEADERS
    ${INC_DIR}/BinaryHeap_q.h
    ${INC_DIR}/LinkedList_q.h
    ${INC_DIR}/utility.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
