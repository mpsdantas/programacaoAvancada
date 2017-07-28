#include <iostream>
using namespace std;
int main(void){
    float soma = 0.0;
    float numeros;
    int contador=0;
    while(true){
        cout << "Digite um número: ";
        cin >> numeros;
        if(numeros<0){
            break;
        }
        soma += numeros;
        contador++;
    }
    cout << soma << endl;
    cout << contador << endl;
    cout << "A média é: " << soma/contador;
}
