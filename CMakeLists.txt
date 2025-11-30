cmake_minimum_required(VERSION 4.0)
project(netflix_n_chill)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(netflix_n_chill
        src/main.cpp
        src/peliculas.cpp
        src/peliculas.h
        src/usuarios.cpp
        src/usuarios.h
        src/hashTable.cpp
        src/recomendaciones.cpp
        src/ratings.cpp
        src/ratings.h)
