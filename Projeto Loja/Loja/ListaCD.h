//
// Created by marcus on 03/09/17.
//

#ifndef LOJA_LISTACD_H
#define LOJA_LISTACD_H


#include "Cd.h"

class ListaCD {
private:
    Cd *listaCD;
    unsigned N;
    void criar(unsigned n);
    void copiar(const ListaCD &listaCopy);
    void limpar();
public:
    inline ListaCD(): N(0), listaCD(NULL){}
    inline ListaCD(unsigned n){criar(n);}
    inline ListaCD(const ListaCD &listaCopy) {copiar(listaCopy);}
    inline ~ListaCD(){limpar();}
    void incluir(const Cd &cd);
    void excluir(const unsigned i);
    void imprimir();
    void salvar(ostream &O);
    void ler(istream &I);
};


#endif //LOJA_LISTACD_H
