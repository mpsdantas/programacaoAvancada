#include <iostream>
using namespace std;

int retornarDia(int dia, int mes, int ano){
    int mDiasMeses[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int dias = 0;
    if(ano%400==0||(ano%4==0 && ano%100!=0)){
        mDiasMeses[1] = 29;
    }
    for(int i =0; i<(mes-1);i++){
        dias += mDiasMeses[i];
    }
    dias+=dia;
    return dias;
}
int main(void){
    int dia, mes, ano;
    cout << "Digite o dia: ";
    cin >> dia;
    cout << "Digite o Mês: ";
    cin >> mes;
    cout << "Digite o Ano: ";
    cin >> ano;
    cout << retornarDia(dia,mes,ano);
}
