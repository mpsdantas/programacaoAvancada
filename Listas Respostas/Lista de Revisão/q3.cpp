#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(void){
    srand((int)time(0));
    int random = rand()%101;
    int tentativa, contador = 0;
    while(true){
        cout << "Digite o número: ";
        cin >> tentativa;
        contador++;
        if(random==tentativa){
            cout << "Parabéns, você acertou!"<<endl;
            cout << "Quantidade de tentativas " << contador << endl;
            cout << "Número aleátorio " << random << endl;
            break;
        }else if(tentativa<random){
            cout << "O número informado é menor que o número gerado." << endl;
        }else{
            cout << "O número informado é maior que o número gerado." << endl;
        }
    }
}
