//
// Created by marcus on 03/09/17.
//
#include "ListaLivro.h"
void ListaLivro::criar(unsigned n) {
    N = n;
    if (N>0) listaLivro = new Livro[n];
    else listaLivro = NULL;
}
void ListaLivro::limpar() {
    if (listaLivro!=NULL) delete[] listaLivro;
    N = 0;
    listaLivro = NULL;
}
void ListaLivro::copiar(const ListaLivro &listaCopy) {
    criar(listaCopy.N);
    for (unsigned i=0; i<N; i++) listaLivro[i]=listaCopy.listaLivro[i];
}
void ListaLivro::incluir(const Livro &livro) {
    Livro *prov = new Livro[N+1];
    for (unsigned i=0; i<N; i++) prov[i]=listaLivro[i];
    prov[N] = livro;
    if (listaLivro!=NULL) delete[] listaLivro;
    N++;
    listaLivro = prov;
}
void ListaLivro::excluir(const unsigned i) {
    unsigned k = 0;
    Livro *prov = new Livro[N-1];
    for (unsigned j=0; j<N; j++){
        if(i!=j){
            prov[k]=listaLivro[j];
            k++;
        }
    }
    if (listaLivro!=NULL) delete[] listaLivro;
    N--;
    listaLivro = prov;
}
void ListaLivro::imprimir() {
    cout << "LISTALIVRO " << N << endl;
    for(unsigned i=0; i<N; i++){
        cout << i << ") ";
        cout << listaLivro[i];
        cout << endl;
    }
}
void ListaLivro::ler(istream &I) {
    string cabecalho;
    int n;
    Livro livro;
    getline(I,cabecalho,' ');
    I >> n;
    if(cabecalho!="LISTALIVRO"){
        cout << "Arquivo com cabeçalho de livros inválido." << endl;
    }else if(n<0){
        cout << "Arquivo com indece do cabeçalho inválido." << endl;
    }else{
        criar(n);
        for(unsigned i = 0; i<N;i++){
            livro.ler(I);
            listaLivro[i] = livro;
        }
    }
}
void ListaLivro::salvar(ostream &O) {
    O << "LISTALIVRO " << N << endl;
    for (unsigned i = 0; i < N; i++) {
        listaLivro[i].salvar(O);
        O << endl;
    }
}