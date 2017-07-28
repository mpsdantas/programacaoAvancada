#include <iostream>
using namespace std;
float mediaNumeros(float *vfloat){
    int i = 0;
    float media = 0.0;
    while(true){
        if(vfloat[i]==0)
            break;
        media+=vfloat[i];
        i++;
    }
    return media/i;
}
float menorNumero(float *vfloat){
    float menor=vfloat[0];
    int i =1;
    while(true){
        if(vfloat[i]==0)
            break;
        if(vfloat[i]<menor)
            menor = vfloat[i];
        i++;
    }
    return menor;
}
float diferenca(float *vfloat){
    float media, menor;
    media = mediaNumeros(vfloat);
    menor = menorNumero(vfloat);
    return (media - menor);
}
int main(){
    float vfloat[] = {1,7,4,0};
    cout << diferenca(vfloat);
}
