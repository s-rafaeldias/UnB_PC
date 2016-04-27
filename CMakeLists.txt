cmake_minimum_required(VERSION 3.5)
project(Exercicios_PC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES "Estudo Dirigido/estudo_dirigido_6.c" "Estudo Dirigido/estudo_dirigido_7.c")
set(ALL_FILES "Estudo Dirigido/estudo_dirigido_6.c")

add_executable(Exercicios_PC ${SOURCE_FILES} "Estudo Dirigido/estudo_dirigido_6.c" "Estudo Dirigido/estudo_dirigido_7.c")
