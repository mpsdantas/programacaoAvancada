cmake_minimum_required(VERSION 3.8)
project(Loja)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Produto.cpp Produto.h Livro.cpp Livro.h Cd.cpp Cd.h Dvd.cpp Dvd.h ListaLivro.cpp ListaLivro.h ListaCD.cpp ListaCD.h ListaDVD.cpp ListaDVD.h)
add_executable(Loja ${SOURCE_FILES})