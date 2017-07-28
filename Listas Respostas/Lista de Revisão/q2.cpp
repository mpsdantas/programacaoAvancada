#include <iostream>
using namespace std;
int main(void){
    float num1, num2;
    char operacao;
    bool continuar = true;
    while(true){
        cout << "Digite sua operação (+, -, / ou *): ";
        cin >> operacao;
        if(!(operacao=='+'||operacao=='-'||operacao=='/'||operacao=='*'))
            break;
        cout << "Primeiro número: ";
        cin >> num1;
        cout << "Segundo número: ";
        cin >> num2;
        switch(operacao){
            case '+':
                cout << "Resultado: " << num1+num2 << endl;
                break;
            case '-':
                cout << "Resultado: " << num1-num2 << endl;
                break;
            case '/':
                cout << "Resultado: " << num1/num2 << endl;
                break;
            case '*':
                cout << "Resultado: " << num1*num2 << endl;
                break;
        }
    }
}
