//
// Created by marcus on 02/09/17.
//

#include "Dvd.h"
void Dvd::digitar() {
    Produto::digitar();
    do{
        cout << "Digite a duração do filme: " << endl;
        cin  >> duracao;
    }while(duracao<=0);
}
void Dvd::imprimir() {
    cout << "D: ";
    Produto::imprimir();
    cout << ";";
    cout << duracao;
}
void Dvd::ler(istream &I) {
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> duracao;
}
void Dvd::salvar(ostream &O) {
    O << "D: ";
    Produto::salvar(O);
    O << ';';
    O << duracao;
}
