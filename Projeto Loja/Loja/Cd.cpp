//
// Created by marcus on 02/09/17.
//

#include "Cd.h"
void Cd::digitar() {
    Produto::digitar();
    do{
        cout << "Quantidade de faixas: " << endl;
        cin  >> numFaixas;
    }while(numFaixas<=0);
}
void Cd::imprimir() {
    cout << "C: ";
    Produto::imprimir();
    cout << ';';
    cout << numFaixas;
}
void Cd::ler(istream &I) {
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> numFaixas;
}
void Cd::salvar(ostream &O) {
    O << "C: ";
    Produto::salvar(O);
    O << ';';
    O << numFaixas;
}
