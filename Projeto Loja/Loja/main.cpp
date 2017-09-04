#include <iostream>
#include "Produto.h"
#include "Livro.h"
#include "Cd.h"
#include "Dvd.h"
#include "ListaLivro.h"
#include "ListaCD.h"
#include "ListaDVD.h"

using namespace std;
int main() {
    string nome_arquivo = "listaDVD.txt";
    Produto produto;
    Livro livro;
    Cd cd;
    Dvd dvd;
    ListaCD listaCD;
    ListaDVD listaDVD;
    ifstream arq(nome_arquivo.c_str());
    listaDVD.ler(arq);
    listaDVD.imprimir();
    /*
    ifstream arq(nome_arquivo.c_str());
    dvd.ler(arq);
    cout << dvd;
     */
    //ofstream arq(nome_arquivo.c_str());
    //dvd.salvar(arq);
    //cin >> cd;
    //ofstream arq(nome_arquivo.c_str());
    //cd.salvar(arq);
    //cin >> cd;
    //cout << cd;
    //cin >> livro;
    //ifstream arq(nome_arquivo.c_str());
    //livro.ler(arq);
    //cin >> produto;
    //cout << produto;
    //cin >> livro;
    //cout << livro;
    /*ifstream arq(nome_arquivo.c_str());
    produto.ler(arq);
     */
}