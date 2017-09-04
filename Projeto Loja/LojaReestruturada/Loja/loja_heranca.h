#ifndef _LOJA_H_
#define _LOJA_H_
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Produto{
private:
    string nome;
    unsigned preco;
    inline unsigned parseCent(float valor){return (valor*100);}
    double parseReal();
public:
    inline Produto(const char *N="", unsigned P=0): nome(N), preco(P) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O);
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O){return imprimir(O);}
};
double Produto::parseReal() {
    /*
     * Convertento o preco em centavos para valor em real.
     * retorna o preço em reais.
     */
    double produtoAux;
    produtoAux = preco/100 + (preco%100)/100.0;
    return produtoAux;
}
istream& Produto::digitar(istream &I) {
    /*
     * Recebe a entrada necessária dos valores do produto: nome e preço.
     * O preço é passado em reais e salvo em centavos.
     */
    float precoAuxiliar;
    cout << "Nome do produto: "<<endl;
    do{
        getline(I,nome);
    }while(nome.size()==0);
    do{
        cout << "Preço do produto: " << endl;
        I >> precoAuxiliar;
    }while(precoAuxiliar<0);
    preco = parseCent(precoAuxiliar);
}
ostream& Produto::imprimir(ostream &O){
    O << '"';
    O << nome;
    O << '"';
    O << fixed;
    O.precision(2);
    O << ";$" << parseReal();
}
istream& Produto::ler(istream &I){
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
inline istream &operator>>(istream &I, Produto &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Produto &X) {return X.imprimir(O);}

// =========================================
// Inclua aqui as classes Livro, CD e DVD
// =========================================

class Livro: public Produto{
private:
    string autor;
public:
    inline Livro(const char *A=""): autor(A) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O);
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O){return imprimir(O);}
};
istream& Livro::digitar(istream &I){
    Produto::digitar(I);
    do{
        cout << "Autor do livro:" << endl;
        I.ignore();
        getline(I,autor);
    }while(autor.size()==0);
}
ostream& Livro::imprimir(ostream &O){
    O << "L: ";
    Produto::imprimir(O);
    O << ';';
    O << '"';
    O << autor;
    O << '"';
}
istream& Livro::ler(istream &I){
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), '"');
    getline(I,autor,'"');
}
inline istream &operator>>(istream &I, Livro &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Livro &X) {return X.imprimir(O);}

class Cd: public Produto{
private:
    int numFaixas;
public:
    inline Cd(const int m=0): numFaixas(m) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O);
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O){return imprimir(O);}
};
istream& Cd::digitar(istream &I){
    Produto::digitar(I);
    do{
        cout << "Quantidade de faixas: " << endl;
        I  >> numFaixas;
    }while(numFaixas<=0);
}
ostream& Cd::imprimir(ostream &O){
    O << "C: ";
    Produto::imprimir(O);
    O << ';';
    O << numFaixas;
}
istream& Cd::ler(istream &I){
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> numFaixas;
}
inline istream &operator>>(istream &I, Cd &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Cd &X) {return X.imprimir(O);}

class Dvd: public Produto{
private:
    unsigned duracao;
public:
    inline Dvd(const unsigned m=0): duracao(m) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O);
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O){return imprimir(O);}
};
istream& Dvd::digitar(istream &I){
    Produto::digitar(I);
    do{
        cout << "Digite a duração do filme: " << endl;
        I  >> duracao;
    }while(duracao<=0);
}
ostream& Dvd::imprimir(ostream &O){
    cout << "D: ";
    Produto::imprimir(O);
    O << ";";
    O << duracao;
}
istream& Dvd::ler(istream &I){
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> duracao;
}
inline istream &operator>>(istream &I, Dvd &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Dvd &X) {return X.imprimir(O);}

class ListaLivro{
private:
    Livro *x;
    unsigned N;
    void criar(unsigned n);
    void copiar(const ListaLivro &listaCopy);
    void limpar();
public:
    // Inclua os construtores, destrutor e operadores necessarios
    inline ListaLivro(): N(0), x(NULL){}
    inline ListaLivro(const ListaLivro &listaCopy) {copiar(listaCopy);}
    inline ~ListaLivro(){limpar();}
    void incluir(const Livro &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};
void ListaLivro::criar(unsigned n) {
    N = n;
    if (N>0) x = new Livro[n];
    else x = NULL;
}
void ListaLivro::limpar() {
    if (x!=NULL) delete[] x;
    N = 0;
    x = NULL;
}
void ListaLivro::copiar(const ListaLivro &listaCopy) {
    criar(listaCopy.N);
    for (unsigned i=0; i<N; i++) x[i]=listaCopy.x[i];
}
void ListaLivro::incluir(const Livro &L){
    Livro *prov = new Livro[N+1];
    for (unsigned i=0; i<N; i++) prov[i]=x[i];
    prov[N] = L;
    if (x!=NULL) delete[] x;
    N++;
    x = prov;
}
void ListaLivro::excluir(unsigned id){
    unsigned k = 0;
    Livro *prov = new Livro[N-1];
    for (unsigned j=0; j<N; j++){
        if(id!=j){
            prov[k]=x[j];
            k++;
        }
    }
    if (x!=NULL) delete[] x;
    N--;
    x = prov;
}
void ListaLivro::imprimir() const{
    cout << "LISTALIVRO " << N << endl;
    for(unsigned i=0; i<N; i++){
        cout << i << ") ";
        cout << x[i];
        cout << endl;
    }
}
void ListaLivro::ler(istream &I){
    string cabecalho;
    int n;
    Livro livro;
    getline(I,cabecalho,' ');
    I >> n;
    criar(n);
    for(unsigned i = 0; i<N;i++){
        livro.ler(I);
        x[i] = livro;
    }
    /*
    if(cabecalho!="LISTALIVRO"){
        cout << "Arquivo com cabeçalho de livros inválido." << endl;
    }else if(n<0){
        cout << "Arquivo com indece do cabeçalho inválido." << endl;
    }else{
        criar(n);
        for(unsigned i = 0; i<N;i++){
            livro.ler(I);
            x[i] = livro;
        }
    }
    */
}
void ListaLivro::salvar(ostream &O) const{
    O << "LISTALIVRO " << N << endl;
    for (unsigned i = 0; i < N; i++) {
        x[i].salvar(O);
        O << endl;
    }
}

// =========================================
// Inclua aqui as classes ListaCD e ListaDVD
// =========================================

class ListaCD{
private:
    Cd *x;
    unsigned N;
    void criar(unsigned n);
    void copiar(const ListaCD &listaCopy);
    void limpar();
public:
    // Inclua os construtores, destrutor e operadores necessarios
    inline ListaCD(): N(0), x(NULL){}
    inline ListaCD(const ListaCD &listaCopy) {copiar(listaCopy);}
    inline ~ListaCD(){limpar();}
    void incluir(const Cd &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};
void ListaCD::criar(unsigned n) {
    N = n;
    if (N>0) x = new Cd[n];
    else x = NULL;
}
void ListaCD::limpar() {
    if (x!=NULL) delete[] x;
    N = 0;
    x = NULL;
}
void ListaCD::copiar(const ListaCD &listaCopy) {
    criar(listaCopy.N);
    for (unsigned i=0; i<N; i++) x[i]=listaCopy.x[i];
}
void ListaCD::incluir(const Cd &L){
    Cd *prov = new Cd[N+1];
    for (unsigned i=0; i<N; i++) prov[i]=x[i];
    prov[N] = L;
    if (x!=NULL) delete[] x;
    N++;
    x = prov;
}
void ListaCD::excluir(unsigned id){
    unsigned k = 0;
    Cd *prov = new Cd[N-1];
    for (unsigned j=0; j<N; j++){
        if(id!=j){
            prov[k]=x[j];
            k++;
        }
    }
    if (x!=NULL) delete[] x;
    N--;
    x = prov;
}
void ListaCD::imprimir() const{
    cout << "LISTACD " << N << endl;
    for(unsigned i=0; i<N; i++){
        cout << i << ") ";
        cout << x[i];
        cout << endl;
    }
}
void ListaCD::ler(istream &I){
    string cabecalho;
    int n;
    Cd cd;
    getline(I,cabecalho,' ');
    I >> n;
    criar(n);
    for(unsigned i = 0; i<N;i++){
        cd.ler(I);
        x[i] = cd;
    }
    /*
    if(cabecalho!="LISTACD"){
        cout << "Arquivo com cabeçalho de livros inválido." << endl;
    }else if(n<0){
        cout << "Arquivo com indece do cabeçalho inválido." << endl;
    }else{
        criar(n);
        for(unsigned i = 0; i<N;i++){
            cd.ler(I);
            x[i] = cd;
        }
    }
    */
}
void ListaCD::salvar(ostream &O) const{
    O << "LISTACD " << N << endl;
    for (unsigned i = 0; i < N; i++) {
        x[i].salvar(O);
        O << endl;
    }
}

class ListaDVD{
private:
    Dvd *x;
    unsigned N;
    void criar(unsigned n);
    void copiar(const ListaDVD &listaCopy);
    void limpar();
public:
    // Inclua os construtores, destrutor e operadores necessarios
    inline ListaDVD(): N(0), x(NULL){}
    inline ListaDVD(const ListaDVD &listaCopy) {copiar(listaCopy);}
    inline ~ListaDVD(){limpar();}
    void incluir(const Dvd &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};
void ListaDVD::criar(unsigned n) {
    N = n;
    if (N>0) x = new Dvd[n];
    else x = NULL;
}
void ListaDVD::limpar() {
    if (x!=NULL) delete[] x;
    N = 0;
    x = NULL;
}
void ListaDVD::copiar(const ListaDVD &listaCopy) {
    criar(listaCopy.N);
    for (unsigned i=0; i<N; i++) x[i]=listaCopy.x[i];
}
void ListaDVD::incluir(const Dvd &L){
    Dvd *prov = new Dvd[N+1];
    for (unsigned i=0; i<N; i++) prov[i]=x[i];
    prov[N] = L;
    if (x!=NULL) delete[] x;
    N++;
    x = prov;
}
void ListaDVD::excluir(unsigned id){
    unsigned k = 0;
    Dvd *prov = new Dvd[N-1];
    for (unsigned j=0; j<N; j++){
        if(id!=j){
            prov[k]=x[j];
            k++;
        }
    }
    if (x!=NULL) delete[] x;
    N--;
    x = prov;
}
void ListaDVD::imprimir() const{
    cout << "LISTADVD " << N << endl;
    for(unsigned i=0; i<N; i++){
        cout << i << ") ";
        cout << x[i];
        cout << endl;
    }
}
void ListaDVD::ler(istream &I){
    string cabecalho;
    int n;
    Dvd dvd;
    getline(I,cabecalho,' ');
    I >> n;
    criar(n);
    for(unsigned i = 0; i<N;i++){
        dvd.ler(I);
        x[i] = dvd;
    }
    /*
    if(cabecalho!="LISTADVD"){
        cout << "Arquivo com cabeçalho de livros inválido." << endl;
    }else if(n<0){
        cout << "Arquivo com indece do cabeçalho inválido." << endl;
    }else{
        criar(n);
        for(unsigned i = 0; i<N;i++){
            dvd.ler(I);
            x[i] = dvd;
        }
    }*/
}
void ListaDVD::salvar(ostream &O) const{
    O << "LISTADVD " << N << endl;
    for (unsigned i = 0; i < N; i++) {
        x[i].salvar(O);
        O << endl;
    }
}

class Loja{
private:
    ListaLivro LL;
    ListaCD LC;
    ListaDVD LD;
public:
    inline Loja(): LL(), LC(), LD() {}
    inline void incluirLivro(const Livro &X) {LL.incluir(X);}
    inline void excluirLivro(unsigned id) {LL.excluir(id);}
    inline void incluirDVD(const Dvd &X) {LD.incluir(X);}
    inline void excluirDVD(unsigned id) {LD.excluir(id);}
    inline void incluirCD(const Cd &X) {LC.incluir(X);}
    inline void excluirCD(unsigned id) {LC.excluir(id);}
    void imprimir();
    void ler(const char* arq);
    void salvar(const char* arq) const;
};
void Loja::imprimir(){
    LL.imprimir();
    LC.imprimir();
    LD.imprimir();
}
void Loja::ler(const char* arq){
    ifstream arquivo(arq);
    LL.ler(arquivo);
    LC.ler(arquivo);
    LD.ler(arquivo);
}
void Loja::salvar(const char* arq) const{
    ofstream arquivo(arq);
    LL.salvar(arquivo);
    LC.salvar(arquivo);
    LD.salvar(arquivo);
};
#endif // _LOJA_H_
