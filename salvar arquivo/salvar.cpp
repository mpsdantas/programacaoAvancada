#include <iostream>
#include <fstream>
using namespace std;
int main(){
    string nome_arquivo;
    cout << "Nome do arquivo (sem espacos)? \n";
    cin >> nome_arquivo; // Pode usar >> porque o nome do arquivo nao contem espacos
    ofstream arq(nome_arquivo.c_str());
    if (arq.is_open())
    {
      cout << "Escrevendo no arquivo " << nome_arquivo << ":\n";
      arq << "Marcus é lindo" << endl;
    }
    else
    {
      cerr << "Erro na abertura do arquivo " << nome_arquivo << " para escrita\n";
    }
}
