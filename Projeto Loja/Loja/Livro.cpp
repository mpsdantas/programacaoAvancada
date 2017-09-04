//
// Created by marcus on 02/09/17.
//

#include "Livro.h"

void Livro::digitar() {
    Produto::digitar();
    do{
        cout << "Autor do livro:" << endl;
        cin.ignore();
        getline(cin,autor);
    }while(autor.size()==0);
}
void Livro::imprimir() {
    cout << "L: ";
    Produto::imprimir();
    cout << ';';
    cout << '"';
    cout << autor;
    cout << '"';
}
void Livro::ler(istream &I) {
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), '"');
    getline(I,autor,'"');
}
void Livro::salvar(ostream &O) {
    O << "L: ";
    Produto::salvar(O);
    O << ';';
    O << '"';
    O << autor;
    O << '"';
}
