//
// Created by marcus on 02/09/17.
//

#include <iostream>
#include "Produto.h"

void Produto::digitar() {
    /*
     * Recebe a entrada necessária dos valores do produto: nome e preço.
     * O preço é passado em reais e salvo em centavos.
     */
    float precoAuxiliar;
    do{
        cout << "Nome do produto: "<<endl;
        getline(cin,nome);
    }while(nome.size()==0);
    do{
        cout << "Preço do produto: " << endl;
        cin >> precoAuxiliar;
    }while(precoAuxiliar<0);
    preco = parseCent(precoAuxiliar);
}
void Produto::imprimir(){
    /*
     * Imprime o nome e valor do produto.
     * Saída esperada: "nome";$preco
     */
    cout << '"';
    cout << nome;
    cout << '"';
    cout << fixed;
    cout.precision(2);
    cout << ";$" << parseReal();
}
double Produto::parseReal() {
    /*
     * Convertento o preco em centavos para valor em real.
     * retorna o preço em reais.
     */
    double produtoAux;
    produtoAux = preco/100 + (preco%100)/100.0;
    return produtoAux;
}
void Produto::ler(istream &I) {
    double precoAuxiliar;
    I.ignore(numeric_limits<streamsize>::max(), '"');
    getline(I,nome,'"');
    I.ignore(numeric_limits<streamsize>::max(), '$');
    I>>precoAuxiliar;
    if(precoAuxiliar<0)
        preco =0.00;
    else
        preco = parseCent(precoAuxiliar);
}
void Produto::salvar(ostream &O) {
    O << '"';
    O << nome;
    O << '"';
    O << fixed;
    O.precision(2);
    O << ";$" << parseReal();
}