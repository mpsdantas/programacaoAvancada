#include <iostream>
using namespace std;
unsigned int  inverte(unsigned int num){
    int numNew;
    while(true){
        numNew += num%10;
        num = num/10;
        if(num==0)
            break;
        numNew *=10;

    }
    return numNew;
}
int main(void){
    unsigned int num;
    cout << "Numero: ";
    cin >> num;
    cout << inverte(num);
}
