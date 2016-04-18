cmake_minimum_required(VERSION 3.5)
project(Exercicios_PC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES parque.c teste.c consumidor_semaforo.c)
set(ALL_FILES hello.c macacos.c parque.c canibais.c )

add_executable(Exercicios_PC ${SOURCE_FILES} consumidor.c)