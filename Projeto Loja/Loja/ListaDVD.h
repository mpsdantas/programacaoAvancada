//
// Created by marcus on 04/09/17.
//

#ifndef LOJA_LISTADVD_H
#define LOJA_LISTADVD_H


#include "Dvd.h"

class ListaDVD {
    Dvd *listaDVD;
    unsigned N;
    void criar(unsigned n);
    void copiar(const ListaDVD &listaCopy);
    void limpar();
public:
    inline ListaDVD(): N(0), listaDVD(NULL){}
    inline ListaDVD(unsigned n){criar(n);}
    inline ListaDVD(const ListaDVD &listaCopy) {copiar(listaCopy);}
    inline ~ListaDVD(){limpar();}
    void incluir(const Dvd &Dvd);
    void excluir(const unsigned i);
    void imprimir();
    void salvar(ostream &O);
    void ler(istream &I);
};


#endif //LOJA_LISTADVD_H
