//
// Created by marcus on 04/09/17.
//

#include "ListaDVD.h"

void ListaDVD::criar(unsigned n) {
    N = n;
    if (N>0) listaDVD = new Dvd[n];
    else listaDVD = NULL;
}
void ListaDVD::limpar() {
    if (listaDVD!=NULL) delete[] listaDVD;
    N = 0;
    listaDVD = NULL;
}
void ListaDVD::copiar(const ListaDVD &listaCopy) {
    criar(listaCopy.N);
    for (unsigned i=0; i<N; i++) listaDVD[i]=listaCopy.listaDVD[i];
}
void ListaDVD::incluir(const Dvd &dvd) {
    Dvd *prov = new Dvd[N+1];
    for (unsigned i=0; i<N; i++) prov[i]=listaDVD[i];
    prov[N] = dvd;
    if (listaDVD!=NULL) delete[] listaDVD;
    N++;
    listaDVD = prov;
}
void ListaDVD::excluir(const unsigned i) {
    unsigned k = 0;
    Dvd *prov = new Dvd[N-1];
    for (unsigned j=0; j<N; j++){
        if(i!=j){
            prov[k]=listaDVD[j];
            k++;
        }
    }
    if (listaDVD!=NULL) delete[] listaDVD;
    N--;
    listaDVD = prov;
}
void ListaDVD::imprimir() {
    cout << "LISTACD " << N << endl;
    for(unsigned i=0; i<N; i++){
        cout << i << ") ";
        cout << listaDVD[i];
        cout << endl;
    }
}
void ListaDVD::ler(istream &I) {
    string cabecalho;
    int n;
    Dvd dvd;
    getline(I,cabecalho,' ');
    I >> n;
    if(cabecalho!="LISTADVD"){
        cout << "Arquivo com cabeçalho de livros inválido." << endl;
    }else if(n<0){
        cout << "Arquivo com indece do cabeçalho inválido." << endl;
    }else{
        criar(n);
        for(unsigned i = 0; i<N;i++){
            dvd.ler(I);
            listaDVD[i] = dvd;
        }
    }
}
void ListaDVD::salvar(ostream &O) {
    O << "LISTADVD " << N << endl;
    for (unsigned i = 0; i < N; i++) {
        listaDVD[i].salvar(O);
        O << endl;
    }
}
