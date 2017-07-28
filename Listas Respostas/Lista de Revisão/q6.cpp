#include <iostream>
using namespace std;
int main(void){
    int vetorNotas[6];
    int vetorValores[6] = {100,50,20,10,5,2};
    int valorPago;
    cout << "Digite o valor: ";
    cin >> valorPago;
    for(int i =0; i<6;i++){
        vetorNotas[i] = valorPago/vetorValores[i];
        valorPago = valorPago%vetorValores[i];
    }
    for(int i=0; i<6;i++){
        if(vetorNotas[i]!=0){
            cout << vetorNotas[i] << " notas de " << vetorValores[i] << " reais" << endl;
        }
    }

}
