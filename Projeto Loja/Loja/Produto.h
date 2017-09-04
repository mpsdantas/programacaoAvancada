//
// Created by marcus on 02/09/17.
//
#ifndef LOJA_PRODUTO_H
#define LOJA_PRODUTO_H
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Produto {
private:
    string nome;
    unsigned preco;
    inline unsigned parseCent(float valor){return (valor*100);};
    double parseReal();
public:
    void digitar();
    void imprimir();
    inline friend istream &operator>>(istream &I, Produto &produto){produto.digitar(); return I;}
    inline friend ostream &operator<<(ostream &O, Produto &produto){produto.imprimir(); return O;}
    void ler(istream &I);
    void salvar(ostream &O);
};
#endif //LOJA_PRODUTO_H
