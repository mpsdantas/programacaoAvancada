//
// Created by marcus on 03/09/17.
//
#ifndef LOJA_LISTALIVRO_H
#define LOJA_LISTALIVRO_H
#include "Livro.h"

class ListaLivro {
private:
    Livro *listaLivro;
    unsigned N;
    void criar(unsigned n);
    void copiar(const ListaLivro &listaCopy);
    void limpar();
public:
    inline ListaLivro(): N(0), listaLivro(NULL){}
    inline ListaLivro(unsigned n){criar(n);}
    inline ListaLivro(const ListaLivro &listaCopy) {copiar(listaCopy);}
    inline ~ListaLivro(){limpar();}
    void incluir(const Livro &livro);
    void excluir(const unsigned i);
    void imprimir();
    void salvar(ostream &O);
    void ler(istream &I);
};
#endif //LOJA_LISTALIVRO_H
