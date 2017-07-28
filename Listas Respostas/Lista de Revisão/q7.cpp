#include <iostream>
using namespace std;
int ordenar(int &a, int &b, int &c){
    int aux;
    int vetorOrdenar[] = {a, b, c};
    for(int i =0; i<3; i++){
        for(int j = i+1; j<3;j++){
            if(vetorOrdenar[i]>vetorOrdenar[j]){
                aux = vetorOrdenar[i];
                vetorOrdenar[i] = vetorOrdenar[j];
                vetorOrdenar[j] = aux;
            }
        }
    }
    a = vetorOrdenar[0];
    b = vetorOrdenar[1];
    c = vetorOrdenar[2];
}
int main(void){
    int a,b,c;
    cout << "Num A: " << endl;
    cin >> a;
    cout << "Num B: "<<endl;
    cin >> b;
    cout << "Num C: " << endl;
    cin >> c;
    ordenar(a,b,c);
    cout << a << " " << b << " " << c;
}
