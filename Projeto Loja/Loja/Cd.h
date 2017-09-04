//
// Created by marcus on 02/09/17.
//

#ifndef LOJA_CD_H
#define LOJA_CD_H


#include "Produto.h"

class Cd: public Produto{
    int numFaixas;
public:
    void digitar();
    void imprimir();
    inline friend istream &operator>>(istream &I, Cd &cd){cd.digitar(); return I;}
    inline friend ostream &operator<<(ostream &O, Cd &cd){cd.imprimir(); return O;}
    void ler(istream &I);
    void salvar(ostream &O);
};


#endif //LOJA_CD_H
