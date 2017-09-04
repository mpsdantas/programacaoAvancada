//
// Created by marcus on 03/09/17.
//

#include "ListaCD.h"

void ListaCD::criar(unsigned n) {
    N = n;
    if (N>0) listaCD = new Cd[n];
    else listaCD = NULL;
}
void ListaCD::limpar() {
    if (listaCD!=NULL) delete[] listaCD;
    N = 0;
    listaCD = NULL;
}
void ListaCD::copiar(const ListaCD &listaCopy) {
    criar(listaCopy.N);
    for (unsigned i=0; i<N; i++) listaCD[i]=listaCopy.listaCD[i];
}
void ListaCD::incluir(const Cd &cd) {
    Cd *prov = new Cd[N+1];
    for (unsigned i=0; i<N; i++) prov[i]=listaCD[i];
    prov[N] = cd;
    if (listaCD!=NULL) delete[] listaCD;
    N++;
    listaCD = prov;
}
void ListaCD::excluir(const unsigned i) {
    unsigned k = 0;
    Cd *prov = new Cd[N-1];
    for (unsigned j=0; j<N; j++){
        if(i!=j){
            prov[k]=listaCD[j];
            k++;
        }
    }
    if (listaCD!=NULL) delete[] listaCD;
    N--;
    listaCD = prov;
}
void ListaCD::imprimir() {
    cout << "LISTACD " << N << endl;
    for(unsigned i=0; i<N; i++){
        cout << i << ") ";
        cout << listaCD[i];
        cout << endl;
    }
}

void ListaCD::ler(istream &I) {
    string cabecalho;
    int n;
    Cd cd;
    getline(I,cabecalho,' ');
    I >> n;
    if(cabecalho!="LISTACD"){
        cout << "Arquivo com cabeçalho de livros inválido." << endl;
    }else if(n<0){
        cout << "Arquivo com indece do cabeçalho inválido." << endl;
    }else{
        criar(n);
        for(unsigned i = 0; i<N;i++){
            cd.ler(I);
            listaCD[i] = cd;
        }
    }
}
void ListaCD::salvar(ostream &O) {
    O << "LISTACD " << N << endl;
    for (unsigned i = 0; i < N; i++) {
        listaCD[i].salvar(O);
        O << endl;
    }
}
