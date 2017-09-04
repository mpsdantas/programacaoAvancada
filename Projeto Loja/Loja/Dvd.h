//
// Created by marcus on 02/09/17.
//

#ifndef LOJA_DVD_H
#define LOJA_DVD_H


#include "Produto.h"

class Dvd: public Produto{
private:
    int duracao;
public:
    void digitar();
    void imprimir();
    inline friend istream &operator>>(istream &I, Dvd &dvd){dvd.digitar(); return I;}
    inline friend ostream &operator<<(ostream &O, Dvd &dvd){dvd.imprimir(); return O;}
    void ler(istream &I);
    void salvar(ostream &O);
};


#endif //LOJA_DVD_H
