//
// Created by marcus on 02/09/17.
//

#ifndef LOJA_LIVRO_H
#define LOJA_LIVRO_H
#include "Produto.h"

class Livro: public Produto{
private:
    string autor;
public:
    void digitar();
    void imprimir();
    inline friend istream &operator>>(istream &I, Livro &livro){livro.digitar(); return I;}
    inline friend ostream &operator<<(ostream &O, Livro &livro){livro.imprimir(); return O;}
    void ler(istream &I);
    void salvar(ostream &O);
};


#endif //LOJA_LIVRO_H
